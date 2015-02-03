/*
**==============================================================================
**
** ODatatLite ver. 0.0.3
**
** Copyright (c) Microsoft Corporation
**
** All rights reserved. 
**
** MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy ** of this software and associated documentation files (the ""Software""), to 
** deal in the Software without restriction, including without limitation the 
** rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
** sell copies of the Software, and to permit persons to whom the Software is 
** furnished to do so, subject to the following conditions: The above copyright ** notice and this permission notice shall be included in all copies or 
** substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
** THE SOFTWARE.
**
**==============================================================================
*/
#include "post.h"
#include "scope.h"
#include "odataplugin.h"
#include <phit.h>
#include <base/shlib.h>
#include <base/str.h>
#include <base/http.h>
#include <base/str.h>
#include <base/alloc.h>
#include <base/log.h>
#include <base/html.h>
#include <base/dump.h>
#include <base/path.h>
#include <base/role.h>
#include <odata/odata.h>
#include <odata/odatamacros.h>
#include <odata/scope.h>
#include <odata/outstream.h>
#include <odata/uri.h>
#include <odata/uriparser.h>
#include <odata/serialize.h>
#include <odata/result.h>
#include <odata/csdl.h>
#include <server/contextoptions.h>
#include "providers.h"
#include "options.h"
#include "webpage.h"

#define D(X)

/* Defined ENABLE_LOGP to log provider errors when calling into scope */
#if defined(ENABLE_LOGP)
# define LOGP LOGW
#else
# define LOGP(EXPR) 
#endif

static OL_Scope* _Scope_New();

static OL_Scope* _scopeCache[4];
size_t _scopeCacheSize;

OL_Scope* ScopeCache_Get()
{
    if (_scopeCacheSize == 0)
        return _Scope_New();
    else
    {
        OL_Scope* scope = _scopeCache[--_scopeCacheSize];
        OL_Scope_Reset(scope);
        return scope;
    }
}

void ScopeCache_Put(OL_Scope* scope)
{
    if (_scopeCacheSize != OL_ARRAYSIZE(_scopeCache))
        _scopeCache[_scopeCacheSize++] = scope;
    else
        OL_Scope_Release(scope);
}

void ScopeCache_Release()
{
    size_t i;

    for (i = 0; i < _scopeCacheSize; i++)
    {
        OL_Scope* scope = _scopeCache[--_scopeCacheSize];
        OL_Scope_Release(scope);
    }

    _scopeCacheSize = 0;
}

/*
**=============================================================================
**
** Scope
**
**=============================================================================
*/

/* Post "@odata.nextLink" property */
static void _SerializeNextLink(
    Buf* out,
    const char* requestURI,
    const char* skiptoken)
{
    BufCat(out, STRLIT("\"@odata.nextLink\": \""));

    /* Serialize the request URI */
    {
        const char* start = requestURI;
        const char* end;

        /* Skip over leading '/' (if any) */
        if (*start == '/')
            start++;

        /* Find '?' (beginning of query options */
        for (end = start; *end && *end != '?'; end++)
            ;

        /* Serialize the request URI */
        BufCat(out, start, end - start);
    }

    /* Serialize the skiptoken */
    BufCat(out, STRLIT("?$skiptoken="));
    BufCat(out, skiptoken, strlen(skiptoken));
    BufCat(out, STRLIT("\""));
}

static OL_Result _Scope_SendBeginEntitySet(
    OL_Scope* self_)
{
    Scope* self = (Scope*)self_;
    PHIT_Context* context = (PHIT_Context*)self->privateData;

    D( printf("Enter.SendBeginEntitySet\n"); )

    /* Bail out if already in error state */
    if (self->error)
        return OL_Result_Failed;

    if (self->postBeginEntitySet)
    {
        LOGP(("SendBeginEntitySet: called more than once"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postEntity)
    {
        LOGP(("SendBeginEntitySet: called after SendEntity"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postEndEntitySet)
    {
        LOGP(("SendBeginEntitySet: called after SendEndEntitySet"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->isCountRequest)
    {
        self->postBeginEntitySet++;
        self->error = OL_TRUE;
        return OL_Result_Ok;
    }

    {
        BufDefine(buf, 128);

        PostStatusLineAndHeaders(
            context, 
            self->httpStatusCode, 
            self->httpStatusMsg, 
            "application/json");

        BufCatCh2(&buf, '{', '\n');

        if (self->metadataType != OL_MetadataType_None)
        {
            BufCat(&buf, STRLIT("  \"@odata.context\": \""));
            BufCatStr(&buf, self->contextURI);
            BufCat(&buf, STRLIT("\",\n"));
        }

        BufCat(&buf, STRLIT("  \"value\": [\n"));

#if 0
        Dump(stdout, "POST.CONTENT.BEGIN", buf.data, buf.size);
#endif

        PHIT_Context_PostContent(context, buf.data, buf.size);
        BufDestroy(&buf);
        self->postHTTPPreamble++;
    }

    self->postBeginEntitySet++;

    D( printf("Leave.SendBeginEntitySet\n"); )

    return OL_Result_Ok;
}

static OL_Result _Scope_SendMetadataXML(
    OL_Scope* self_,
    const char* data,
    size_t size)
{
    Scope* self = (Scope*)self_;
    PHIT_Context* context = (PHIT_Context*)self->privateData;

    D( printf("Enter.SendMetadataAux\n"); )

    /* Bail out if already in error state */
    if (self->error)
        return OL_Result_Failed;

    if (self->postMetadata)
    {
        LOGP(("SendMetadataAux: called more than once"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postBeginEntitySet)
    {
        LOGP(("SendMetadataAux: called after SendBeginEntity"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postEntity)
    {
        LOGP(("SendMetadataAux: called after SendEntity"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postEndEntitySet)
    {
        LOGP(("SendMetadataAux: called after SendEndEntitySet"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    /* Post the headers */
    {
        PostStatusLineAndHeaders(
            context, 
            self->httpStatusCode, 
            self->httpStatusMsg, 
            "application/xml");

        self->postHTTPPreamble++;
    }

    /* Post the content */
    PHIT_Context_PostContent(context, data, size);
    self->postMetadata++;

    return OL_Result_Ok;
}

static OL_Result _Scope_SendMetadataStruct(
    OL_Scope* self_,
    const EDMX_Edmx* edmx)
{
    Scope* self = (Scope*)self_;
    Buf buf = BUF_INITIALIZER;
    OL_Result r;

    if (CSDL_Serialize(&buf, edmx) != 0)
    {
        BufDestroy(&buf);
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if ((r = _Scope_SendMetadataXML(self_, buf.data, buf.size)) != OL_Result_Ok)
    {
        BufDestroy(&buf);
        return r;
    }

    BufDestroy(&buf);
    return OL_Result_Ok;
}

static OL_Result _Scope_SendEntityAux(
    OL_Scope* self_,
    const OL_Object* object)
{
    Scope* self = (Scope*)self_;
    PHIT_Context* context = (PHIT_Context*)self->privateData;
    Buf* out;
    size_t indent;
    size_t chunkPrefixOffset = 0;
    int chunkedEncoding = 0;
    const char* propertyName;

    /* Bail out if in error state already */
    if (self->error)
        return OL_Result_Failed;

    /* If provider failed to call PostBeginEntitySet() */
    if (!self->postBeginEntitySet && self->postEntity == 1)
    {
        LOGP(("SendEntity: called twice but no SendBeginEntitySet"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    /* If provider called SendEntity() after SendBeginEntitySet() */
    if (self->postEndEntitySet)
    {
        LOGP(("SendEntity: called after SendEndEntitySet"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->isCountRequest)
    {
        self->postEntity++;
        self->count++;
        return OL_Result_Ok;
    }

    if (self->postBeginEntitySet)
        propertyName = NULL;
    else
        propertyName = self->unmatchedSegmentName;

    /* $skip query option (skip=0 by default) */
    if (self->count < self->skip)
    {
        /* Ignore this instance */
        self->count++;
        return OL_Result_Ok;
    }

    /* $top query option (top=UINT_MAX by default) */
    if (self->count >= self->top)
    {
        /* Ignore this instance */
        self->count++;
        return OL_Result_Ok;
    }

    /* Increment the instance counter */
    self->count++;

    /* Post HTTP status line and headers only first time */
    if (!self->postHTTPPreamble)
    {
        const char* contentType;

        if (self->uriQueryOptions & OL_QUERY_OPTION_VALUE)
            contentType = "text/plain";
        else
            contentType = "application/json";

        PostStatusLineAndHeaders(
            context, 
            self->httpStatusCode, 
            self->httpStatusMsg, 
            contentType);

        self->postHTTPPreamble++;
    }

    /* Initialize OutStream from the internal PHIT buffer */
    {
        if (PHIT_Context_GetOption(context, CONTEXT_OPTION_BUF, &out,
            sizeof(Buf)) != 0)
        {
            LOGE(("PHIT_Context_GetOption(BUF)"));
            self->error = OL_TRUE;
            return OL_Result_Failed;
        }

        self->out = out;
    }

    /* Get whether chunked encoding was requested */
    if (PHIT_Context_GetOption(
        context, 
        CONTEXT_OPTION_CHUNKED_ENCODING, 
        &chunkedEncoding, 
        sizeof(chunkedEncoding)) != 0)
    {
        LOGE(("PHIT_Context_GetOption(CHUNKED_ENCODING)"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    /* Write the HTTP chunk prefix (if any) */
    if (chunkedEncoding)
    {
        chunkPrefixOffset = out->size;
        HTTPFormatNullChunkPrefix(out);
    }

    /* Determine level of indentation */
    indent = self->postBeginEntitySet ? 2 : 0;

    /* Put comma if this is not the first entity */
    if (self->postEntity)
    {
        BufCatCh2(out, ',', '\n');
    }

    /* Append extras to "@odata.context" */
    /* ATTN: move this logic into URIFormatContextURL() */
    if (!self->postEntity && !self->postBeginEntitySet &&
        strcmp(self->contextURI, "odata/$metadata") != 0 &&
        !propertyName)
    {
        Strlcat(self->contextURI, "/$entity", sizeof(self->contextURI));
    }

    /* Serialize the object */
    {
        if (self->uriQueryOptions & OL_QUERY_OPTION_COUNT)
            propertyName = "count";

        if (((self->uriQueryOptions & OL_QUERY_OPTION_COUNT) ||
            (self->uriQueryOptions & OL_QUERY_OPTION_VALUE)) &&
            propertyName)
        {
            OL_Value value;

            if (OL_Object_Get(object, propertyName, &value) != OL_Result_Ok)
            {
                LOGE(("property not found: %s", propertyName));
                self->error = OL_TRUE;
                return OL_Result_Failed;
            }

            SerializeRawPrimitiveValue(self->out, &value);

            if (self->out->err)
            {
                LOGE(("serialize failed"));
                self->error = OL_TRUE;
                return OL_Result_Failed;
            }
        }
        else
        {
            SerializeObject(
                (JSONObject*)object,
                self->postBeginEntitySet ? NULL : self->contextURI,
                self->out,
                indent,
                1,
                self->metadataType,
                propertyName);

            if (self->out->err)
            {
                LOGE(("serialize failed"));
                self->error = OL_TRUE;
                return OL_Result_Failed;
            }
        }
    }

    if (chunkedEncoding)
    {
        /* Now that we have the chunk size, update the null chunk prefix */
        UIntToHexStr8(
            out->data + chunkPrefixOffset, 
            out->size - chunkPrefixOffset - MAX_CHUNK_PREFIX_SIZE);

        /* Write the HTTP chunk suffix */
        HTTPFormatChunkSuffix(out);
    }

    self->postEntity++;

    return OL_Result_Ok;
}

static OL_Result _Scope_SendEntity(
    OL_Scope* self,
    const OL_Object* object)
{
    if (!object)
        return OL_Result_BadParameter;

    return _Scope_SendEntityAux(self, object);
}

static OL_Result _Scope_SendEndEntitySet(
    OL_Scope* self_,
    const char* skiptoken)
{
    Scope* self = (Scope*)self_;
    PHIT_Context* context = (PHIT_Context*)self->privateData;

    D( printf("Enter.SendEntity\n"); )

    /* If already in an error state */
    if (self->error)
        return OL_Result_Failed;

    if (!self->postBeginEntitySet)
    {
        LOGP(("SendEndEntitySet: SendBeginEntitySet never called"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postEndEntitySet)
    {
        LOGP(("SendEndEntitySet: called more than once"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->isCountRequest)
    {
        self->postEndEntitySet++;
        return OL_Result_Ok;
    }

    {
        BufDefine(buf, 128);

        BufCat(&buf, STRLIT("\n  ]"));

        if (skiptoken)
        {
            BufCat(&buf, STRLIT(",\n  "));
            _SerializeNextLink(&buf, self->requestURI, skiptoken);
        }

        BufCat(&buf, STRLIT("\n}\n"));
        PHIT_Context_PostContent(context, buf.data, buf.size);
        BufDestroy(&buf);
    }

    self->postEndEntitySet++;

    D( printf("Leave.SendEntity\n"); )

    return OL_Result_Ok;
}

static OL_Result _Scope_SendResult(
    OL_Scope* self_,
    OL_Result result,
    const char* format,
    va_list ap)
{
    Scope* self = (Scope*)self_;
    PHIT_Context* context = (PHIT_Context*)self->privateData;

    D( printf("Enter.SendResult\n"); )

    if (self->error)
        return OL_Result_Failed;

    /* Check whether context is invalid */
    if (self->magic != CONTEXT_MAGIC)
    {
        LOGP(("SendResult: called with corrupt context"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (self->postResult)
    {
        LOGP(("SendResult: already called on this context"));
        self->error = OL_TRUE;
        return OL_Result_Failed;
    }

    if (result == OL_Result_Ok && self->isCountRequest)
    {
        PostCountResponse(context, self->count);
        self->postHTTPPreamble++;
    }

    /* Ignore error if data already posted (cannot report error after fact) */
    if (result != OL_Result_Ok &&
        !self->postHTTPPreamble && 
        !self->postBeginEntitySet && 
        !self->postEntity &&
        !self->postEndEntitySet &&
        !self->postMetadata)
    {
        PostErrorV(context, result, format, ap);
        self->postHTTPPreamble++;
    }
    else
    {
        /* If no HTTP preamble */
        if (!self->postHTTPPreamble)
        {
            PostStatusLineAndHeaders(
                context, 
                self->httpStatusCode, 
                self->httpStatusMsg, 
                "application/json");
            self->postHTTPPreamble++;
        }

        PHIT_Context_PostEOC(context);
    }

    self->postResult++;

    PHIT_Context_SetPluginData(context, NULL);
    ScopeCache_Put(self_);

    D( printf("Leave.SendResult\n"); )

    return OL_Result_Ok;
}

static OL_Result _Scope_GetOption(
    const OL_Scope* self_,
    int option,
    void* value,
    size_t valueSize)
{
    Scope* self = (Scope*)self_;

    if (!self || !value)
        return OL_Result_BadParameter;


#if defined(ENABLE_DEBUG) && defined(ENABLE_ALLOCATOR)
    if (option == OPTION_ALLOCSTATS)
    {
        if (valueSize != sizeof(AllocStats))
            return OL_Result_NotFound;

        GetAllocStats((AllocStats*)value);
        return OL_Result_Ok;
    }
#endif

    if (option == OL_Scope_Option_Role && ((Scope*)self)->phitContext)
    {
        PHIT_Role role;

        if (valueSize != sizeof(const char*))
        {
            self->error = OL_TRUE;
            return OL_Result_Failed;
        }

        if (PHIT_Context_GetOption(
            ((Scope*)self)->phitContext,
            PHIT_CONTEXT_OPTION_ROLE, 
            &role, 
            sizeof(role)) != 0)
        {
            return OL_Result_NotFound;
        }

        *((const char**)value) = RoleName(role);
        return OL_Result_Ok;
    }

    return OL_Result_NotFound;
}

static OL_Scope* _Scope_New()
{
    OL_Scope* scope;

    if (!(scope = __OL_Scope_New()))
        return NULL;

    /* Override these methods */
    scope->ft->SendBeginEntitySet = _Scope_SendBeginEntitySet;
    scope->ft->SendEntity = _Scope_SendEntity;
    scope->ft->SendEndEntitySet = _Scope_SendEndEntitySet;
    scope->ft->SendMetadataStruct = _Scope_SendMetadataStruct;
    scope->ft->SendMetadataXML = _Scope_SendMetadataXML;
    scope->ft->SendResult = _Scope_SendResult;
    scope->ft->GetOption = _Scope_GetOption;

    ((Scope*)scope)->contextURI[0] = '\0';

    return scope;
}
