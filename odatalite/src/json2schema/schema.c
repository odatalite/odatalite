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
#include <odata/json.h>

/*
**********************************************************************************
** schema_AccountService_entityType
**
*********************************************************************************/

static const JSON_Property _schema_AccountService_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_AccountService_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_AccountService_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_AccountService_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_AccountService_AuthFailureLoggingThreshold_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\033AuthFailureLoggingThreshold" /* name */
};

static const JSON_Property _schema_AccountService_MinPasswordLength_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\021MinPasswordLength" /* name */
};

static const JSON_Property _schema_AccountService_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  0, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_AccountService_properties[] =
{
  (const JSON_Property*)&_schema_AccountService_Name_property,
  (const JSON_Property*)&_schema_AccountService_Modified_property,
  (const JSON_Property*)&_schema_AccountService_Type_property,
  (const JSON_Property*)&_schema_AccountService_Description_property,
  (const JSON_Property*)&_schema_AccountService_AuthFailureLoggingThreshold_property,
  (const JSON_Property*)&_schema_AccountService_MinPasswordLength_property,
  (const JSON_Property*)&_schema_AccountService_links_property,
};

static const JSON_EntityType _schema_AccountService_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "AccountService", /* name */
  NULL, /* baseType */
  _schema_AccountService_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_AccountService_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Status_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Status_State_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\005State" /* name */
};

static const JSON_Property _schema_Status_HealthRollUp_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  1, /* index */
  "\014HealthRollUp" /* name */
};

static const JSON_Property _schema_Status_Health_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  2, /* index */
  "\006Health" /* name */
};

static const JSON_Property* _schema_Status_properties[] =
{
  (const JSON_Property*)&_schema_Status_State_property,
  (const JSON_Property*)&_schema_Status_HealthRollUp_property,
  (const JSON_Property*)&_schema_Status_Health_property,
};

static const JSON_EntityType _schema_Status_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Status", /* name */
  NULL, /* baseType */
  _schema_Status_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Status_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Chassis_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Chassis_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Chassis_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_Chassis_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_Chassis_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_Chassis_ChassisType_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  3, /* index */
  "\013ChassisType" /* name */
};

static const JSON_Property _schema_Chassis_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_Chassis_Manufacturer_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014Manufacturer" /* name */
};

static const JSON_Property _schema_Chassis_Model_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005Model" /* name */
};

static const JSON_Property _schema_Chassis_SKU_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\003SKU" /* name */
};

static const JSON_Property _schema_Chassis_SerialNumber_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014SerialNumber" /* name */
};

static const JSON_Property _schema_Chassis_Version_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Version" /* name */
};

static const JSON_Property _schema_Chassis_PartNumber_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012PartNumber" /* name */
};

static const JSON_Property _schema_Chassis_AssetTag_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010AssetTag" /* name */
};

static const JSON_Property _schema_Chassis_IndicatorLED_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  4, /* index */
  "\014IndicatorLED" /* name */
};

static const JSON_Property _schema_Chassis_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_Chassis_properties[] =
{
  (const JSON_Property*)&_schema_Chassis_Name_property,
  (const JSON_Property*)&_schema_Chassis_Modified_property,
  (const JSON_Property*)&_schema_Chassis_Type_property,
  (const JSON_Property*)&_schema_Chassis_Status_property,
  (const JSON_Property*)&_schema_Chassis_ChassisType_property,
  (const JSON_Property*)&_schema_Chassis_Description_property,
  (const JSON_Property*)&_schema_Chassis_Manufacturer_property,
  (const JSON_Property*)&_schema_Chassis_Model_property,
  (const JSON_Property*)&_schema_Chassis_SKU_property,
  (const JSON_Property*)&_schema_Chassis_SerialNumber_property,
  (const JSON_Property*)&_schema_Chassis_Version_property,
  (const JSON_Property*)&_schema_Chassis_PartNumber_property,
  (const JSON_Property*)&_schema_Chassis_AssetTag_property,
  (const JSON_Property*)&_schema_Chassis_IndicatorLED_property,
  (const JSON_Property*)&_schema_Chassis_links_property,
};

static const JSON_EntityType _schema_Chassis_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Chassis", /* name */
  NULL, /* baseType */
  _schema_Chassis_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Chassis_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Collection_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Collection_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Collection_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_Collection_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_Collection_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_Collection_MemberType_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012MemberType" /* name */
};

static const JSON_Property _schema_Collection_Total_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\005Total" /* name */
};

static const JSON_Property _schema_Collection_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  2, /* index */
  "\005links" /* name */
};

static const JSON_Property _schema_Collection_Items_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\005Items" /* name */
};

static const JSON_Property* _schema_Collection_properties[] =
{
  (const JSON_Property*)&_schema_Collection_Name_property,
  (const JSON_Property*)&_schema_Collection_Modified_property,
  (const JSON_Property*)&_schema_Collection_Type_property,
  (const JSON_Property*)&_schema_Collection_Description_property,
  (const JSON_Property*)&_schema_Collection_MemberType_property,
  (const JSON_Property*)&_schema_Collection_Total_property,
  (const JSON_Property*)&_schema_Collection_links_property,
  (const JSON_Property*)&_schema_Collection_Items_property,
};

static const JSON_EntityType _schema_Collection_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Collection", /* name */
  NULL, /* baseType */
  _schema_Collection_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Collection_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_FwRev_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_FwRev_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "FwRev", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ComputerSystem_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ComputerSystem_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_ComputerSystem_SystemType_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  5, /* index */
  "\012SystemType" /* name */
};

static const JSON_Property _schema_ComputerSystem_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  3, /* index */
  "\005links" /* name */
};

static const JSON_Property _schema_ComputerSystem_AssetTag_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010AssetTag" /* name */
};

static const JSON_Property _schema_ComputerSystem_Manufacturer_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014Manufacturer" /* name */
};

static const JSON_Property _schema_ComputerSystem_Model_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005Model" /* name */
};

static const JSON_Property _schema_ComputerSystem_SKU_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\003SKU" /* name */
};

static const JSON_Property _schema_ComputerSystem_SerialNumber_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014SerialNumber" /* name */
};

static const JSON_Property _schema_ComputerSystem_Version_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Version" /* name */
};

static const JSON_Property _schema_ComputerSystem_PartNumber_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012PartNumber" /* name */
};

static const JSON_Property _schema_ComputerSystem_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ComputerSystem_VirtualSerialNumber_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\023VirtualSerialNumber" /* name */
};

static const JSON_Property _schema_ComputerSystem_UUID_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004UUID" /* name */
};

static const JSON_Property _schema_ComputerSystem_HostCorrelation_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  4, /* index */
  "\017HostCorrelation" /* name */
};

static const JSON_Property _schema_ComputerSystem_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_ComputerSystem_BIOSPOSTCode_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\014BIOSPOSTCode" /* name */
};

static const JSON_Property _schema_ComputerSystem_IndicatorLED_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  6, /* index */
  "\014IndicatorLED" /* name */
};

static const JSON_Property _schema_ComputerSystem_Power_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  7, /* index */
  "\005Power" /* name */
};

static const JSON_Property _schema_ComputerSystem_Boot_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  5, /* index */
  "\004Boot" /* name */
};

static const JSON_Property _schema_ComputerSystem_Bios_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  6, /* index */
  "\004Bios" /* name */
};

static const JSON_Property _schema_ComputerSystem_Processors_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  7, /* index */
  "\012Processors" /* name */
};

static const JSON_Property _schema_ComputerSystem_Memory_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  8, /* index */
  "\006Memory" /* name */
};

static const JSON_Property* _schema_ComputerSystem_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_Name_property,
  (const JSON_Property*)&_schema_ComputerSystem_Modified_property,
  (const JSON_Property*)&_schema_ComputerSystem_Type_property,
  (const JSON_Property*)&_schema_ComputerSystem_SystemType_property,
  (const JSON_Property*)&_schema_ComputerSystem_links_property,
  (const JSON_Property*)&_schema_ComputerSystem_AssetTag_property,
  (const JSON_Property*)&_schema_ComputerSystem_Manufacturer_property,
  (const JSON_Property*)&_schema_ComputerSystem_Model_property,
  (const JSON_Property*)&_schema_ComputerSystem_SKU_property,
  (const JSON_Property*)&_schema_ComputerSystem_SerialNumber_property,
  (const JSON_Property*)&_schema_ComputerSystem_Version_property,
  (const JSON_Property*)&_schema_ComputerSystem_PartNumber_property,
  (const JSON_Property*)&_schema_ComputerSystem_Description_property,
  (const JSON_Property*)&_schema_ComputerSystem_VirtualSerialNumber_property,
  (const JSON_Property*)&_schema_ComputerSystem_UUID_property,
  (const JSON_Property*)&_schema_ComputerSystem_HostCorrelation_property,
  (const JSON_Property*)&_schema_ComputerSystem_Status_property,
  (const JSON_Property*)&_schema_ComputerSystem_BIOSPOSTCode_property,
  (const JSON_Property*)&_schema_ComputerSystem_IndicatorLED_property,
  (const JSON_Property*)&_schema_ComputerSystem_Power_property,
  (const JSON_Property*)&_schema_ComputerSystem_Boot_property,
  (const JSON_Property*)&_schema_ComputerSystem_Bios_property,
  (const JSON_Property*)&_schema_ComputerSystem_Processors_property,
  (const JSON_Property*)&_schema_ComputerSystem_Memory_property,
};

static const JSON_EntityType _schema_ComputerSystem_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem", /* name */
  NULL, /* baseType */
  _schema_ComputerSystem_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Description_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Description_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Description", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_Settings_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Settings_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Settings", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_EthernetNetworkInterface_entityType
**
*********************************************************************************/

static const JSON_Property _schema_EthernetNetworkInterface_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_UEFIDevicePath_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016UEFIDevicePath" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_FactoryMacAddress_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\021FactoryMacAddress" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_MacAddress_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012MacAddress" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_LinkTechnology_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  11, /* index */
  "\016LinkTechnology" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_SpeedMbps_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\011SpeedMbps" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_Autosense_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\011Autosense" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_FullDuplex_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\012FullDuplex" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_FrameSize_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\011FrameSize" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_VLANEnable_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\012VLANEnable" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_VLANId_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\006VLANId" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_IPv6AddressPolicyTable_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\026IPv6AddressPolicyTable" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_IPv4Addresses_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\015IPv4Addresses" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_IPv6Addresses_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\015IPv6Addresses" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_MaxIPv6StaticAddresses_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\026MaxIPv6StaticAddresses" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_IPv6StaticAddresses_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\023IPv6StaticAddresses" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_IPv6DefaultGateway_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\022IPv6DefaultGateway" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_NameServers_property =
{
  49, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013NameServers" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_HostName_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010HostName" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_FQDN_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004FQDN" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  9, /* index */
  "\005links" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_SettingsResult_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  7, /* index */
  "\016SettingsResult" /* name */
};

static const JSON_Property* _schema_EthernetNetworkInterface_properties[] =
{
  (const JSON_Property*)&_schema_EthernetNetworkInterface_Name_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_Modified_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_Type_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_Description_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_UEFIDevicePath_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_Status_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_FactoryMacAddress_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_MacAddress_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_LinkTechnology_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_SpeedMbps_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_Autosense_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_FullDuplex_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_FrameSize_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_VLANEnable_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_VLANId_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_IPv6AddressPolicyTable_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_IPv4Addresses_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_IPv6Addresses_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_MaxIPv6StaticAddresses_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_IPv6StaticAddresses_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_IPv6DefaultGateway_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_NameServers_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_HostName_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_FQDN_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_links_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_SettingsResult_property,
};

static const JSON_EntityType _schema_EthernetNetworkInterface_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "EthernetNetworkInterface", /* name */
  NULL, /* baseType */
  _schema_EthernetNetworkInterface_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_EthernetNetworkInterface_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Event_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Event_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Event_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_Event_Events_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\006Events" /* name */
};

static const JSON_Property* _schema_Event_properties[] =
{
  (const JSON_Property*)&_schema_Event_Name_property,
  (const JSON_Property*)&_schema_Event_Type_property,
  (const JSON_Property*)&_schema_Event_Events_property,
};

static const JSON_EntityType _schema_Event_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Event", /* name */
  NULL, /* baseType */
  _schema_Event_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Event_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_EventService_entityType
**
*********************************************************************************/

static const JSON_Property _schema_EventService_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_EventService_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_EventService_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_EventService_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_EventService_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  10, /* index */
  "\005links" /* name */
};

static const JSON_Property _schema_EventService_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_EventService_DeliveryRetryAttempts_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\025DeliveryRetryAttempts" /* name */
};

static const JSON_Property _schema_EventService_DeliveryRetryIntervalInSeconds_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\036DeliveryRetryIntervalInSeconds" /* name */
};

static const JSON_Property _schema_EventService_SubscriptionRemovalAction_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  12, /* index */
  "\031SubscriptionRemovalAction" /* name */
};

static const JSON_Property _schema_EventService_SubscriptionRemovalTimeIntervalInMinutes_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\050SubscriptionRemovalTimeIntervalInMinutes" /* name */
};

static const JSON_Property _schema_EventService_EventTypesForSubscription_property =
{
  40, /* flags */
  JSON_Type_Integer, /* type */
  13, /* index */
  "\031EventTypesForSubscription" /* name */
};

static const JSON_Property* _schema_EventService_properties[] =
{
  (const JSON_Property*)&_schema_EventService_Name_property,
  (const JSON_Property*)&_schema_EventService_Modified_property,
  (const JSON_Property*)&_schema_EventService_Type_property,
  (const JSON_Property*)&_schema_EventService_Description_property,
  (const JSON_Property*)&_schema_EventService_links_property,
  (const JSON_Property*)&_schema_EventService_Status_property,
  (const JSON_Property*)&_schema_EventService_DeliveryRetryAttempts_property,
  (const JSON_Property*)&_schema_EventService_DeliveryRetryIntervalInSeconds_property,
  (const JSON_Property*)&_schema_EventService_SubscriptionRemovalAction_property,
  (const JSON_Property*)&_schema_EventService_SubscriptionRemovalTimeIntervalInMinutes_property,
  (const JSON_Property*)&_schema_EventService_EventTypesForSubscription_property,
};

static const JSON_EntityType _schema_EventService_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "EventService", /* name */
  NULL, /* baseType */
  _schema_EventService_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_EventService_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ExtendedError_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ExtendedError_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ExtendedError_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ExtendedError_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ExtendedError_Messages_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\010Messages" /* name */
};

static const JSON_Property* _schema_ExtendedError_properties[] =
{
  (const JSON_Property*)&_schema_ExtendedError_Name_property,
  (const JSON_Property*)&_schema_ExtendedError_Modified_property,
  (const JSON_Property*)&_schema_ExtendedError_Description_property,
  (const JSON_Property*)&_schema_ExtendedError_Messages_property,
};

static const JSON_EntityType _schema_ExtendedError_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ExtendedError", /* name */
  NULL, /* baseType */
  _schema_ExtendedError_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ExtendedError_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_extref_entityType
**
*********************************************************************************/

static const JSON_Property _schema_extref_extref_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\006extref" /* name */
};

static const JSON_Property* _schema_extref_properties[] =
{
  (const JSON_Property*)&_schema_extref_extref_property,
};

static const JSON_EntityType _schema_extref_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "extref", /* name */
  NULL, /* baseType */
  _schema_extref_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_extref_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_href_entityType
**
*********************************************************************************/

static const JSON_Property _schema_href_href_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004href" /* name */
};

static const JSON_Property* _schema_href_properties[] =
{
  (const JSON_Property*)&_schema_href_href_property,
};

static const JSON_EntityType _schema_href_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "href", /* name */
  NULL, /* baseType */
  _schema_href_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_href_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ListenerDestination_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ListenerDestination_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ListenerDestination_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ListenerDestination_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_ListenerDestination_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ListenerDestination_Destination_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Destination" /* name */
};

static const JSON_Property _schema_ListenerDestination_HttpHeaders_property =
{
  18, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\013HttpHeaders" /* name */
};

static const JSON_Property _schema_ListenerDestination_EventTypes_property =
{
  40, /* flags */
  JSON_Type_Integer, /* type */
  14, /* index */
  "\012EventTypes" /* name */
};

static const JSON_Property _schema_ListenerDestination_TTLCount_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\010TTLCount" /* name */
};

static const JSON_Property _schema_ListenerDestination_TTLUnits_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  15, /* index */
  "\010TTLUnits" /* name */
};

static const JSON_Property _schema_ListenerDestination_Context_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Context" /* name */
};

static const JSON_Property _schema_ListenerDestination_Protocol_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  16, /* index */
  "\010Protocol" /* name */
};

static const JSON_Property _schema_ListenerDestination_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  11, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_ListenerDestination_properties[] =
{
  (const JSON_Property*)&_schema_ListenerDestination_Name_property,
  (const JSON_Property*)&_schema_ListenerDestination_Modified_property,
  (const JSON_Property*)&_schema_ListenerDestination_Type_property,
  (const JSON_Property*)&_schema_ListenerDestination_Description_property,
  (const JSON_Property*)&_schema_ListenerDestination_Destination_property,
  (const JSON_Property*)&_schema_ListenerDestination_HttpHeaders_property,
  (const JSON_Property*)&_schema_ListenerDestination_EventTypes_property,
  (const JSON_Property*)&_schema_ListenerDestination_TTLCount_property,
  (const JSON_Property*)&_schema_ListenerDestination_TTLUnits_property,
  (const JSON_Property*)&_schema_ListenerDestination_Context_property,
  (const JSON_Property*)&_schema_ListenerDestination_Protocol_property,
  (const JSON_Property*)&_schema_ListenerDestination_links_property,
};

static const JSON_EntityType _schema_ListenerDestination_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ListenerDestination", /* name */
  NULL, /* baseType */
  _schema_ListenerDestination_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ListenerDestination_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_LogEntry_entityType
**
*********************************************************************************/

static const JSON_Property _schema_LogEntry_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_LogEntry_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_LogEntry_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_LogEntry_RecordId_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\010RecordId" /* name */
};

static const JSON_Property _schema_LogEntry_Severity_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  17, /* index */
  "\010Severity" /* name */
};

static const JSON_Property _schema_LogEntry_Created_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Created" /* name */
};

static const JSON_Property _schema_LogEntry_EntryType_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  18, /* index */
  "\011EntryType" /* name */
};

static const JSON_Property _schema_LogEntry_OemRecordFormat_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\017OemRecordFormat" /* name */
};

static const JSON_Property _schema_LogEntry_EntryCode_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  19, /* index */
  "\011EntryCode" /* name */
};

static const JSON_Property _schema_LogEntry_SensorType_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  20, /* index */
  "\012SensorType" /* name */
};

static const JSON_Property _schema_LogEntry_Number_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\006Number" /* name */
};

static const JSON_Property _schema_LogEntry_Message_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Message" /* name */
};

static const JSON_Property _schema_LogEntry_MessageID_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011MessageID" /* name */
};

static const JSON_Property _schema_LogEntry_MessageArgs_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013MessageArgs" /* name */
};

static const JSON_Property _schema_LogEntry_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  12, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_LogEntry_properties[] =
{
  (const JSON_Property*)&_schema_LogEntry_Name_property,
  (const JSON_Property*)&_schema_LogEntry_Modified_property,
  (const JSON_Property*)&_schema_LogEntry_Description_property,
  (const JSON_Property*)&_schema_LogEntry_RecordId_property,
  (const JSON_Property*)&_schema_LogEntry_Severity_property,
  (const JSON_Property*)&_schema_LogEntry_Created_property,
  (const JSON_Property*)&_schema_LogEntry_EntryType_property,
  (const JSON_Property*)&_schema_LogEntry_OemRecordFormat_property,
  (const JSON_Property*)&_schema_LogEntry_EntryCode_property,
  (const JSON_Property*)&_schema_LogEntry_SensorType_property,
  (const JSON_Property*)&_schema_LogEntry_Number_property,
  (const JSON_Property*)&_schema_LogEntry_Message_property,
  (const JSON_Property*)&_schema_LogEntry_MessageID_property,
  (const JSON_Property*)&_schema_LogEntry_MessageArgs_property,
  (const JSON_Property*)&_schema_LogEntry_links_property,
};

static const JSON_EntityType _schema_LogEntry_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "LogEntry", /* name */
  NULL, /* baseType */
  _schema_LogEntry_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_LogEntry_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_LogService_entityType
**
*********************************************************************************/

static const JSON_Property _schema_LogService_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_LogService_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_LogService_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_LogService_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_LogService_MaxNumberOfRecords_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\022MaxNumberOfRecords" /* name */
};

static const JSON_Property _schema_LogService_OverWritePolicy_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  21, /* index */
  "\017OverWritePolicy" /* name */
};

static const JSON_Property _schema_LogService_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_LogService_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  13, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_LogService_properties[] =
{
  (const JSON_Property*)&_schema_LogService_Name_property,
  (const JSON_Property*)&_schema_LogService_Modified_property,
  (const JSON_Property*)&_schema_LogService_Type_property,
  (const JSON_Property*)&_schema_LogService_Description_property,
  (const JSON_Property*)&_schema_LogService_MaxNumberOfRecords_property,
  (const JSON_Property*)&_schema_LogService_OverWritePolicy_property,
  (const JSON_Property*)&_schema_LogService_Status_property,
  (const JSON_Property*)&_schema_LogService_links_property,
};

static const JSON_EntityType _schema_LogService_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "LogService", /* name */
  NULL, /* baseType */
  _schema_LogService_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_LogService_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Redundancy_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Redundancy_ActiveCorrelatableIDs_property =
{
  49, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\025ActiveCorrelatableIDs" /* name */
};

static const JSON_Property _schema_Redundancy_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Redundancy_Mode_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  26, /* index */
  "\004Mode" /* name */
};

static const JSON_Property _schema_Redundancy_MaxNumSupported_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\017MaxNumSupported" /* name */
};

static const JSON_Property _schema_Redundancy_MinNumNeeded_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\014MinNumNeeded" /* name */
};

static const JSON_Property _schema_Redundancy_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property* _schema_Redundancy_properties[] =
{
  (const JSON_Property*)&_schema_Redundancy_ActiveCorrelatableIDs_property,
  (const JSON_Property*)&_schema_Redundancy_Name_property,
  (const JSON_Property*)&_schema_Redundancy_Mode_property,
  (const JSON_Property*)&_schema_Redundancy_MaxNumSupported_property,
  (const JSON_Property*)&_schema_Redundancy_MinNumNeeded_property,
  (const JSON_Property*)&_schema_Redundancy_Status_property,
};

static const JSON_EntityType _schema_Redundancy_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Redundancy", /* name */
  NULL, /* baseType */
  _schema_Redundancy_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Redundancy_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Manager_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Manager_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Manager_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_Manager_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_Manager_ManagerType_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  22, /* index */
  "\013ManagerType" /* name */
};

static const JSON_Property _schema_Manager_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  14, /* index */
  "\005links" /* name */
};

static const JSON_Property _schema_Manager_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_Manager_UUID_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004UUID" /* name */
};

static const JSON_Property _schema_Manager_Model_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005Model" /* name */
};

static const JSON_Property _schema_Manager_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_Manager_Firmware_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  4, /* index */
  "\010Firmware" /* name */
};

static const JSON_Property _schema_Manager_SerialConsole_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  15, /* index */
  "\015SerialConsole" /* name */
};

static const JSON_Property _schema_Manager_CommandShell_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  16, /* index */
  "\014CommandShell" /* name */
};

static const JSON_Property _schema_Manager_GraphicalConsole_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  17, /* index */
  "\020GraphicalConsole" /* name */
};

static const JSON_Property _schema_Manager_Redundancy_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  17, /* index */
  "\012Redundancy" /* name */
};

static const JSON_Property* _schema_Manager_properties[] =
{
  (const JSON_Property*)&_schema_Manager_Name_property,
  (const JSON_Property*)&_schema_Manager_Modified_property,
  (const JSON_Property*)&_schema_Manager_Type_property,
  (const JSON_Property*)&_schema_Manager_ManagerType_property,
  (const JSON_Property*)&_schema_Manager_links_property,
  (const JSON_Property*)&_schema_Manager_Description_property,
  (const JSON_Property*)&_schema_Manager_UUID_property,
  (const JSON_Property*)&_schema_Manager_Model_property,
  (const JSON_Property*)&_schema_Manager_Status_property,
  (const JSON_Property*)&_schema_Manager_Firmware_property,
  (const JSON_Property*)&_schema_Manager_SerialConsole_property,
  (const JSON_Property*)&_schema_Manager_CommandShell_property,
  (const JSON_Property*)&_schema_Manager_GraphicalConsole_property,
  (const JSON_Property*)&_schema_Manager_Redundancy_property,
};

static const JSON_EntityType _schema_Manager_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Manager", /* name */
  NULL, /* baseType */
  _schema_Manager_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Manager_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerAccount_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerAccount_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ManagerAccount_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ManagerAccount_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_ManagerAccount_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ManagerAccount_Password_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Password" /* name */
};

static const JSON_Property _schema_ManagerAccount_UserName_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010UserName" /* name */
};

static const JSON_Property _schema_ManagerAccount_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  18, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_ManagerAccount_properties[] =
{
  (const JSON_Property*)&_schema_ManagerAccount_Name_property,
  (const JSON_Property*)&_schema_ManagerAccount_Modified_property,
  (const JSON_Property*)&_schema_ManagerAccount_Type_property,
  (const JSON_Property*)&_schema_ManagerAccount_Description_property,
  (const JSON_Property*)&_schema_ManagerAccount_Password_property,
  (const JSON_Property*)&_schema_ManagerAccount_UserName_property,
  (const JSON_Property*)&_schema_ManagerAccount_links_property,
};

static const JSON_EntityType _schema_ManagerAccount_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerAccount", /* name */
  NULL, /* baseType */
  _schema_ManagerAccount_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerAccount_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  19, /* index */
  "\005links" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_HostName_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010HostName" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_FQDN_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004FQDN" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SessionTimeoutMinutes_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\025SessionTimeoutMinutes" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_HTTP_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  20, /* index */
  "\004HTTP" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_HTTPS_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  21, /* index */
  "\005HTTPS" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SNMP_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  22, /* index */
  "\004SNMP" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_VirtualMedia_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  23, /* index */
  "\014VirtualMedia" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_Telnet_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  24, /* index */
  "\006Telnet" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSDP_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  25, /* index */
  "\004SSDP" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_IPMI_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  26, /* index */
  "\004IPMI" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSH_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  27, /* index */
  "\003SSH" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_KVMIP_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  28, /* index */
  "\005KVMIP" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_Name_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_Modified_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_Type_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_Description_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_Status_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_links_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_HostName_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_FQDN_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SessionTimeoutMinutes_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_HTTP_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_HTTPS_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SNMP_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_VirtualMedia_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_Telnet_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSDP_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_IPMI_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSH_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_KVMIP_property,
};

static const JSON_EntityType _schema_ManagerNetworkService_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService", /* name */
  NULL, /* baseType */
  _schema_ManagerNetworkService_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_MessageRegistry_entityType
**
*********************************************************************************/

static const JSON_Property _schema_MessageRegistry_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_MessageRegistry_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_MessageRegistry_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_MessageRegistry_Language_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Language" /* name */
};

static const JSON_Property _schema_MessageRegistry_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_MessageRegistry_RegistryPrefix_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016RegistryPrefix" /* name */
};

static const JSON_Property _schema_MessageRegistry_Version_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Version" /* name */
};

static const JSON_Property _schema_MessageRegistry_OwningEntity_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014OwningEntity" /* name */
};

static const JSON_Property _schema_MessageRegistry_Messages_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\010Messages" /* name */
};

static const JSON_Property* _schema_MessageRegistry_properties[] =
{
  (const JSON_Property*)&_schema_MessageRegistry_Name_property,
  (const JSON_Property*)&_schema_MessageRegistry_Modified_property,
  (const JSON_Property*)&_schema_MessageRegistry_Type_property,
  (const JSON_Property*)&_schema_MessageRegistry_Language_property,
  (const JSON_Property*)&_schema_MessageRegistry_Description_property,
  (const JSON_Property*)&_schema_MessageRegistry_RegistryPrefix_property,
  (const JSON_Property*)&_schema_MessageRegistry_Version_property,
  (const JSON_Property*)&_schema_MessageRegistry_OwningEntity_property,
  (const JSON_Property*)&_schema_MessageRegistry_Messages_property,
};

static const JSON_EntityType _schema_MessageRegistry_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "MessageRegistry", /* name */
  NULL, /* baseType */
  _schema_MessageRegistry_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_MessageRegistry_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_MiscMetrics_entityType
**
*********************************************************************************/

static const JSON_Property _schema_MiscMetrics_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_MiscMetrics_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_MiscMetrics_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_MiscMetrics_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_MiscMetrics_Intrusion_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\011Intrusion" /* name */
};

static const JSON_Property _schema_MiscMetrics_Misc_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\004Misc" /* name */
};

static const JSON_Property _schema_MiscMetrics_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  29, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_MiscMetrics_properties[] =
{
  (const JSON_Property*)&_schema_MiscMetrics_Name_property,
  (const JSON_Property*)&_schema_MiscMetrics_Modified_property,
  (const JSON_Property*)&_schema_MiscMetrics_Type_property,
  (const JSON_Property*)&_schema_MiscMetrics_Description_property,
  (const JSON_Property*)&_schema_MiscMetrics_Intrusion_property,
  (const JSON_Property*)&_schema_MiscMetrics_Misc_property,
  (const JSON_Property*)&_schema_MiscMetrics_links_property,
};

static const JSON_EntityType _schema_MiscMetrics_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "MiscMetrics", /* name */
  NULL, /* baseType */
  _schema_MiscMetrics_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_MiscMetrics_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Modified_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Modified_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Modified", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_Name_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Name_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Name", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_Oem_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Oem_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Oem", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_PhysicalContext_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_PhysicalContext_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "PhysicalContext", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_PowerMetrics_entityType
**
*********************************************************************************/

static const JSON_Property _schema_PowerMetrics_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_PowerMetrics_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_PowerMetrics_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_PowerMetrics_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_PowerMetrics_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerConsumedWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\022PowerConsumedWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerRequestedWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\023PowerRequestedWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerAvailableWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\023PowerAvailableWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerCapacityWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\022PowerCapacityWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerAllocatedWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\023PowerAllocatedWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerMetrics_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  30, /* index */
  "\014PowerMetrics" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerLimit_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  31, /* index */
  "\012PowerLimit" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerSupplies_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\015PowerSupplies" /* name */
};

static const JSON_Property _schema_PowerMetrics_Redundancy_property =
{
  36, /* flags */
  JSON_Type_Object, /* type */
  17, /* index */
  "\012Redundancy" /* name */
};

static const JSON_Property _schema_PowerMetrics_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  32, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_PowerMetrics_properties[] =
{
  (const JSON_Property*)&_schema_PowerMetrics_Name_property,
  (const JSON_Property*)&_schema_PowerMetrics_Modified_property,
  (const JSON_Property*)&_schema_PowerMetrics_Type_property,
  (const JSON_Property*)&_schema_PowerMetrics_Description_property,
  (const JSON_Property*)&_schema_PowerMetrics_Status_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerConsumedWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerRequestedWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerAvailableWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerCapacityWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerAllocatedWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerMetrics_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerLimit_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerSupplies_property,
  (const JSON_Property*)&_schema_PowerMetrics_Redundancy_property,
  (const JSON_Property*)&_schema_PowerMetrics_links_property,
};

static const JSON_EntityType _schema_PowerMetrics_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "PowerMetrics", /* name */
  NULL, /* baseType */
  _schema_PowerMetrics_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_PowerMetrics_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Redfish_Schema_Extension_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Redfish_Schema_Extension_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Redfish Schema Extension", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_SchemaFile_entityType
**
*********************************************************************************/

static const JSON_Property _schema_SchemaFile_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_SchemaFile_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_SchemaFile_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_SchemaFile_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_SchemaFile_Languages_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011Languages" /* name */
};

static const JSON_Property _schema_SchemaFile_Schema_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\006Schema" /* name */
};

static const JSON_Property _schema_SchemaFile_Location_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\010Location" /* name */
};

static const JSON_Property _schema_SchemaFile_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  33, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_SchemaFile_properties[] =
{
  (const JSON_Property*)&_schema_SchemaFile_Name_property,
  (const JSON_Property*)&_schema_SchemaFile_Modified_property,
  (const JSON_Property*)&_schema_SchemaFile_Type_property,
  (const JSON_Property*)&_schema_SchemaFile_Description_property,
  (const JSON_Property*)&_schema_SchemaFile_Languages_property,
  (const JSON_Property*)&_schema_SchemaFile_Schema_property,
  (const JSON_Property*)&_schema_SchemaFile_Location_property,
  (const JSON_Property*)&_schema_SchemaFile_links_property,
};

static const JSON_EntityType _schema_SchemaFile_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "SchemaFile", /* name */
  NULL, /* baseType */
  _schema_SchemaFile_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_SchemaFile_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_SerialInterface_entityType
**
*********************************************************************************/

static const JSON_Property _schema_SerialInterface_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_SerialInterface_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_SerialInterface_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_SerialInterface_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_SerialInterface_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_SerialInterface_SignalType_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  29, /* index */
  "\012SignalType" /* name */
};

static const JSON_Property _schema_SerialInterface_BitRate_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  30, /* index */
  "\007BitRate" /* name */
};

static const JSON_Property _schema_SerialInterface_Parity_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  31, /* index */
  "\006Parity" /* name */
};

static const JSON_Property _schema_SerialInterface_DataBits_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  32, /* index */
  "\010DataBits" /* name */
};

static const JSON_Property _schema_SerialInterface_StopBits_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  33, /* index */
  "\010StopBits" /* name */
};

static const JSON_Property _schema_SerialInterface_FlowControl_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  34, /* index */
  "\013FlowControl" /* name */
};

static const JSON_Property _schema_SerialInterface_PinOut_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  35, /* index */
  "\006PinOut" /* name */
};

static const JSON_Property* _schema_SerialInterface_properties[] =
{
  (const JSON_Property*)&_schema_SerialInterface_Name_property,
  (const JSON_Property*)&_schema_SerialInterface_Modified_property,
  (const JSON_Property*)&_schema_SerialInterface_Type_property,
  (const JSON_Property*)&_schema_SerialInterface_Description_property,
  (const JSON_Property*)&_schema_SerialInterface_Status_property,
  (const JSON_Property*)&_schema_SerialInterface_SignalType_property,
  (const JSON_Property*)&_schema_SerialInterface_BitRate_property,
  (const JSON_Property*)&_schema_SerialInterface_Parity_property,
  (const JSON_Property*)&_schema_SerialInterface_DataBits_property,
  (const JSON_Property*)&_schema_SerialInterface_StopBits_property,
  (const JSON_Property*)&_schema_SerialInterface_FlowControl_property,
  (const JSON_Property*)&_schema_SerialInterface_PinOut_property,
};

static const JSON_EntityType _schema_SerialInterface_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "SerialInterface", /* name */
  NULL, /* baseType */
  _schema_SerialInterface_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_SerialInterface_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ServiceRoot_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ServiceRoot_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ServiceRoot_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ServiceRoot_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_ServiceRoot_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ServiceRoot_Time_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Time" /* name */
};

static const JSON_Property _schema_ServiceRoot_ServiceVersion_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016ServiceVersion" /* name */
};

static const JSON_Property _schema_ServiceRoot_UUID_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004UUID" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  34, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_ServiceRoot_properties[] =
{
  (const JSON_Property*)&_schema_ServiceRoot_Name_property,
  (const JSON_Property*)&_schema_ServiceRoot_Modified_property,
  (const JSON_Property*)&_schema_ServiceRoot_Type_property,
  (const JSON_Property*)&_schema_ServiceRoot_Description_property,
  (const JSON_Property*)&_schema_ServiceRoot_Time_property,
  (const JSON_Property*)&_schema_ServiceRoot_ServiceVersion_property,
  (const JSON_Property*)&_schema_ServiceRoot_UUID_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_property,
};

static const JSON_EntityType _schema_ServiceRoot_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ServiceRoot", /* name */
  NULL, /* baseType */
  _schema_ServiceRoot_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ServiceRoot_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Session_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Session_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Session_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_Session_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_Session_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_Session_UserName_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010UserName" /* name */
};

static const JSON_Property _schema_Session_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  35, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_Session_properties[] =
{
  (const JSON_Property*)&_schema_Session_Name_property,
  (const JSON_Property*)&_schema_Session_Modified_property,
  (const JSON_Property*)&_schema_Session_Type_property,
  (const JSON_Property*)&_schema_Session_Description_property,
  (const JSON_Property*)&_schema_Session_UserName_property,
  (const JSON_Property*)&_schema_Session_links_property,
};

static const JSON_EntityType _schema_Session_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Session", /* name */
  NULL, /* baseType */
  _schema_Session_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Session_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_SimpleStorage_entityType
**
*********************************************************************************/

static const JSON_Property _schema_SimpleStorage_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_SimpleStorage_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_SimpleStorage_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_SimpleStorage_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_SimpleStorage_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_SimpleStorage_UefiDevicePath_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016UefiDevicePath" /* name */
};

static const JSON_Property _schema_SimpleStorage_Devices_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\007Devices" /* name */
};

static const JSON_Property* _schema_SimpleStorage_properties[] =
{
  (const JSON_Property*)&_schema_SimpleStorage_Name_property,
  (const JSON_Property*)&_schema_SimpleStorage_Modified_property,
  (const JSON_Property*)&_schema_SimpleStorage_Type_property,
  (const JSON_Property*)&_schema_SimpleStorage_Description_property,
  (const JSON_Property*)&_schema_SimpleStorage_Status_property,
  (const JSON_Property*)&_schema_SimpleStorage_UefiDevicePath_property,
  (const JSON_Property*)&_schema_SimpleStorage_Devices_property,
};

static const JSON_EntityType _schema_SimpleStorage_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "SimpleStorage", /* name */
  NULL, /* baseType */
  _schema_SimpleStorage_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_SimpleStorage_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Task_entityType
**
*********************************************************************************/

static const JSON_Property _schema_Task_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_Task_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_Task_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_Task_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_Task_TaskState_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  36, /* index */
  "\011TaskState" /* name */
};

static const JSON_Property _schema_Task_StartTime_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011StartTime" /* name */
};

static const JSON_Property _schema_Task_EndTime_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007EndTime" /* name */
};

static const JSON_Property _schema_Task_TaskStatus_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  37, /* index */
  "\012TaskStatus" /* name */
};

static const JSON_Property _schema_Task_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  36, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_Task_properties[] =
{
  (const JSON_Property*)&_schema_Task_Name_property,
  (const JSON_Property*)&_schema_Task_Modified_property,
  (const JSON_Property*)&_schema_Task_Type_property,
  (const JSON_Property*)&_schema_Task_Description_property,
  (const JSON_Property*)&_schema_Task_TaskState_property,
  (const JSON_Property*)&_schema_Task_StartTime_property,
  (const JSON_Property*)&_schema_Task_EndTime_property,
  (const JSON_Property*)&_schema_Task_TaskStatus_property,
  (const JSON_Property*)&_schema_Task_links_property,
};

static const JSON_EntityType _schema_Task_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Task", /* name */
  NULL, /* baseType */
  _schema_Task_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Task_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_TaskService_entityType
**
*********************************************************************************/

static const JSON_Property _schema_TaskService_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_TaskService_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_TaskService_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_TaskService_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_TaskService_MaxNumberOfTasks_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\020MaxNumberOfTasks" /* name */
};

static const JSON_Property _schema_TaskService_CompletedTaskOverWritePolicy_property =
{
  8, /* flags */
  JSON_Type_Integer, /* type */
  38, /* index */
  "\034CompletedTaskOverWritePolicy" /* name */
};

static const JSON_Property _schema_TaskService_LifeCycleEventOnTaskStateChange_property =
{
  1, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\037LifeCycleEventOnTaskStateChange" /* name */
};

static const JSON_Property _schema_TaskService_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_TaskService_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  37, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_TaskService_properties[] =
{
  (const JSON_Property*)&_schema_TaskService_Name_property,
  (const JSON_Property*)&_schema_TaskService_Modified_property,
  (const JSON_Property*)&_schema_TaskService_Type_property,
  (const JSON_Property*)&_schema_TaskService_Description_property,
  (const JSON_Property*)&_schema_TaskService_MaxNumberOfTasks_property,
  (const JSON_Property*)&_schema_TaskService_CompletedTaskOverWritePolicy_property,
  (const JSON_Property*)&_schema_TaskService_LifeCycleEventOnTaskStateChange_property,
  (const JSON_Property*)&_schema_TaskService_Status_property,
  (const JSON_Property*)&_schema_TaskService_links_property,
};

static const JSON_EntityType _schema_TaskService_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "TaskService", /* name */
  NULL, /* baseType */
  _schema_TaskService_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_TaskService_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ThermalMetrics_entityType
**
*********************************************************************************/

static const JSON_Property _schema_ThermalMetrics_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Temperatures_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\014Temperatures" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Fans_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\004Fans" /* name */
};

static const JSON_Property _schema_ThermalMetrics_Redundancy_property =
{
  36, /* flags */
  JSON_Type_Object, /* type */
  17, /* index */
  "\012Redundancy" /* name */
};

static const JSON_Property _schema_ThermalMetrics_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  38, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_ThermalMetrics_properties[] =
{
  (const JSON_Property*)&_schema_ThermalMetrics_Name_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Modified_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Type_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Description_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Status_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Temperatures_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Fans_property,
  (const JSON_Property*)&_schema_ThermalMetrics_Redundancy_property,
  (const JSON_Property*)&_schema_ThermalMetrics_links_property,
};

static const JSON_EntityType _schema_ThermalMetrics_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ThermalMetrics", /* name */
  NULL, /* baseType */
  _schema_ThermalMetrics_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ThermalMetrics_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Type_entityType
**
*********************************************************************************/

static const JSON_EntityType _schema_Type_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Type", /* name */
  NULL, /* baseType */
  NULL, /* properties */
  0, /* propertiesSize */
};

/*
**********************************************************************************
** schema_VirtualMedia_entityType
**
*********************************************************************************/

static const JSON_Property _schema_VirtualMedia_Name_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Name" /* name */
};

static const JSON_Property _schema_VirtualMedia_Modified_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Modified" /* name */
};

static const JSON_Property _schema_VirtualMedia_Type_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Type" /* name */
};

static const JSON_Property _schema_VirtualMedia_Description_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013Description" /* name */
};

static const JSON_Property _schema_VirtualMedia_ImageName_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011ImageName" /* name */
};

static const JSON_Property _schema_VirtualMedia_Image_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005Image" /* name */
};

static const JSON_Property _schema_VirtualMedia_MediaTypes_property =
{
  40, /* flags */
  JSON_Type_Integer, /* type */
  39, /* index */
  "\012MediaTypes" /* name */
};

static const JSON_Property _schema_VirtualMedia_ConnectedVia_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  40, /* index */
  "\014ConnectedVia" /* name */
};

static const JSON_Property _schema_VirtualMedia_Inserted_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\010Inserted" /* name */
};

static const JSON_Property _schema_VirtualMedia_WriteProtected_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\016WriteProtected" /* name */
};

static const JSON_Property _schema_VirtualMedia_links_property =
{
  2, /* flags */
  JSON_Type_Object, /* type */
  39, /* index */
  "\005links" /* name */
};

static const JSON_Property* _schema_VirtualMedia_properties[] =
{
  (const JSON_Property*)&_schema_VirtualMedia_Name_property,
  (const JSON_Property*)&_schema_VirtualMedia_Modified_property,
  (const JSON_Property*)&_schema_VirtualMedia_Type_property,
  (const JSON_Property*)&_schema_VirtualMedia_Description_property,
  (const JSON_Property*)&_schema_VirtualMedia_ImageName_property,
  (const JSON_Property*)&_schema_VirtualMedia_Image_property,
  (const JSON_Property*)&_schema_VirtualMedia_MediaTypes_property,
  (const JSON_Property*)&_schema_VirtualMedia_ConnectedVia_property,
  (const JSON_Property*)&_schema_VirtualMedia_Inserted_property,
  (const JSON_Property*)&_schema_VirtualMedia_WriteProtected_property,
  (const JSON_Property*)&_schema_VirtualMedia_links_property,
};

static const JSON_EntityType _schema_VirtualMedia_entityType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "VirtualMedia", /* name */
  NULL, /* baseType */
  _schema_VirtualMedia_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_VirtualMedia_properties), /* propertiesSize */
};

static const JSON_EntityType* _schema_entityTypes[] =
{
  (const JSON_EntityType*)&_schema_AccountService_entityType,
  (const JSON_EntityType*)&_schema_Status_entityType,
  (const JSON_EntityType*)&_schema_Chassis_entityType,
  (const JSON_EntityType*)&_schema_Collection_entityType,
  (const JSON_EntityType*)&_schema_FwRev_entityType,
  (const JSON_EntityType*)&_schema_ComputerSystem_entityType,
  (const JSON_EntityType*)&_schema_Description_entityType,
  (const JSON_EntityType*)&_schema_Settings_entityType,
  (const JSON_EntityType*)&_schema_EthernetNetworkInterface_entityType,
  (const JSON_EntityType*)&_schema_Event_entityType,
  (const JSON_EntityType*)&_schema_EventService_entityType,
  (const JSON_EntityType*)&_schema_ExtendedError_entityType,
  (const JSON_EntityType*)&_schema_extref_entityType,
  (const JSON_EntityType*)&_schema_href_entityType,
  (const JSON_EntityType*)&_schema_ListenerDestination_entityType,
  (const JSON_EntityType*)&_schema_LogEntry_entityType,
  (const JSON_EntityType*)&_schema_LogService_entityType,
  (const JSON_EntityType*)&_schema_Redundancy_entityType,
  (const JSON_EntityType*)&_schema_Manager_entityType,
  (const JSON_EntityType*)&_schema_ManagerAccount_entityType,
  (const JSON_EntityType*)&_schema_ManagerNetworkService_entityType,
  (const JSON_EntityType*)&_schema_MessageRegistry_entityType,
  (const JSON_EntityType*)&_schema_MiscMetrics_entityType,
  (const JSON_EntityType*)&_schema_Modified_entityType,
  (const JSON_EntityType*)&_schema_Name_entityType,
  (const JSON_EntityType*)&_schema_Oem_entityType,
  (const JSON_EntityType*)&_schema_PhysicalContext_entityType,
  (const JSON_EntityType*)&_schema_PowerMetrics_entityType,
  (const JSON_EntityType*)&_schema_Redfish_Schema_Extension_entityType,
  (const JSON_EntityType*)&_schema_SchemaFile_entityType,
  (const JSON_EntityType*)&_schema_SerialInterface_entityType,
  (const JSON_EntityType*)&_schema_ServiceRoot_entityType,
  (const JSON_EntityType*)&_schema_Session_entityType,
  (const JSON_EntityType*)&_schema_SimpleStorage_entityType,
  (const JSON_EntityType*)&_schema_Task_entityType,
  (const JSON_EntityType*)&_schema_TaskService_entityType,
  (const JSON_EntityType*)&_schema_ThermalMetrics_entityType,
  (const JSON_EntityType*)&_schema_Type_entityType,
  (const JSON_EntityType*)&_schema_VirtualMedia_entityType,
};

/*
**********************************************************************************
** _schema_Status_State_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Status_State_Enabled_member =
{
  "\007Enabled", /* name */
  0, /* value */
};

static const JSON_Member _schema_Status_State_Disabled_member =
{
  "\010Disabled", /* name */
  1, /* value */
};

static const JSON_Member _schema_Status_State_Offline_member =
{
  "\007Offline", /* name */
  2, /* value */
};

static const JSON_Member _schema_Status_State_InTest_member =
{
  "\006InTest", /* name */
  3, /* value */
};

static const JSON_Member _schema_Status_State_Starting_member =
{
  "\010Starting", /* name */
  4, /* value */
};

static const JSON_Member _schema_Status_State_Absent_member =
{
  "\006Absent", /* name */
  5, /* value */
};

static const JSON_Member* _schema_Status_State_members[] =
{
  &_schema_Status_State_Enabled_member,
  &_schema_Status_State_Disabled_member,
  &_schema_Status_State_Offline_member,
  &_schema_Status_State_InTest_member,
  &_schema_Status_State_Starting_member,
  &_schema_Status_State_Absent_member,
};

static const JSON_EnumType _schema_Status_State_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Status_State_members), /* membersSize */
  "\014Status.State", /* name */
  _schema_Status_State_members /* members */
};

/*
**********************************************************************************
** _schema_Status_HealthRollUp_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Status_HealthRollUp_OK_member =
{
  "\002OK", /* name */
  0, /* value */
};

static const JSON_Member _schema_Status_HealthRollUp_Warning_member =
{
  "\007Warning", /* name */
  1, /* value */
};

static const JSON_Member _schema_Status_HealthRollUp_Critical_member =
{
  "\010Critical", /* name */
  2, /* value */
};

static const JSON_Member* _schema_Status_HealthRollUp_members[] =
{
  &_schema_Status_HealthRollUp_OK_member,
  &_schema_Status_HealthRollUp_Warning_member,
  &_schema_Status_HealthRollUp_Critical_member,
};

static const JSON_EnumType _schema_Status_HealthRollUp_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Status_HealthRollUp_members), /* membersSize */
  "\023Status.HealthRollUp", /* name */
  _schema_Status_HealthRollUp_members /* members */
};

/*
**********************************************************************************
** _schema_Status_Health_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Status_Health_OK_member =
{
  "\002OK", /* name */
  0, /* value */
};

static const JSON_Member _schema_Status_Health_Warning_member =
{
  "\007Warning", /* name */
  1, /* value */
};

static const JSON_Member _schema_Status_Health_Critical_member =
{
  "\010Critical", /* name */
  2, /* value */
};

static const JSON_Member* _schema_Status_Health_members[] =
{
  &_schema_Status_Health_OK_member,
  &_schema_Status_Health_Warning_member,
  &_schema_Status_Health_Critical_member,
};

static const JSON_EnumType _schema_Status_Health_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Status_Health_members), /* membersSize */
  "\015Status.Health", /* name */
  _schema_Status_Health_members /* members */
};

/*
**********************************************************************************
** _schema_Chassis_ChassisType_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Chassis_ChassisType_Rack_member =
{
  "\004Rack", /* name */
  0, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Blade_member =
{
  "\005Blade", /* name */
  1, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Enclosure_member =
{
  "\011Enclosure", /* name */
  2, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_StandAlone_member =
{
  "\012StandAlone", /* name */
  3, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_RackMount_member =
{
  "\011RackMount", /* name */
  4, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Card_member =
{
  "\004Card", /* name */
  5, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Cartridge_member =
{
  "\011Cartridge", /* name */
  6, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Row_member =
{
  "\003Row", /* name */
  7, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Pod_member =
{
  "\003Pod", /* name */
  8, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Expansion_member =
{
  "\011Expansion", /* name */
  9, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Sidecar_member =
{
  "\007Sidecar", /* name */
  10, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Zone_member =
{
  "\004Zone", /* name */
  11, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Sled_member =
{
  "\004Sled", /* name */
  12, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Shelf_member =
{
  "\005Shelf", /* name */
  13, /* value */
};

static const JSON_Member _schema_Chassis_ChassisType_Other_member =
{
  "\005Other", /* name */
  14, /* value */
};

static const JSON_Member* _schema_Chassis_ChassisType_members[] =
{
  &_schema_Chassis_ChassisType_Rack_member,
  &_schema_Chassis_ChassisType_Blade_member,
  &_schema_Chassis_ChassisType_Enclosure_member,
  &_schema_Chassis_ChassisType_StandAlone_member,
  &_schema_Chassis_ChassisType_RackMount_member,
  &_schema_Chassis_ChassisType_Card_member,
  &_schema_Chassis_ChassisType_Cartridge_member,
  &_schema_Chassis_ChassisType_Row_member,
  &_schema_Chassis_ChassisType_Pod_member,
  &_schema_Chassis_ChassisType_Expansion_member,
  &_schema_Chassis_ChassisType_Sidecar_member,
  &_schema_Chassis_ChassisType_Zone_member,
  &_schema_Chassis_ChassisType_Sled_member,
  &_schema_Chassis_ChassisType_Shelf_member,
  &_schema_Chassis_ChassisType_Other_member,
};

static const JSON_EnumType _schema_Chassis_ChassisType_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Chassis_ChassisType_members), /* membersSize */
  "\023Chassis.ChassisType", /* name */
  _schema_Chassis_ChassisType_members /* members */
};

/*
**********************************************************************************
** _schema_Chassis_IndicatorLED_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Chassis_IndicatorLED_Unknown_member =
{
  "\007Unknown", /* name */
  0, /* value */
};

static const JSON_Member _schema_Chassis_IndicatorLED_Lit_member =
{
  "\003Lit", /* name */
  1, /* value */
};

static const JSON_Member _schema_Chassis_IndicatorLED_Blinking_member =
{
  "\010Blinking", /* name */
  2, /* value */
};

static const JSON_Member _schema_Chassis_IndicatorLED_Off_member =
{
  "\003Off", /* name */
  3, /* value */
};

static const JSON_Member* _schema_Chassis_IndicatorLED_members[] =
{
  &_schema_Chassis_IndicatorLED_Unknown_member,
  &_schema_Chassis_IndicatorLED_Lit_member,
  &_schema_Chassis_IndicatorLED_Blinking_member,
  &_schema_Chassis_IndicatorLED_Off_member,
};

static const JSON_EnumType _schema_Chassis_IndicatorLED_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Chassis_IndicatorLED_members), /* membersSize */
  "\024Chassis.IndicatorLED", /* name */
  _schema_Chassis_IndicatorLED_members /* members */
};

/*
**********************************************************************************
** _schema_ComputerSystem_SystemType_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ComputerSystem_SystemType_Physical_member =
{
  "\010Physical", /* name */
  0, /* value */
};

static const JSON_Member _schema_ComputerSystem_SystemType_Virtual_member =
{
  "\007Virtual", /* name */
  1, /* value */
};

static const JSON_Member _schema_ComputerSystem_SystemType_OS_member =
{
  "\002OS", /* name */
  2, /* value */
};

static const JSON_Member _schema_ComputerSystem_SystemType_PhysicallyPartitioned_member =
{
  "\025PhysicallyPartitioned", /* name */
  3, /* value */
};

static const JSON_Member _schema_ComputerSystem_SystemType_VirtuallyPartitioned_member =
{
  "\024VirtuallyPartitioned", /* name */
  4, /* value */
};

static const JSON_Member* _schema_ComputerSystem_SystemType_members[] =
{
  &_schema_ComputerSystem_SystemType_Physical_member,
  &_schema_ComputerSystem_SystemType_Virtual_member,
  &_schema_ComputerSystem_SystemType_OS_member,
  &_schema_ComputerSystem_SystemType_PhysicallyPartitioned_member,
  &_schema_ComputerSystem_SystemType_VirtuallyPartitioned_member,
};

static const JSON_EnumType _schema_ComputerSystem_SystemType_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_SystemType_members), /* membersSize */
  "\031ComputerSystem.SystemType", /* name */
  _schema_ComputerSystem_SystemType_members /* members */
};

/*
**********************************************************************************
** _schema_ComputerSystem_IndicatorLED_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ComputerSystem_IndicatorLED_Unknown_member =
{
  "\007Unknown", /* name */
  0, /* value */
};

static const JSON_Member _schema_ComputerSystem_IndicatorLED_Lit_member =
{
  "\003Lit", /* name */
  1, /* value */
};

static const JSON_Member _schema_ComputerSystem_IndicatorLED_Blinking_member =
{
  "\010Blinking", /* name */
  2, /* value */
};

static const JSON_Member _schema_ComputerSystem_IndicatorLED_Off_member =
{
  "\003Off", /* name */
  3, /* value */
};

static const JSON_Member* _schema_ComputerSystem_IndicatorLED_members[] =
{
  &_schema_ComputerSystem_IndicatorLED_Unknown_member,
  &_schema_ComputerSystem_IndicatorLED_Lit_member,
  &_schema_ComputerSystem_IndicatorLED_Blinking_member,
  &_schema_ComputerSystem_IndicatorLED_Off_member,
};

static const JSON_EnumType _schema_ComputerSystem_IndicatorLED_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_IndicatorLED_members), /* membersSize */
  "\033ComputerSystem.IndicatorLED", /* name */
  _schema_ComputerSystem_IndicatorLED_members /* members */
};

/*
**********************************************************************************
** _schema_ComputerSystem_Power_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ComputerSystem_Power_On_member =
{
  "\002On", /* name */
  0, /* value */
};

static const JSON_Member _schema_ComputerSystem_Power_Off_member =
{
  "\003Off", /* name */
  1, /* value */
};

static const JSON_Member _schema_ComputerSystem_Power_Unknown_member =
{
  "\007Unknown", /* name */
  2, /* value */
};

static const JSON_Member _schema_ComputerSystem_Power_Reset_member =
{
  "\005Reset", /* name */
  3, /* value */
};

static const JSON_Member* _schema_ComputerSystem_Power_members[] =
{
  &_schema_ComputerSystem_Power_On_member,
  &_schema_ComputerSystem_Power_Off_member,
  &_schema_ComputerSystem_Power_Unknown_member,
  &_schema_ComputerSystem_Power_Reset_member,
};

static const JSON_EnumType _schema_ComputerSystem_Power_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Power_members), /* membersSize */
  "\024ComputerSystem.Power", /* name */
  _schema_ComputerSystem_Power_members /* members */
};

/*
**********************************************************************************
** _schema_ComputerSystem_Boot_BootSourceOverrideTarget_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_None_member =
{
  "\004None", /* name */
  0, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Pxe_member =
{
  "\003Pxe", /* name */
  1, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Floppy_member =
{
  "\006Floppy", /* name */
  2, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Cd_member =
{
  "\002Cd", /* name */
  3, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Usb_member =
{
  "\003Usb", /* name */
  4, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Hdd_member =
{
  "\003Hdd", /* name */
  5, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_BiosSetup_member =
{
  "\011BiosSetup", /* name */
  6, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Utilities_member =
{
  "\011Utilities", /* name */
  7, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_Diags_member =
{
  "\005Diags", /* name */
  8, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_UefiShell_member =
{
  "\011UefiShell", /* name */
  9, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideTarget_UefiTarget_member =
{
  "\012UefiTarget", /* name */
  10, /* value */
};

static const JSON_Member* _schema_ComputerSystem_Boot_BootSourceOverrideTarget_members[] =
{
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_None_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Pxe_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Floppy_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Cd_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Usb_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Hdd_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_BiosSetup_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Utilities_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_Diags_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_UefiShell_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideTarget_UefiTarget_member,
};

static const JSON_EnumType _schema_ComputerSystem_Boot_BootSourceOverrideTarget_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Boot_BootSourceOverrideTarget_members), /* membersSize */
  "\054ComputerSystem.Boot.BootSourceOverrideTarget", /* name */
  _schema_ComputerSystem_Boot_BootSourceOverrideTarget_members /* members */
};

/*
**********************************************************************************
** _schema_ComputerSystem_Boot_BootSourceOverrideSupported_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_None_member =
{
  "\004None", /* name */
  0, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Pxe_member =
{
  "\003Pxe", /* name */
  1, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Floppy_member =
{
  "\006Floppy", /* name */
  2, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Cd_member =
{
  "\002Cd", /* name */
  3, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Usb_member =
{
  "\003Usb", /* name */
  4, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Hdd_member =
{
  "\003Hdd", /* name */
  5, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_BiosSetup_member =
{
  "\011BiosSetup", /* name */
  6, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Utilities_member =
{
  "\011Utilities", /* name */
  7, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_Diags_member =
{
  "\005Diags", /* name */
  8, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_UefiShell_member =
{
  "\011UefiShell", /* name */
  9, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideSupported_UefiTarget_member =
{
  "\012UefiTarget", /* name */
  10, /* value */
};

static const JSON_Member* _schema_ComputerSystem_Boot_BootSourceOverrideSupported_members[] =
{
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_None_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Pxe_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Floppy_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Cd_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Usb_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Hdd_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_BiosSetup_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Utilities_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_Diags_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_UefiShell_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideSupported_UefiTarget_member,
};

static const JSON_EnumType _schema_ComputerSystem_Boot_BootSourceOverrideSupported_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Boot_BootSourceOverrideSupported_members), /* membersSize */
  "\057ComputerSystem.Boot.BootSourceOverrideSupported", /* name */
  _schema_ComputerSystem_Boot_BootSourceOverrideSupported_members /* members */
};

/*
**********************************************************************************
** _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_Disabled_member =
{
  "\010Disabled", /* name */
  0, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_Once_member =
{
  "\004Once", /* name */
  1, /* value */
};

static const JSON_Member _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_Continuous_member =
{
  "\012Continuous", /* name */
  2, /* value */
};

static const JSON_Member* _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_members[] =
{
  &_schema_ComputerSystem_Boot_BootSourceOverrideEnabled_Disabled_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideEnabled_Once_member,
  &_schema_ComputerSystem_Boot_BootSourceOverrideEnabled_Continuous_member,
};

static const JSON_EnumType _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Boot_BootSourceOverrideEnabled_members), /* membersSize */
  "\055ComputerSystem.Boot.BootSourceOverrideEnabled", /* name */
  _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_members /* members */
};

/*
**********************************************************************************
** _schema_EthernetNetworkInterface_LinkTechnology_enumType
**
*********************************************************************************/

static const JSON_Member _schema_EthernetNetworkInterface_LinkTechnology_Ethernet_member =
{
  "\010Ethernet", /* name */
  0, /* value */
};

static const JSON_Member* _schema_EthernetNetworkInterface_LinkTechnology_members[] =
{
  &_schema_EthernetNetworkInterface_LinkTechnology_Ethernet_member,
};

static const JSON_EnumType _schema_EthernetNetworkInterface_LinkTechnology_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_EthernetNetworkInterface_LinkTechnology_members), /* membersSize */
  "\047EthernetNetworkInterface.LinkTechnology", /* name */
  _schema_EthernetNetworkInterface_LinkTechnology_members /* members */
};

/*
**********************************************************************************
** _schema_EventService_SubscriptionRemovalAction_enumType
**
*********************************************************************************/

static const JSON_Member _schema_EventService_SubscriptionRemovalAction_Remove_member =
{
  "\006Remove", /* name */
  0, /* value */
};

static const JSON_Member _schema_EventService_SubscriptionRemovalAction_Disable_member =
{
  "\007Disable", /* name */
  1, /* value */
};

static const JSON_Member _schema_EventService_SubscriptionRemovalAction_Ignore_member =
{
  "\006Ignore", /* name */
  2, /* value */
};

static const JSON_Member* _schema_EventService_SubscriptionRemovalAction_members[] =
{
  &_schema_EventService_SubscriptionRemovalAction_Remove_member,
  &_schema_EventService_SubscriptionRemovalAction_Disable_member,
  &_schema_EventService_SubscriptionRemovalAction_Ignore_member,
};

static const JSON_EnumType _schema_EventService_SubscriptionRemovalAction_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_EventService_SubscriptionRemovalAction_members), /* membersSize */
  "\046EventService.SubscriptionRemovalAction", /* name */
  _schema_EventService_SubscriptionRemovalAction_members /* members */
};

/*
**********************************************************************************
** _schema_EventService_EventTypesForSubscription_enumType
**
*********************************************************************************/

static const JSON_Member _schema_EventService_EventTypesForSubscription_StatusChange_member =
{
  "\014StatusChange", /* name */
  0, /* value */
};

static const JSON_Member _schema_EventService_EventTypesForSubscription_ResourceUpdated_member =
{
  "\017ResourceUpdated", /* name */
  1, /* value */
};

static const JSON_Member _schema_EventService_EventTypesForSubscription_ResourceAdded_member =
{
  "\015ResourceAdded", /* name */
  2, /* value */
};

static const JSON_Member _schema_EventService_EventTypesForSubscription_ResourceRemoved_member =
{
  "\017ResourceRemoved", /* name */
  3, /* value */
};

static const JSON_Member _schema_EventService_EventTypesForSubscription_Alert_member =
{
  "\005Alert", /* name */
  4, /* value */
};

static const JSON_Member* _schema_EventService_EventTypesForSubscription_members[] =
{
  &_schema_EventService_EventTypesForSubscription_StatusChange_member,
  &_schema_EventService_EventTypesForSubscription_ResourceUpdated_member,
  &_schema_EventService_EventTypesForSubscription_ResourceAdded_member,
  &_schema_EventService_EventTypesForSubscription_ResourceRemoved_member,
  &_schema_EventService_EventTypesForSubscription_Alert_member,
};

static const JSON_EnumType _schema_EventService_EventTypesForSubscription_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_EventService_EventTypesForSubscription_members), /* membersSize */
  "\046EventService.EventTypesForSubscription", /* name */
  _schema_EventService_EventTypesForSubscription_members /* members */
};

/*
**********************************************************************************
** _schema_ListenerDestination_EventTypes_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ListenerDestination_EventTypes_StatusChange_member =
{
  "\014StatusChange", /* name */
  0, /* value */
};

static const JSON_Member _schema_ListenerDestination_EventTypes_ResourceUpdated_member =
{
  "\017ResourceUpdated", /* name */
  1, /* value */
};

static const JSON_Member _schema_ListenerDestination_EventTypes_ResourceAdded_member =
{
  "\015ResourceAdded", /* name */
  2, /* value */
};

static const JSON_Member _schema_ListenerDestination_EventTypes_ResourceRemoved_member =
{
  "\017ResourceRemoved", /* name */
  3, /* value */
};

static const JSON_Member _schema_ListenerDestination_EventTypes_Alert_member =
{
  "\005Alert", /* name */
  4, /* value */
};

static const JSON_Member* _schema_ListenerDestination_EventTypes_members[] =
{
  &_schema_ListenerDestination_EventTypes_StatusChange_member,
  &_schema_ListenerDestination_EventTypes_ResourceUpdated_member,
  &_schema_ListenerDestination_EventTypes_ResourceAdded_member,
  &_schema_ListenerDestination_EventTypes_ResourceRemoved_member,
  &_schema_ListenerDestination_EventTypes_Alert_member,
};

static const JSON_EnumType _schema_ListenerDestination_EventTypes_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ListenerDestination_EventTypes_members), /* membersSize */
  "\036ListenerDestination.EventTypes", /* name */
  _schema_ListenerDestination_EventTypes_members /* members */
};

/*
**********************************************************************************
** _schema_ListenerDestination_TTLUnits_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ListenerDestination_TTLUnits_seconds_member =
{
  "\007seconds", /* name */
  0, /* value */
};

static const JSON_Member _schema_ListenerDestination_TTLUnits_minutes_member =
{
  "\007minutes", /* name */
  1, /* value */
};

static const JSON_Member _schema_ListenerDestination_TTLUnits_days_member =
{
  "\004days", /* name */
  2, /* value */
};

static const JSON_Member* _schema_ListenerDestination_TTLUnits_members[] =
{
  &_schema_ListenerDestination_TTLUnits_seconds_member,
  &_schema_ListenerDestination_TTLUnits_minutes_member,
  &_schema_ListenerDestination_TTLUnits_days_member,
};

static const JSON_EnumType _schema_ListenerDestination_TTLUnits_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ListenerDestination_TTLUnits_members), /* membersSize */
  "\034ListenerDestination.TTLUnits", /* name */
  _schema_ListenerDestination_TTLUnits_members /* members */
};

/*
**********************************************************************************
** _schema_ListenerDestination_Protocol_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ListenerDestination_Protocol_Redfish_member =
{
  "\007Redfish", /* name */
  0, /* value */
};

static const JSON_Member* _schema_ListenerDestination_Protocol_members[] =
{
  &_schema_ListenerDestination_Protocol_Redfish_member,
};

static const JSON_EnumType _schema_ListenerDestination_Protocol_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ListenerDestination_Protocol_members), /* membersSize */
  "\034ListenerDestination.Protocol", /* name */
  _schema_ListenerDestination_Protocol_members /* members */
};

/*
**********************************************************************************
** _schema_LogEntry_Severity_enumType
**
*********************************************************************************/

static const JSON_Member _schema_LogEntry_Severity_OK_member =
{
  "\002OK", /* name */
  0, /* value */
};

static const JSON_Member _schema_LogEntry_Severity_Warning_member =
{
  "\007Warning", /* name */
  1, /* value */
};

static const JSON_Member _schema_LogEntry_Severity_Critical_member =
{
  "\010Critical", /* name */
  2, /* value */
};

static const JSON_Member* _schema_LogEntry_Severity_members[] =
{
  &_schema_LogEntry_Severity_OK_member,
  &_schema_LogEntry_Severity_Warning_member,
  &_schema_LogEntry_Severity_Critical_member,
};

static const JSON_EnumType _schema_LogEntry_Severity_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_LogEntry_Severity_members), /* membersSize */
  "\021LogEntry.Severity", /* name */
  _schema_LogEntry_Severity_members /* members */
};

/*
**********************************************************************************
** _schema_LogEntry_EntryType_enumType
**
*********************************************************************************/

static const JSON_Member _schema_LogEntry_EntryType_Event_member =
{
  "\005Event", /* name */
  0, /* value */
};

static const JSON_Member _schema_LogEntry_EntryType_SEL_member =
{
  "\003SEL", /* name */
  1, /* value */
};

static const JSON_Member _schema_LogEntry_EntryType_Oem_member =
{
  "\003Oem", /* name */
  2, /* value */
};

static const JSON_Member* _schema_LogEntry_EntryType_members[] =
{
  &_schema_LogEntry_EntryType_Event_member,
  &_schema_LogEntry_EntryType_SEL_member,
  &_schema_LogEntry_EntryType_Oem_member,
};

static const JSON_EnumType _schema_LogEntry_EntryType_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_LogEntry_EntryType_members), /* membersSize */
  "\022LogEntry.EntryType", /* name */
  _schema_LogEntry_EntryType_members /* members */
};

/*
**********************************************************************************
** _schema_LogEntry_EntryCode_enumType
**
*********************************************************************************/

static const JSON_Member _schema_LogEntry_EntryCode_Assert_member =
{
  "\006Assert", /* name */
  0, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Deassert_member =
{
  "\010Deassert", /* name */
  1, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Lower_Non_critical___going_low_member =
{
  "\036Lower_Non_critical___going_low", /* name */
  2, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Lower_Non_critical___going_high_member =
{
  "\037Lower_Non_critical___going_high", /* name */
  3, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Lower_Critical___going_low_member =
{
  "\032Lower_Critical___going_low", /* name */
  4, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Lower_Critical___going_high_member =
{
  "\033Lower_Critical___going_high", /* name */
  5, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Lower_Non_recoverable___going_low_member =
{
  "\041Lower_Non_recoverable___going_low", /* name */
  6, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Lower_Non_recoverable___going_high_member =
{
  "\042Lower_Non_recoverable___going_high", /* name */
  7, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Upper_Non_critical___going_low_member =
{
  "\036Upper_Non_critical___going_low", /* name */
  8, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Upper_Non_critical___going_high_member =
{
  "\037Upper_Non_critical___going_high", /* name */
  9, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Upper_Critical___going_low_member =
{
  "\032Upper_Critical___going_low", /* name */
  10, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Upper_Critical___going_high_member =
{
  "\033Upper_Critical___going_high", /* name */
  11, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Upper_Non_recoverable___going_low_member =
{
  "\041Upper_Non_recoverable___going_low", /* name */
  12, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Upper_Non_recoverable___going_high_member =
{
  "\042Upper_Non_recoverable___going_high", /* name */
  13, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Idle_member =
{
  "\022Transition_to_Idle", /* name */
  14, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Active_member =
{
  "\024Transition_to_Active", /* name */
  15, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Busy_member =
{
  "\022Transition_to_Busy", /* name */
  16, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_State_Deasserted_member =
{
  "\020State_Deasserted", /* name */
  17, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_State_Asserted_member =
{
  "\016State_Asserted", /* name */
  18, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Predictive_Failure_deasserted_member =
{
  "\035Predictive_Failure_deasserted", /* name */
  19, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Predictive_Failure_asserted_member =
{
  "\033Predictive_Failure_asserted", /* name */
  20, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Limit_Not_Exceeded_member =
{
  "\022Limit_Not_Exceeded", /* name */
  21, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Limit_Exceeded_member =
{
  "\016Limit_Exceeded", /* name */
  22, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Performance_Met_member =
{
  "\017Performance_Met", /* name */
  23, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Performance_Lags_member =
{
  "\020Performance_Lags", /* name */
  24, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_OK_member =
{
  "\020Transition_to_OK", /* name */
  25, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Non_Critical_from_OK_member =
{
  "\042Transition_to_Non_Critical_from_OK", /* name */
  26, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Critical_from_less_severe_member =
{
  "\047Transition_to_Critical_from_less_severe", /* name */
  27, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Non_recoverable_from_less_severe_member =
{
  "\056Transition_to_Non_recoverable_from_less_severe", /* name */
  28, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Non_Critical_from_more_severe_member =
{
  "\053Transition_to_Non_Critical_from_more_severe", /* name */
  29, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Critical_from_Non_recoverable_member =
{
  "\053Transition_to_Critical_from_Non_recoverable", /* name */
  30, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Non_recoverable_member =
{
  "\035Transition_to_Non_recoverable", /* name */
  31, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Monitor_member =
{
  "\007Monitor", /* name */
  32, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Informational_member =
{
  "\015Informational", /* name */
  33, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Device_Removed___Device_Absent_member =
{
  "\036Device_Removed___Device_Absent", /* name */
  34, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Device_Inserted___Device_Present_member =
{
  "\040Device_Inserted___Device_Present", /* name */
  35, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Device_Disabled_member =
{
  "\017Device_Disabled", /* name */
  36, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Device_Enabled_member =
{
  "\016Device_Enabled", /* name */
  37, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Running_member =
{
  "\025Transition_to_Running", /* name */
  38, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_In_Test_member =
{
  "\025Transition_to_In_Test", /* name */
  39, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Power_Off_member =
{
  "\027Transition_to_Power_Off", /* name */
  40, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_On_Line_member =
{
  "\025Transition_to_On_Line", /* name */
  41, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Off_Line_member =
{
  "\026Transition_to_Off_Line", /* name */
  42, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Off_Duty_member =
{
  "\026Transition_to_Off_Duty", /* name */
  43, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Degraded_member =
{
  "\026Transition_to_Degraded", /* name */
  44, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Transition_to_Power_Save_member =
{
  "\030Transition_to_Power_Save", /* name */
  45, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Install_Error_member =
{
  "\015Install_Error", /* name */
  46, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Fully_Redundant_member =
{
  "\017Fully_Redundant", /* name */
  47, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Redundancy_Lost_member =
{
  "\017Redundancy_Lost", /* name */
  48, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Redundancy_Degraded_member =
{
  "\023Redundancy_Degraded", /* name */
  49, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Non_redundant_Sufficient_Resources_from_Redundant_member =
{
  "\061Non_redundant_Sufficient_Resources_from_Redundant", /* name */
  50, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Non_redundant_Sufficient_Resources_from_Insufficient_Resources_member =
{
  "\076Non_redundant_Sufficient_Resources_from_Insufficient_Resources", /* name */
  51, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Non_redundant_Insufficient_Resources_member =
{
  "\044Non_redundant_Insufficient_Resources", /* name */
  52, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Redundancy_Degraded_from_Fully_Redundant_member =
{
  "\050Redundancy_Degraded_from_Fully_Redundant", /* name */
  53, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_Redundancy_Degraded_from_Non_redundant_member =
{
  "\046Redundancy_Degraded_from_Non_redundant", /* name */
  54, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_D0_Power_State_member =
{
  "\016D0_Power_State", /* name */
  55, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_D1_Power_State_member =
{
  "\016D1_Power_State", /* name */
  56, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_D2_Power_State_member =
{
  "\016D2_Power_State", /* name */
  57, /* value */
};

static const JSON_Member _schema_LogEntry_EntryCode_D3_Power_State_member =
{
  "\016D3_Power_State", /* name */
  58, /* value */
};

static const JSON_Member* _schema_LogEntry_EntryCode_members[] =
{
  &_schema_LogEntry_EntryCode_Assert_member,
  &_schema_LogEntry_EntryCode_Deassert_member,
  &_schema_LogEntry_EntryCode_Lower_Non_critical___going_low_member,
  &_schema_LogEntry_EntryCode_Lower_Non_critical___going_high_member,
  &_schema_LogEntry_EntryCode_Lower_Critical___going_low_member,
  &_schema_LogEntry_EntryCode_Lower_Critical___going_high_member,
  &_schema_LogEntry_EntryCode_Lower_Non_recoverable___going_low_member,
  &_schema_LogEntry_EntryCode_Lower_Non_recoverable___going_high_member,
  &_schema_LogEntry_EntryCode_Upper_Non_critical___going_low_member,
  &_schema_LogEntry_EntryCode_Upper_Non_critical___going_high_member,
  &_schema_LogEntry_EntryCode_Upper_Critical___going_low_member,
  &_schema_LogEntry_EntryCode_Upper_Critical___going_high_member,
  &_schema_LogEntry_EntryCode_Upper_Non_recoverable___going_low_member,
  &_schema_LogEntry_EntryCode_Upper_Non_recoverable___going_high_member,
  &_schema_LogEntry_EntryCode_Transition_to_Idle_member,
  &_schema_LogEntry_EntryCode_Transition_to_Active_member,
  &_schema_LogEntry_EntryCode_Transition_to_Busy_member,
  &_schema_LogEntry_EntryCode_State_Deasserted_member,
  &_schema_LogEntry_EntryCode_State_Asserted_member,
  &_schema_LogEntry_EntryCode_Predictive_Failure_deasserted_member,
  &_schema_LogEntry_EntryCode_Predictive_Failure_asserted_member,
  &_schema_LogEntry_EntryCode_Limit_Not_Exceeded_member,
  &_schema_LogEntry_EntryCode_Limit_Exceeded_member,
  &_schema_LogEntry_EntryCode_Performance_Met_member,
  &_schema_LogEntry_EntryCode_Performance_Lags_member,
  &_schema_LogEntry_EntryCode_Transition_to_OK_member,
  &_schema_LogEntry_EntryCode_Transition_to_Non_Critical_from_OK_member,
  &_schema_LogEntry_EntryCode_Transition_to_Critical_from_less_severe_member,
  &_schema_LogEntry_EntryCode_Transition_to_Non_recoverable_from_less_severe_member,
  &_schema_LogEntry_EntryCode_Transition_to_Non_Critical_from_more_severe_member,
  &_schema_LogEntry_EntryCode_Transition_to_Critical_from_Non_recoverable_member,
  &_schema_LogEntry_EntryCode_Transition_to_Non_recoverable_member,
  &_schema_LogEntry_EntryCode_Monitor_member,
  &_schema_LogEntry_EntryCode_Informational_member,
  &_schema_LogEntry_EntryCode_Device_Removed___Device_Absent_member,
  &_schema_LogEntry_EntryCode_Device_Inserted___Device_Present_member,
  &_schema_LogEntry_EntryCode_Device_Disabled_member,
  &_schema_LogEntry_EntryCode_Device_Enabled_member,
  &_schema_LogEntry_EntryCode_Transition_to_Running_member,
  &_schema_LogEntry_EntryCode_Transition_to_In_Test_member,
  &_schema_LogEntry_EntryCode_Transition_to_Power_Off_member,
  &_schema_LogEntry_EntryCode_Transition_to_On_Line_member,
  &_schema_LogEntry_EntryCode_Transition_to_Off_Line_member,
  &_schema_LogEntry_EntryCode_Transition_to_Off_Duty_member,
  &_schema_LogEntry_EntryCode_Transition_to_Degraded_member,
  &_schema_LogEntry_EntryCode_Transition_to_Power_Save_member,
  &_schema_LogEntry_EntryCode_Install_Error_member,
  &_schema_LogEntry_EntryCode_Fully_Redundant_member,
  &_schema_LogEntry_EntryCode_Redundancy_Lost_member,
  &_schema_LogEntry_EntryCode_Redundancy_Degraded_member,
  &_schema_LogEntry_EntryCode_Non_redundant_Sufficient_Resources_from_Redundant_member,
  &_schema_LogEntry_EntryCode_Non_redundant_Sufficient_Resources_from_Insufficient_Resources_member,
  &_schema_LogEntry_EntryCode_Non_redundant_Insufficient_Resources_member,
  &_schema_LogEntry_EntryCode_Redundancy_Degraded_from_Fully_Redundant_member,
  &_schema_LogEntry_EntryCode_Redundancy_Degraded_from_Non_redundant_member,
  &_schema_LogEntry_EntryCode_D0_Power_State_member,
  &_schema_LogEntry_EntryCode_D1_Power_State_member,
  &_schema_LogEntry_EntryCode_D2_Power_State_member,
  &_schema_LogEntry_EntryCode_D3_Power_State_member,
};

static const JSON_EnumType _schema_LogEntry_EntryCode_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_LogEntry_EntryCode_members), /* membersSize */
  "\022LogEntry.EntryCode", /* name */
  _schema_LogEntry_EntryCode_members /* members */
};

/*
**********************************************************************************
** _schema_LogEntry_SensorType_enumType
**
*********************************************************************************/

static const JSON_Member _schema_LogEntry_SensorType_Temperature_member =
{
  "\013Temperature", /* name */
  0, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Voltage_member =
{
  "\007Voltage", /* name */
  1, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Current_member =
{
  "\007Current", /* name */
  2, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Fan_member =
{
  "\003Fan", /* name */
  3, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Physical_Chassis__Security_member =
{
  "\032Physical_Chassis__Security", /* name */
  4, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Platform_Security_Violation_Attempt_member =
{
  "\043Platform_Security_Violation_Attempt", /* name */
  5, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Processor_member =
{
  "\011Processor", /* name */
  6, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Power_Supply___Converter_member =
{
  "\030Power_Supply___Converter", /* name */
  7, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_PowerUnit_member =
{
  "\011PowerUnit", /* name */
  8, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_CoolingDevice_member =
{
  "\015CoolingDevice", /* name */
  9, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Other_Units_based_Sensor_member =
{
  "\030Other_Units_based_Sensor", /* name */
  10, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Memory_member =
{
  "\006Memory", /* name */
  11, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Drive_Slot_Bay_member =
{
  "\016Drive_Slot_Bay", /* name */
  12, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_POST_Memory_Resize_member =
{
  "\022POST_Memory_Resize", /* name */
  13, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_System_Firmware_Progress_member =
{
  "\030System_Firmware_Progress", /* name */
  14, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Event_Logging_Disabled_member =
{
  "\026Event_Logging_Disabled", /* name */
  15, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_System_Event_member =
{
  "\014System_Event", /* name */
  16, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Critical_Interrupt_member =
{
  "\022Critical_Interrupt", /* name */
  17, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Button_Switch_member =
{
  "\015Button_Switch", /* name */
  18, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Module_Board_member =
{
  "\014Module_Board", /* name */
  19, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Microcontroller_Coprocessor_member =
{
  "\033Microcontroller_Coprocessor", /* name */
  20, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Add_in_Card_member =
{
  "\013Add_in_Card", /* name */
  21, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Chassis_member =
{
  "\007Chassis", /* name */
  22, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_ChipSet_member =
{
  "\007ChipSet", /* name */
  23, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Other_FRU_member =
{
  "\011Other_FRU", /* name */
  24, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Cable_Interconnect_member =
{
  "\022Cable_Interconnect", /* name */
  25, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Terminator_member =
{
  "\012Terminator", /* name */
  26, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_SystemBoot_Restart_member =
{
  "\022SystemBoot_Restart", /* name */
  27, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Boot_Error_member =
{
  "\012Boot_Error", /* name */
  28, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_BaseOSBoot_InstallationStatus_member =
{
  "\035BaseOSBoot_InstallationStatus", /* name */
  29, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_OS_Stop_Shutdown_member =
{
  "\020OS_Stop_Shutdown", /* name */
  30, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Slot_Connector_member =
{
  "\016Slot_Connector", /* name */
  31, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_System_ACPI_PowerState_member =
{
  "\026System_ACPI_PowerState", /* name */
  32, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Watchdog_member =
{
  "\010Watchdog", /* name */
  33, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Platform_Alert_member =
{
  "\016Platform_Alert", /* name */
  34, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Entity_Presence_member =
{
  "\017Entity_Presence", /* name */
  35, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Monitor_ASIC_IC_member =
{
  "\017Monitor_ASIC_IC", /* name */
  36, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_LAN_member =
{
  "\003LAN", /* name */
  37, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Management_Subsystem_Health_member =
{
  "\033Management_Subsystem_Health", /* name */
  38, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Battery_member =
{
  "\007Battery", /* name */
  39, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Session_Audit_member =
{
  "\015Session_Audit", /* name */
  40, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_Version_Change_member =
{
  "\016Version_Change", /* name */
  41, /* value */
};

static const JSON_Member _schema_LogEntry_SensorType_FRUState_member =
{
  "\010FRUState", /* name */
  42, /* value */
};

static const JSON_Member* _schema_LogEntry_SensorType_members[] =
{
  &_schema_LogEntry_SensorType_Temperature_member,
  &_schema_LogEntry_SensorType_Voltage_member,
  &_schema_LogEntry_SensorType_Current_member,
  &_schema_LogEntry_SensorType_Fan_member,
  &_schema_LogEntry_SensorType_Physical_Chassis__Security_member,
  &_schema_LogEntry_SensorType_Platform_Security_Violation_Attempt_member,
  &_schema_LogEntry_SensorType_Processor_member,
  &_schema_LogEntry_SensorType_Power_Supply___Converter_member,
  &_schema_LogEntry_SensorType_PowerUnit_member,
  &_schema_LogEntry_SensorType_CoolingDevice_member,
  &_schema_LogEntry_SensorType_Other_Units_based_Sensor_member,
  &_schema_LogEntry_SensorType_Memory_member,
  &_schema_LogEntry_SensorType_Drive_Slot_Bay_member,
  &_schema_LogEntry_SensorType_POST_Memory_Resize_member,
  &_schema_LogEntry_SensorType_System_Firmware_Progress_member,
  &_schema_LogEntry_SensorType_Event_Logging_Disabled_member,
  &_schema_LogEntry_SensorType_System_Event_member,
  &_schema_LogEntry_SensorType_Critical_Interrupt_member,
  &_schema_LogEntry_SensorType_Button_Switch_member,
  &_schema_LogEntry_SensorType_Module_Board_member,
  &_schema_LogEntry_SensorType_Microcontroller_Coprocessor_member,
  &_schema_LogEntry_SensorType_Add_in_Card_member,
  &_schema_LogEntry_SensorType_Chassis_member,
  &_schema_LogEntry_SensorType_ChipSet_member,
  &_schema_LogEntry_SensorType_Other_FRU_member,
  &_schema_LogEntry_SensorType_Cable_Interconnect_member,
  &_schema_LogEntry_SensorType_Terminator_member,
  &_schema_LogEntry_SensorType_SystemBoot_Restart_member,
  &_schema_LogEntry_SensorType_Boot_Error_member,
  &_schema_LogEntry_SensorType_BaseOSBoot_InstallationStatus_member,
  &_schema_LogEntry_SensorType_OS_Stop_Shutdown_member,
  &_schema_LogEntry_SensorType_Slot_Connector_member,
  &_schema_LogEntry_SensorType_System_ACPI_PowerState_member,
  &_schema_LogEntry_SensorType_Watchdog_member,
  &_schema_LogEntry_SensorType_Platform_Alert_member,
  &_schema_LogEntry_SensorType_Entity_Presence_member,
  &_schema_LogEntry_SensorType_Monitor_ASIC_IC_member,
  &_schema_LogEntry_SensorType_LAN_member,
  &_schema_LogEntry_SensorType_Management_Subsystem_Health_member,
  &_schema_LogEntry_SensorType_Battery_member,
  &_schema_LogEntry_SensorType_Session_Audit_member,
  &_schema_LogEntry_SensorType_Version_Change_member,
  &_schema_LogEntry_SensorType_FRUState_member,
};

static const JSON_EnumType _schema_LogEntry_SensorType_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_LogEntry_SensorType_members), /* membersSize */
  "\023LogEntry.SensorType", /* name */
  _schema_LogEntry_SensorType_members /* members */
};

/*
**********************************************************************************
** _schema_LogService_OverWritePolicy_enumType
**
*********************************************************************************/

static const JSON_Member _schema_LogService_OverWritePolicy_Unknown_member =
{
  "\007Unknown", /* name */
  0, /* value */
};

static const JSON_Member _schema_LogService_OverWritePolicy_WrapsWhenFull_member =
{
  "\015WrapsWhenFull", /* name */
  1, /* value */
};

static const JSON_Member _schema_LogService_OverWritePolicy_NeverOverwrites_member =
{
  "\017NeverOverwrites", /* name */
  2, /* value */
};

static const JSON_Member* _schema_LogService_OverWritePolicy_members[] =
{
  &_schema_LogService_OverWritePolicy_Unknown_member,
  &_schema_LogService_OverWritePolicy_WrapsWhenFull_member,
  &_schema_LogService_OverWritePolicy_NeverOverwrites_member,
};

static const JSON_EnumType _schema_LogService_OverWritePolicy_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_LogService_OverWritePolicy_members), /* membersSize */
  "\032LogService.OverWritePolicy", /* name */
  _schema_LogService_OverWritePolicy_members /* members */
};

/*
**********************************************************************************
** _schema_Manager_ManagerType_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Manager_ManagerType_ManagementController_member =
{
  "\024ManagementController", /* name */
  0, /* value */
};

static const JSON_Member _schema_Manager_ManagerType_EnclosureManager_member =
{
  "\020EnclosureManager", /* name */
  1, /* value */
};

static const JSON_Member _schema_Manager_ManagerType_BMC_member =
{
  "\003BMC", /* name */
  2, /* value */
};

static const JSON_Member* _schema_Manager_ManagerType_members[] =
{
  &_schema_Manager_ManagerType_ManagementController_member,
  &_schema_Manager_ManagerType_EnclosureManager_member,
  &_schema_Manager_ManagerType_BMC_member,
};

static const JSON_EnumType _schema_Manager_ManagerType_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Manager_ManagerType_members), /* membersSize */
  "\023Manager.ManagerType", /* name */
  _schema_Manager_ManagerType_members /* members */
};

/*
**********************************************************************************
** _schema_Manager_SerialConsole_ConnectTypesSupported_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Manager_SerialConsole_ConnectTypesSupported_SSH_member =
{
  "\003SSH", /* name */
  0, /* value */
};

static const JSON_Member _schema_Manager_SerialConsole_ConnectTypesSupported_Telnet_member =
{
  "\006Telnet", /* name */
  1, /* value */
};

static const JSON_Member _schema_Manager_SerialConsole_ConnectTypesSupported_IPMI_member =
{
  "\004IPMI", /* name */
  2, /* value */
};

static const JSON_Member _schema_Manager_SerialConsole_ConnectTypesSupported_Oem_member =
{
  "\003Oem", /* name */
  3, /* value */
};

static const JSON_Member* _schema_Manager_SerialConsole_ConnectTypesSupported_members[] =
{
  &_schema_Manager_SerialConsole_ConnectTypesSupported_SSH_member,
  &_schema_Manager_SerialConsole_ConnectTypesSupported_Telnet_member,
  &_schema_Manager_SerialConsole_ConnectTypesSupported_IPMI_member,
  &_schema_Manager_SerialConsole_ConnectTypesSupported_Oem_member,
};

static const JSON_EnumType _schema_Manager_SerialConsole_ConnectTypesSupported_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Manager_SerialConsole_ConnectTypesSupported_members), /* membersSize */
  "\053Manager.SerialConsole.ConnectTypesSupported", /* name */
  _schema_Manager_SerialConsole_ConnectTypesSupported_members /* members */
};

/*
**********************************************************************************
** _schema_Manager_CommandShell_ConnectTypesSupported_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Manager_CommandShell_ConnectTypesSupported_SSH_member =
{
  "\003SSH", /* name */
  0, /* value */
};

static const JSON_Member _schema_Manager_CommandShell_ConnectTypesSupported_Telnet_member =
{
  "\006Telnet", /* name */
  1, /* value */
};

static const JSON_Member _schema_Manager_CommandShell_ConnectTypesSupported_IPMI_member =
{
  "\004IPMI", /* name */
  2, /* value */
};

static const JSON_Member _schema_Manager_CommandShell_ConnectTypesSupported_Oem_member =
{
  "\003Oem", /* name */
  3, /* value */
};

static const JSON_Member* _schema_Manager_CommandShell_ConnectTypesSupported_members[] =
{
  &_schema_Manager_CommandShell_ConnectTypesSupported_SSH_member,
  &_schema_Manager_CommandShell_ConnectTypesSupported_Telnet_member,
  &_schema_Manager_CommandShell_ConnectTypesSupported_IPMI_member,
  &_schema_Manager_CommandShell_ConnectTypesSupported_Oem_member,
};

static const JSON_EnumType _schema_Manager_CommandShell_ConnectTypesSupported_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Manager_CommandShell_ConnectTypesSupported_members), /* membersSize */
  "\052Manager.CommandShell.ConnectTypesSupported", /* name */
  _schema_Manager_CommandShell_ConnectTypesSupported_members /* members */
};

/*
**********************************************************************************
** _schema_Manager_GraphicalConsole_ConnectTypesSupported_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Manager_GraphicalConsole_ConnectTypesSupported_KVMIP_member =
{
  "\005KVMIP", /* name */
  0, /* value */
};

static const JSON_Member _schema_Manager_GraphicalConsole_ConnectTypesSupported_Oem_member =
{
  "\003Oem", /* name */
  1, /* value */
};

static const JSON_Member* _schema_Manager_GraphicalConsole_ConnectTypesSupported_members[] =
{
  &_schema_Manager_GraphicalConsole_ConnectTypesSupported_KVMIP_member,
  &_schema_Manager_GraphicalConsole_ConnectTypesSupported_Oem_member,
};

static const JSON_EnumType _schema_Manager_GraphicalConsole_ConnectTypesSupported_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Manager_GraphicalConsole_ConnectTypesSupported_members), /* membersSize */
  "\056Manager.GraphicalConsole.ConnectTypesSupported", /* name */
  _schema_Manager_GraphicalConsole_ConnectTypesSupported_members /* members */
};

/*
**********************************************************************************
** _schema_Redundancy_Mode_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Redundancy_Mode_Failover_member =
{
  "\010Failover", /* name */
  0, /* value */
};

static const JSON_Member _schema_Redundancy_Mode_N_1_member =
{
  "\003N_1", /* name */
  1, /* value */
};

static const JSON_Member _schema_Redundancy_Mode_LoadBalanced_member =
{
  "\014LoadBalanced", /* name */
  2, /* value */
};

static const JSON_Member _schema_Redundancy_Mode_Sparing_member =
{
  "\007Sparing", /* name */
  3, /* value */
};

static const JSON_Member _schema_Redundancy_Mode_LimitedSparing_member =
{
  "\016LimitedSparing", /* name */
  4, /* value */
};

static const JSON_Member* _schema_Redundancy_Mode_members[] =
{
  &_schema_Redundancy_Mode_Failover_member,
  &_schema_Redundancy_Mode_N_1_member,
  &_schema_Redundancy_Mode_LoadBalanced_member,
  &_schema_Redundancy_Mode_Sparing_member,
  &_schema_Redundancy_Mode_LimitedSparing_member,
};

static const JSON_EnumType _schema_Redundancy_Mode_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Redundancy_Mode_members), /* membersSize */
  "\017Redundancy.Mode", /* name */
  _schema_Redundancy_Mode_members /* members */
};

/*
**********************************************************************************
** _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_enumType
**
*********************************************************************************/

static const JSON_Member _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_Link_member =
{
  "\004Link", /* name */
  0, /* value */
};

static const JSON_Member _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_Site_member =
{
  "\004Site", /* name */
  1, /* value */
};

static const JSON_Member _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_Organization_member =
{
  "\014Organization", /* name */
  2, /* value */
};

static const JSON_Member* _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_members[] =
{
  &_schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_Link_member,
  &_schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_Site_member,
  &_schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_Organization_member,
};

static const JSON_EnumType _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_members), /* membersSize */
  "\052ManagerNetworkService.SSDP.NotifyIPv6Scope", /* name */
  _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_members /* members */
};

/*
**********************************************************************************
** _schema_PowerMetrics_PowerLimit_LimitException_enumType
**
*********************************************************************************/

static const JSON_Member _schema_PowerMetrics_PowerLimit_LimitException_NoAction_member =
{
  "\010NoAction", /* name */
  0, /* value */
};

static const JSON_Member _schema_PowerMetrics_PowerLimit_LimitException_HardPowerOff_member =
{
  "\014HardPowerOff", /* name */
  1, /* value */
};

static const JSON_Member _schema_PowerMetrics_PowerLimit_LimitException_LogEventOnly_member =
{
  "\014LogEventOnly", /* name */
  2, /* value */
};

static const JSON_Member _schema_PowerMetrics_PowerLimit_LimitException_Oem_member =
{
  "\003Oem", /* name */
  3, /* value */
};

static const JSON_Member* _schema_PowerMetrics_PowerLimit_LimitException_members[] =
{
  &_schema_PowerMetrics_PowerLimit_LimitException_NoAction_member,
  &_schema_PowerMetrics_PowerLimit_LimitException_HardPowerOff_member,
  &_schema_PowerMetrics_PowerLimit_LimitException_LogEventOnly_member,
  &_schema_PowerMetrics_PowerLimit_LimitException_Oem_member,
};

static const JSON_EnumType _schema_PowerMetrics_PowerLimit_LimitException_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_PowerMetrics_PowerLimit_LimitException_members), /* membersSize */
  "\046PowerMetrics.PowerLimit.LimitException", /* name */
  _schema_PowerMetrics_PowerLimit_LimitException_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_SignalType_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_SignalType_Rs232_member =
{
  "\005Rs232", /* name */
  0, /* value */
};

static const JSON_Member _schema_SerialInterface_SignalType_Rs485_member =
{
  "\005Rs485", /* name */
  1, /* value */
};

static const JSON_Member* _schema_SerialInterface_SignalType_members[] =
{
  &_schema_SerialInterface_SignalType_Rs232_member,
  &_schema_SerialInterface_SignalType_Rs485_member,
};

static const JSON_EnumType _schema_SerialInterface_SignalType_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_SignalType_members), /* membersSize */
  "\032SerialInterface.SignalType", /* name */
  _schema_SerialInterface_SignalType_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_BitRate_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_BitRate_T1200_member =
{
  "\005T1200", /* name */
  1200, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T2400_member =
{
  "\005T2400", /* name */
  2400, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T4800_member =
{
  "\005T4800", /* name */
  4800, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T9600_member =
{
  "\005T9600", /* name */
  9600, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T19200_member =
{
  "\006T19200", /* name */
  19200, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T38400_member =
{
  "\006T38400", /* name */
  38400, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T57600_member =
{
  "\006T57600", /* name */
  57600, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T115200_member =
{
  "\007T115200", /* name */
  115200, /* value */
};

static const JSON_Member _schema_SerialInterface_BitRate_T230400_member =
{
  "\007T230400", /* name */
  230400, /* value */
};

static const JSON_Member* _schema_SerialInterface_BitRate_members[] =
{
  &_schema_SerialInterface_BitRate_T1200_member,
  &_schema_SerialInterface_BitRate_T2400_member,
  &_schema_SerialInterface_BitRate_T4800_member,
  &_schema_SerialInterface_BitRate_T9600_member,
  &_schema_SerialInterface_BitRate_T19200_member,
  &_schema_SerialInterface_BitRate_T38400_member,
  &_schema_SerialInterface_BitRate_T57600_member,
  &_schema_SerialInterface_BitRate_T115200_member,
  &_schema_SerialInterface_BitRate_T230400_member,
};

static const JSON_EnumType _schema_SerialInterface_BitRate_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_BitRate_members), /* membersSize */
  "\027SerialInterface.BitRate", /* name */
  _schema_SerialInterface_BitRate_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_Parity_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_Parity_None_member =
{
  "\004None", /* name */
  0, /* value */
};

static const JSON_Member _schema_SerialInterface_Parity_Even_member =
{
  "\004Even", /* name */
  1, /* value */
};

static const JSON_Member _schema_SerialInterface_Parity_Odd_member =
{
  "\003Odd", /* name */
  2, /* value */
};

static const JSON_Member _schema_SerialInterface_Parity_Mark_member =
{
  "\004Mark", /* name */
  3, /* value */
};

static const JSON_Member _schema_SerialInterface_Parity_Space_member =
{
  "\005Space", /* name */
  4, /* value */
};

static const JSON_Member* _schema_SerialInterface_Parity_members[] =
{
  &_schema_SerialInterface_Parity_None_member,
  &_schema_SerialInterface_Parity_Even_member,
  &_schema_SerialInterface_Parity_Odd_member,
  &_schema_SerialInterface_Parity_Mark_member,
  &_schema_SerialInterface_Parity_Space_member,
};

static const JSON_EnumType _schema_SerialInterface_Parity_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_Parity_members), /* membersSize */
  "\026SerialInterface.Parity", /* name */
  _schema_SerialInterface_Parity_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_DataBits_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_DataBits_T5_member =
{
  "\002T5", /* name */
  5, /* value */
};

static const JSON_Member _schema_SerialInterface_DataBits_T6_member =
{
  "\002T6", /* name */
  6, /* value */
};

static const JSON_Member _schema_SerialInterface_DataBits_T7_member =
{
  "\002T7", /* name */
  7, /* value */
};

static const JSON_Member _schema_SerialInterface_DataBits_T8_member =
{
  "\002T8", /* name */
  8, /* value */
};

static const JSON_Member* _schema_SerialInterface_DataBits_members[] =
{
  &_schema_SerialInterface_DataBits_T5_member,
  &_schema_SerialInterface_DataBits_T6_member,
  &_schema_SerialInterface_DataBits_T7_member,
  &_schema_SerialInterface_DataBits_T8_member,
};

static const JSON_EnumType _schema_SerialInterface_DataBits_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_DataBits_members), /* membersSize */
  "\030SerialInterface.DataBits", /* name */
  _schema_SerialInterface_DataBits_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_StopBits_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_StopBits_T1_member =
{
  "\002T1", /* name */
  1, /* value */
};

static const JSON_Member _schema_SerialInterface_StopBits_T2_member =
{
  "\002T2", /* name */
  2, /* value */
};

static const JSON_Member* _schema_SerialInterface_StopBits_members[] =
{
  &_schema_SerialInterface_StopBits_T1_member,
  &_schema_SerialInterface_StopBits_T2_member,
};

static const JSON_EnumType _schema_SerialInterface_StopBits_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_StopBits_members), /* membersSize */
  "\030SerialInterface.StopBits", /* name */
  _schema_SerialInterface_StopBits_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_FlowControl_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_FlowControl_None_member =
{
  "\004None", /* name */
  0, /* value */
};

static const JSON_Member _schema_SerialInterface_FlowControl_Software_member =
{
  "\010Software", /* name */
  1, /* value */
};

static const JSON_Member _schema_SerialInterface_FlowControl_Hardware_member =
{
  "\010Hardware", /* name */
  2, /* value */
};

static const JSON_Member* _schema_SerialInterface_FlowControl_members[] =
{
  &_schema_SerialInterface_FlowControl_None_member,
  &_schema_SerialInterface_FlowControl_Software_member,
  &_schema_SerialInterface_FlowControl_Hardware_member,
};

static const JSON_EnumType _schema_SerialInterface_FlowControl_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_FlowControl_members), /* membersSize */
  "\033SerialInterface.FlowControl", /* name */
  _schema_SerialInterface_FlowControl_members /* members */
};

/*
**********************************************************************************
** _schema_SerialInterface_PinOut_enumType
**
*********************************************************************************/

static const JSON_Member _schema_SerialInterface_PinOut_Cisco_member =
{
  "\005Cisco", /* name */
  0, /* value */
};

static const JSON_Member _schema_SerialInterface_PinOut_Cyclades_member =
{
  "\010Cyclades", /* name */
  1, /* value */
};

static const JSON_Member _schema_SerialInterface_PinOut_Digi_member =
{
  "\004Digi", /* name */
  2, /* value */
};

static const JSON_Member* _schema_SerialInterface_PinOut_members[] =
{
  &_schema_SerialInterface_PinOut_Cisco_member,
  &_schema_SerialInterface_PinOut_Cyclades_member,
  &_schema_SerialInterface_PinOut_Digi_member,
};

static const JSON_EnumType _schema_SerialInterface_PinOut_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_SerialInterface_PinOut_members), /* membersSize */
  "\026SerialInterface.PinOut", /* name */
  _schema_SerialInterface_PinOut_members /* members */
};

/*
**********************************************************************************
** _schema_Task_TaskState_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Task_TaskState_New_member =
{
  "\003New", /* name */
  0, /* value */
};

static const JSON_Member _schema_Task_TaskState_Starting_member =
{
  "\010Starting", /* name */
  1, /* value */
};

static const JSON_Member _schema_Task_TaskState_Running_member =
{
  "\007Running", /* name */
  2, /* value */
};

static const JSON_Member _schema_Task_TaskState_Suspended_member =
{
  "\011Suspended", /* name */
  3, /* value */
};

static const JSON_Member _schema_Task_TaskState_Interrupted_member =
{
  "\013Interrupted", /* name */
  4, /* value */
};

static const JSON_Member _schema_Task_TaskState_Pending_member =
{
  "\007Pending", /* name */
  5, /* value */
};

static const JSON_Member _schema_Task_TaskState_Stopping_member =
{
  "\010Stopping", /* name */
  6, /* value */
};

static const JSON_Member _schema_Task_TaskState_Completed_member =
{
  "\011Completed", /* name */
  7, /* value */
};

static const JSON_Member _schema_Task_TaskState_Killed_member =
{
  "\006Killed", /* name */
  8, /* value */
};

static const JSON_Member _schema_Task_TaskState_Exception_member =
{
  "\011Exception", /* name */
  9, /* value */
};

static const JSON_Member _schema_Task_TaskState_Service_member =
{
  "\007Service", /* name */
  10, /* value */
};

static const JSON_Member* _schema_Task_TaskState_members[] =
{
  &_schema_Task_TaskState_New_member,
  &_schema_Task_TaskState_Starting_member,
  &_schema_Task_TaskState_Running_member,
  &_schema_Task_TaskState_Suspended_member,
  &_schema_Task_TaskState_Interrupted_member,
  &_schema_Task_TaskState_Pending_member,
  &_schema_Task_TaskState_Stopping_member,
  &_schema_Task_TaskState_Completed_member,
  &_schema_Task_TaskState_Killed_member,
  &_schema_Task_TaskState_Exception_member,
  &_schema_Task_TaskState_Service_member,
};

static const JSON_EnumType _schema_Task_TaskState_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Task_TaskState_members), /* membersSize */
  "\016Task.TaskState", /* name */
  _schema_Task_TaskState_members /* members */
};

/*
**********************************************************************************
** _schema_Task_TaskStatus_enumType
**
*********************************************************************************/

static const JSON_Member _schema_Task_TaskStatus_OK_member =
{
  "\002OK", /* name */
  0, /* value */
};

static const JSON_Member _schema_Task_TaskStatus_Warning_member =
{
  "\007Warning", /* name */
  1, /* value */
};

static const JSON_Member _schema_Task_TaskStatus_Critical_member =
{
  "\010Critical", /* name */
  2, /* value */
};

static const JSON_Member* _schema_Task_TaskStatus_members[] =
{
  &_schema_Task_TaskStatus_OK_member,
  &_schema_Task_TaskStatus_Warning_member,
  &_schema_Task_TaskStatus_Critical_member,
};

static const JSON_EnumType _schema_Task_TaskStatus_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_Task_TaskStatus_members), /* membersSize */
  "\017Task.TaskStatus", /* name */
  _schema_Task_TaskStatus_members /* members */
};

/*
**********************************************************************************
** _schema_TaskService_CompletedTaskOverWritePolicy_enumType
**
*********************************************************************************/

static const JSON_Member _schema_TaskService_CompletedTaskOverWritePolicy_Manual_member =
{
  "\006Manual", /* name */
  0, /* value */
};

static const JSON_Member _schema_TaskService_CompletedTaskOverWritePolicy_Oldest_member =
{
  "\006Oldest", /* name */
  1, /* value */
};

static const JSON_Member* _schema_TaskService_CompletedTaskOverWritePolicy_members[] =
{
  &_schema_TaskService_CompletedTaskOverWritePolicy_Manual_member,
  &_schema_TaskService_CompletedTaskOverWritePolicy_Oldest_member,
};

static const JSON_EnumType _schema_TaskService_CompletedTaskOverWritePolicy_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_TaskService_CompletedTaskOverWritePolicy_members), /* membersSize */
  "\050TaskService.CompletedTaskOverWritePolicy", /* name */
  _schema_TaskService_CompletedTaskOverWritePolicy_members /* members */
};

/*
**********************************************************************************
** _schema_VirtualMedia_MediaTypes_enumType
**
*********************************************************************************/

static const JSON_Member _schema_VirtualMedia_MediaTypes_CD_member =
{
  "\002CD", /* name */
  0, /* value */
};

static const JSON_Member _schema_VirtualMedia_MediaTypes_Floppy_member =
{
  "\006Floppy", /* name */
  1, /* value */
};

static const JSON_Member _schema_VirtualMedia_MediaTypes_USBStick_member =
{
  "\010USBStick", /* name */
  2, /* value */
};

static const JSON_Member _schema_VirtualMedia_MediaTypes_DVD_member =
{
  "\003DVD", /* name */
  3, /* value */
};

static const JSON_Member* _schema_VirtualMedia_MediaTypes_members[] =
{
  &_schema_VirtualMedia_MediaTypes_CD_member,
  &_schema_VirtualMedia_MediaTypes_Floppy_member,
  &_schema_VirtualMedia_MediaTypes_USBStick_member,
  &_schema_VirtualMedia_MediaTypes_DVD_member,
};

static const JSON_EnumType _schema_VirtualMedia_MediaTypes_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_VirtualMedia_MediaTypes_members), /* membersSize */
  "\027VirtualMedia.MediaTypes", /* name */
  _schema_VirtualMedia_MediaTypes_members /* members */
};

/*
**********************************************************************************
** _schema_VirtualMedia_ConnectedVia_enumType
**
*********************************************************************************/

static const JSON_Member _schema_VirtualMedia_ConnectedVia_NotConnected_member =
{
  "\014NotConnected", /* name */
  0, /* value */
};

static const JSON_Member _schema_VirtualMedia_ConnectedVia_URI_member =
{
  "\003URI", /* name */
  1, /* value */
};

static const JSON_Member _schema_VirtualMedia_ConnectedVia_Applet_member =
{
  "\006Applet", /* name */
  2, /* value */
};

static const JSON_Member* _schema_VirtualMedia_ConnectedVia_members[] =
{
  &_schema_VirtualMedia_ConnectedVia_NotConnected_member,
  &_schema_VirtualMedia_ConnectedVia_URI_member,
  &_schema_VirtualMedia_ConnectedVia_Applet_member,
};

static const JSON_EnumType _schema_VirtualMedia_ConnectedVia_enumType =
{
  0, /* flags */
  JSON_Type_Integer, /* underlyingType */
  ODATA_ARRAYSIZE(_schema_VirtualMedia_ConnectedVia_members), /* membersSize */
  "\031VirtualMedia.ConnectedVia", /* name */
  _schema_VirtualMedia_ConnectedVia_members /* members */
};

static const JSON_EnumType* _schema_enumTypes[] =
{
  (const JSON_EnumType*)&_schema_Status_State_enumType,
  (const JSON_EnumType*)&_schema_Status_HealthRollUp_enumType,
  (const JSON_EnumType*)&_schema_Status_Health_enumType,
  (const JSON_EnumType*)&_schema_Chassis_ChassisType_enumType,
  (const JSON_EnumType*)&_schema_Chassis_IndicatorLED_enumType,
  (const JSON_EnumType*)&_schema_ComputerSystem_SystemType_enumType,
  (const JSON_EnumType*)&_schema_ComputerSystem_IndicatorLED_enumType,
  (const JSON_EnumType*)&_schema_ComputerSystem_Power_enumType,
  (const JSON_EnumType*)&_schema_ComputerSystem_Boot_BootSourceOverrideTarget_enumType,
  (const JSON_EnumType*)&_schema_ComputerSystem_Boot_BootSourceOverrideSupported_enumType,
  (const JSON_EnumType*)&_schema_ComputerSystem_Boot_BootSourceOverrideEnabled_enumType,
  (const JSON_EnumType*)&_schema_EthernetNetworkInterface_LinkTechnology_enumType,
  (const JSON_EnumType*)&_schema_EventService_SubscriptionRemovalAction_enumType,
  (const JSON_EnumType*)&_schema_EventService_EventTypesForSubscription_enumType,
  (const JSON_EnumType*)&_schema_ListenerDestination_EventTypes_enumType,
  (const JSON_EnumType*)&_schema_ListenerDestination_TTLUnits_enumType,
  (const JSON_EnumType*)&_schema_ListenerDestination_Protocol_enumType,
  (const JSON_EnumType*)&_schema_LogEntry_Severity_enumType,
  (const JSON_EnumType*)&_schema_LogEntry_EntryType_enumType,
  (const JSON_EnumType*)&_schema_LogEntry_EntryCode_enumType,
  (const JSON_EnumType*)&_schema_LogEntry_SensorType_enumType,
  (const JSON_EnumType*)&_schema_LogService_OverWritePolicy_enumType,
  (const JSON_EnumType*)&_schema_Manager_ManagerType_enumType,
  (const JSON_EnumType*)&_schema_Manager_SerialConsole_ConnectTypesSupported_enumType,
  (const JSON_EnumType*)&_schema_Manager_CommandShell_ConnectTypesSupported_enumType,
  (const JSON_EnumType*)&_schema_Manager_GraphicalConsole_ConnectTypesSupported_enumType,
  (const JSON_EnumType*)&_schema_Redundancy_Mode_enumType,
  (const JSON_EnumType*)&_schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_enumType,
  (const JSON_EnumType*)&_schema_PowerMetrics_PowerLimit_LimitException_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_SignalType_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_BitRate_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_Parity_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_DataBits_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_StopBits_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_FlowControl_enumType,
  (const JSON_EnumType*)&_schema_SerialInterface_PinOut_enumType,
  (const JSON_EnumType*)&_schema_Task_TaskState_enumType,
  (const JSON_EnumType*)&_schema_Task_TaskStatus_enumType,
  (const JSON_EnumType*)&_schema_TaskService_CompletedTaskOverWritePolicy_enumType,
  (const JSON_EnumType*)&_schema_VirtualMedia_MediaTypes_enumType,
  (const JSON_EnumType*)&_schema_VirtualMedia_ConnectedVia_enumType,
};

/*
**********************************************************************************
** schema_AccountService_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_AccountService_links_Accounts_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Accounts" /* name */
};

static const JSON_Property _schema_AccountService_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_AccountService_links_properties[] =
{
  (const JSON_Property*)&_schema_AccountService_links_Accounts_property,
  (const JSON_Property*)&_schema_AccountService_links_self_property,
};

static const JSON_ComplexType _schema_AccountService_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "AccountService.links", /* name */
  _schema_AccountService_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_AccountService_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Chassis_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Chassis_links_LogService_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012LogService" /* name */
};

static const JSON_Property _schema_Chassis_links_ComputerSystems_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\017ComputerSystems" /* name */
};

static const JSON_Property _schema_Chassis_links_ManagedBy_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011ManagedBy" /* name */
};

static const JSON_Property _schema_Chassis_links_ThermalMetrics_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016ThermalMetrics" /* name */
};

static const JSON_Property _schema_Chassis_links_PowerMetrics_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014PowerMetrics" /* name */
};

static const JSON_Property _schema_Chassis_links_MiscMetrics_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013MiscMetrics" /* name */
};

static const JSON_Property _schema_Chassis_links_ContainedBy_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\013ContainedBy" /* name */
};

static const JSON_Property _schema_Chassis_links_Contains_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Contains" /* name */
};

static const JSON_Property _schema_Chassis_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_Chassis_links_properties[] =
{
  (const JSON_Property*)&_schema_Chassis_links_LogService_property,
  (const JSON_Property*)&_schema_Chassis_links_ComputerSystems_property,
  (const JSON_Property*)&_schema_Chassis_links_ManagedBy_property,
  (const JSON_Property*)&_schema_Chassis_links_ThermalMetrics_property,
  (const JSON_Property*)&_schema_Chassis_links_PowerMetrics_property,
  (const JSON_Property*)&_schema_Chassis_links_MiscMetrics_property,
  (const JSON_Property*)&_schema_Chassis_links_ContainedBy_property,
  (const JSON_Property*)&_schema_Chassis_links_Contains_property,
  (const JSON_Property*)&_schema_Chassis_links_self_property,
};

static const JSON_ComplexType _schema_Chassis_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Chassis.links", /* name */
  _schema_Chassis_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Chassis_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Collection_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Collection_links_Member_property =
{
  34, /* flags */
  JSON_Type_Object, /* type */
  65535, /* index */
  "\006Member" /* name */
};

static const JSON_Property _schema_Collection_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_Collection_links_properties[] =
{
  (const JSON_Property*)&_schema_Collection_links_Member_property,
  (const JSON_Property*)&_schema_Collection_links_self_property,
};

static const JSON_ComplexType _schema_Collection_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Collection.links", /* name */
  _schema_Collection_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Collection_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_links_Chassis_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Chassis" /* name */
};

static const JSON_Property _schema_ComputerSystem_links_ManagedBy_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011ManagedBy" /* name */
};

static const JSON_Property _schema_ComputerSystem_links_SimpleNetwork_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\015SimpleNetwork" /* name */
};

static const JSON_Property _schema_ComputerSystem_links_SimpleStorage_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\015SimpleStorage" /* name */
};

static const JSON_Property _schema_ComputerSystem_links_LogService_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012LogService" /* name */
};

static const JSON_Property _schema_ComputerSystem_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_ComputerSystem_links_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_links_Chassis_property,
  (const JSON_Property*)&_schema_ComputerSystem_links_ManagedBy_property,
  (const JSON_Property*)&_schema_ComputerSystem_links_SimpleNetwork_property,
  (const JSON_Property*)&_schema_ComputerSystem_links_SimpleStorage_property,
  (const JSON_Property*)&_schema_ComputerSystem_links_LogService_property,
  (const JSON_Property*)&_schema_ComputerSystem_links_self_property,
};

static const JSON_ComplexType _schema_ComputerSystem_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem.links", /* name */
  _schema_ComputerSystem_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_HostCorrelation_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_HostCorrelation_IPAddress_property =
{
  49, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\011IPAddress" /* name */
};

static const JSON_Property _schema_ComputerSystem_HostCorrelation_HostMACAddress_property =
{
  49, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016HostMACAddress" /* name */
};

static const JSON_Property _schema_ComputerSystem_HostCorrelation_HostName_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010HostName" /* name */
};

static const JSON_Property _schema_ComputerSystem_HostCorrelation_HostFQDN_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010HostFQDN" /* name */
};

static const JSON_Property* _schema_ComputerSystem_HostCorrelation_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_HostCorrelation_IPAddress_property,
  (const JSON_Property*)&_schema_ComputerSystem_HostCorrelation_HostMACAddress_property,
  (const JSON_Property*)&_schema_ComputerSystem_HostCorrelation_HostName_property,
  (const JSON_Property*)&_schema_ComputerSystem_HostCorrelation_HostFQDN_property,
};

static const JSON_ComplexType _schema_ComputerSystem_HostCorrelation_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem.HostCorrelation", /* name */
  _schema_ComputerSystem_HostCorrelation_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_HostCorrelation_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_Boot_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_Boot_BootSourceOverrideTarget_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  8, /* index */
  "\030BootSourceOverrideTarget" /* name */
};

static const JSON_Property _schema_ComputerSystem_Boot_BootSourceOverrideSupported_property =
{
  56, /* flags */
  JSON_Type_Integer, /* type */
  9, /* index */
  "\033BootSourceOverrideSupported" /* name */
};

static const JSON_Property _schema_ComputerSystem_Boot_BootSourceOverrideEnabled_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  10, /* index */
  "\031BootSourceOverrideEnabled" /* name */
};

static const JSON_Property _schema_ComputerSystem_Boot_UefiTargetBootSourceOverrideSupported_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\045UefiTargetBootSourceOverrideSupported" /* name */
};

static const JSON_Property _schema_ComputerSystem_Boot_UefiTargetBootSourceOverride_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\034UefiTargetBootSourceOverride" /* name */
};

static const JSON_Property* _schema_ComputerSystem_Boot_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_Boot_BootSourceOverrideTarget_property,
  (const JSON_Property*)&_schema_ComputerSystem_Boot_BootSourceOverrideSupported_property,
  (const JSON_Property*)&_schema_ComputerSystem_Boot_BootSourceOverrideEnabled_property,
  (const JSON_Property*)&_schema_ComputerSystem_Boot_UefiTargetBootSourceOverrideSupported_property,
  (const JSON_Property*)&_schema_ComputerSystem_Boot_UefiTargetBootSourceOverride_property,
};

static const JSON_ComplexType _schema_ComputerSystem_Boot_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem.Boot", /* name */
  _schema_ComputerSystem_Boot_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Boot_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_Bios_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_Bios_Current_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  4, /* index */
  "\007Current" /* name */
};

static const JSON_Property* _schema_ComputerSystem_Bios_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_Bios_Current_property,
};

static const JSON_ComplexType _schema_ComputerSystem_Bios_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem.Bios", /* name */
  _schema_ComputerSystem_Bios_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Bios_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_Processors_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_Processors_Count_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\005Count" /* name */
};

static const JSON_Property _schema_ComputerSystem_Processors_ProcessorFamily_property =
{
  17, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\017ProcessorFamily" /* name */
};

static const JSON_Property _schema_ComputerSystem_Processors_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property* _schema_ComputerSystem_Processors_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_Processors_Count_property,
  (const JSON_Property*)&_schema_ComputerSystem_Processors_ProcessorFamily_property,
  (const JSON_Property*)&_schema_ComputerSystem_Processors_Status_property,
};

static const JSON_ComplexType _schema_ComputerSystem_Processors_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem.Processors", /* name */
  _schema_ComputerSystem_Processors_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Processors_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ComputerSystem_Memory_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ComputerSystem_Memory_TotalSystemMemoryGB_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\023TotalSystemMemoryGB" /* name */
};

static const JSON_Property _schema_ComputerSystem_Memory_Status_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  1, /* index */
  "\006Status" /* name */
};

static const JSON_Property* _schema_ComputerSystem_Memory_properties[] =
{
  (const JSON_Property*)&_schema_ComputerSystem_Memory_TotalSystemMemoryGB_property,
  (const JSON_Property*)&_schema_ComputerSystem_Memory_Status_property,
};

static const JSON_ComplexType _schema_ComputerSystem_Memory_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ComputerSystem.Memory", /* name */
  _schema_ComputerSystem_Memory_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ComputerSystem_Memory_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_EthernetNetworkInterface_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_EthernetNetworkInterface_links_Settings_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  7, /* index */
  "\010Settings" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_links_NetworkServices_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\017NetworkServices" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_links_VLANs_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005VLANs" /* name */
};

static const JSON_Property _schema_EthernetNetworkInterface_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_EthernetNetworkInterface_links_properties[] =
{
  (const JSON_Property*)&_schema_EthernetNetworkInterface_links_Settings_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_links_NetworkServices_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_links_VLANs_property,
  (const JSON_Property*)&_schema_EthernetNetworkInterface_links_self_property,
};

static const JSON_ComplexType _schema_EthernetNetworkInterface_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "EthernetNetworkInterface.links", /* name */
  _schema_EthernetNetworkInterface_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_EthernetNetworkInterface_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_EventService_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_EventService_links_Subscriptions_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\015Subscriptions" /* name */
};

static const JSON_Property _schema_EventService_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_EventService_links_properties[] =
{
  (const JSON_Property*)&_schema_EventService_links_Subscriptions_property,
  (const JSON_Property*)&_schema_EventService_links_self_property,
};

static const JSON_ComplexType _schema_EventService_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "EventService.links", /* name */
  _schema_EventService_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_EventService_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ListenerDestination_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ListenerDestination_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_ListenerDestination_links_properties[] =
{
  (const JSON_Property*)&_schema_ListenerDestination_links_self_property,
};

static const JSON_ComplexType _schema_ListenerDestination_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ListenerDestination.links", /* name */
  _schema_ListenerDestination_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ListenerDestination_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_LogEntry_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_LogEntry_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property _schema_LogEntry_links_OriginOfCondition_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\021OriginOfCondition" /* name */
};

static const JSON_Property* _schema_LogEntry_links_properties[] =
{
  (const JSON_Property*)&_schema_LogEntry_links_self_property,
  (const JSON_Property*)&_schema_LogEntry_links_OriginOfCondition_property,
};

static const JSON_ComplexType _schema_LogEntry_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "LogEntry.links", /* name */
  _schema_LogEntry_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_LogEntry_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_LogService_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_LogService_links_Entries_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Entries" /* name */
};

static const JSON_Property _schema_LogService_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_LogService_links_properties[] =
{
  (const JSON_Property*)&_schema_LogService_links_Entries_property,
  (const JSON_Property*)&_schema_LogService_links_self_property,
};

static const JSON_ComplexType _schema_LogService_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "LogService.links", /* name */
  _schema_LogService_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_LogService_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Manager_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Manager_links_ManagerForServers_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\021ManagerForServers" /* name */
};

static const JSON_Property _schema_Manager_links_ManagerForChassis_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\021ManagerForChassis" /* name */
};

static const JSON_Property _schema_Manager_links_EthernetNICs_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014EthernetNICs" /* name */
};

static const JSON_Property _schema_Manager_links_SerialInterfaces_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\020SerialInterfaces" /* name */
};

static const JSON_Property _schema_Manager_links_NetworkService_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016NetworkService" /* name */
};

static const JSON_Property _schema_Manager_links_Logs_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004Logs" /* name */
};

static const JSON_Property _schema_Manager_links_VirtualMedia_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014VirtualMedia" /* name */
};

static const JSON_Property _schema_Manager_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_Manager_links_properties[] =
{
  (const JSON_Property*)&_schema_Manager_links_ManagerForServers_property,
  (const JSON_Property*)&_schema_Manager_links_ManagerForChassis_property,
  (const JSON_Property*)&_schema_Manager_links_EthernetNICs_property,
  (const JSON_Property*)&_schema_Manager_links_SerialInterfaces_property,
  (const JSON_Property*)&_schema_Manager_links_NetworkService_property,
  (const JSON_Property*)&_schema_Manager_links_Logs_property,
  (const JSON_Property*)&_schema_Manager_links_VirtualMedia_property,
  (const JSON_Property*)&_schema_Manager_links_self_property,
};

static const JSON_ComplexType _schema_Manager_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Manager.links", /* name */
  _schema_Manager_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Manager_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Manager_SerialConsole_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Manager_SerialConsole_Enabled_property =
{
  1, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_Manager_SerialConsole_MaxConcurrentSessions_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\025MaxConcurrentSessions" /* name */
};

static const JSON_Property _schema_Manager_SerialConsole_ConnectTypesSupported_property =
{
  40, /* flags */
  JSON_Type_Integer, /* type */
  23, /* index */
  "\025ConnectTypesSupported" /* name */
};

static const JSON_Property* _schema_Manager_SerialConsole_properties[] =
{
  (const JSON_Property*)&_schema_Manager_SerialConsole_Enabled_property,
  (const JSON_Property*)&_schema_Manager_SerialConsole_MaxConcurrentSessions_property,
  (const JSON_Property*)&_schema_Manager_SerialConsole_ConnectTypesSupported_property,
};

static const JSON_ComplexType _schema_Manager_SerialConsole_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Manager.SerialConsole", /* name */
  _schema_Manager_SerialConsole_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Manager_SerialConsole_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Manager_CommandShell_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Manager_CommandShell_Enabled_property =
{
  1, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_Manager_CommandShell_MaxConcurrentSessions_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\025MaxConcurrentSessions" /* name */
};

static const JSON_Property _schema_Manager_CommandShell_ConnectTypesSupported_property =
{
  40, /* flags */
  JSON_Type_Integer, /* type */
  24, /* index */
  "\025ConnectTypesSupported" /* name */
};

static const JSON_Property* _schema_Manager_CommandShell_properties[] =
{
  (const JSON_Property*)&_schema_Manager_CommandShell_Enabled_property,
  (const JSON_Property*)&_schema_Manager_CommandShell_MaxConcurrentSessions_property,
  (const JSON_Property*)&_schema_Manager_CommandShell_ConnectTypesSupported_property,
};

static const JSON_ComplexType _schema_Manager_CommandShell_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Manager.CommandShell", /* name */
  _schema_Manager_CommandShell_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Manager_CommandShell_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Manager_GraphicalConsole_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Manager_GraphicalConsole_Enabled_property =
{
  1, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_Manager_GraphicalConsole_MaxConcurrentSessions_property =
{
  1, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\025MaxConcurrentSessions" /* name */
};

static const JSON_Property _schema_Manager_GraphicalConsole_ConnectTypesSupported_property =
{
  40, /* flags */
  JSON_Type_Integer, /* type */
  25, /* index */
  "\025ConnectTypesSupported" /* name */
};

static const JSON_Property* _schema_Manager_GraphicalConsole_properties[] =
{
  (const JSON_Property*)&_schema_Manager_GraphicalConsole_Enabled_property,
  (const JSON_Property*)&_schema_Manager_GraphicalConsole_MaxConcurrentSessions_property,
  (const JSON_Property*)&_schema_Manager_GraphicalConsole_ConnectTypesSupported_property,
};

static const JSON_ComplexType _schema_Manager_GraphicalConsole_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Manager.GraphicalConsole", /* name */
  _schema_Manager_GraphicalConsole_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Manager_GraphicalConsole_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerAccount_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerAccount_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_ManagerAccount_links_properties[] =
{
  (const JSON_Property*)&_schema_ManagerAccount_links_self_property,
};

static const JSON_ComplexType _schema_ManagerAccount_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerAccount.links", /* name */
  _schema_ManagerAccount_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerAccount_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_links_Settings_property =
{
  4, /* flags */
  JSON_Type_Object, /* type */
  7, /* index */
  "\010Settings" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_links_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_links_Settings_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_links_self_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.links", /* name */
  _schema_ManagerNetworkService_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_HTTP_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_HTTP_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_HTTP_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_HTTP_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_HTTP_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_HTTP_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_HTTP_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.HTTP", /* name */
  _schema_ManagerNetworkService_HTTP_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_HTTP_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_HTTPS_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_HTTPS_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_HTTPS_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_HTTPS_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_HTTPS_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_HTTPS_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_HTTPS_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.HTTPS", /* name */
  _schema_ManagerNetworkService_HTTPS_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_HTTPS_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_SNMP_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_SNMP_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SNMP_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_SNMP_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_SNMP_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SNMP_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_SNMP_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.SNMP", /* name */
  _schema_ManagerNetworkService_SNMP_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_SNMP_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_VirtualMedia_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_VirtualMedia_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_VirtualMedia_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_VirtualMedia_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_VirtualMedia_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_VirtualMedia_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_VirtualMedia_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.VirtualMedia", /* name */
  _schema_ManagerNetworkService_VirtualMedia_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_VirtualMedia_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_Telnet_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_Telnet_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_Telnet_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_Telnet_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_Telnet_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_Telnet_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_Telnet_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.Telnet", /* name */
  _schema_ManagerNetworkService_Telnet_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_Telnet_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_SSDP_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_SSDP_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSDP_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSDP_NotifyMulticastIntervalSeconds_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\036NotifyMulticastIntervalSeconds" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSDP_NotifyTTL_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\011NotifyTTL" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  27, /* index */
  "\017NotifyIPv6Scope" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_SSDP_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_SSDP_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSDP_Port_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSDP_NotifyMulticastIntervalSeconds_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSDP_NotifyTTL_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSDP_NotifyIPv6Scope_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_SSDP_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.SSDP", /* name */
  _schema_ManagerNetworkService_SSDP_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_SSDP_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_IPMI_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_IPMI_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_IPMI_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_IPMI_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_IPMI_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_IPMI_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_IPMI_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.IPMI", /* name */
  _schema_ManagerNetworkService_IPMI_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_IPMI_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_SSH_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_SSH_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_SSH_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_SSH_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_SSH_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_SSH_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_SSH_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.SSH", /* name */
  _schema_ManagerNetworkService_SSH_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_SSH_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ManagerNetworkService_KVMIP_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ManagerNetworkService_KVMIP_Enabled_property =
{
  17, /* flags */
  JSON_Type_Boolean, /* type */
  0, /* index */
  "\007Enabled" /* name */
};

static const JSON_Property _schema_ManagerNetworkService_KVMIP_Port_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\004Port" /* name */
};

static const JSON_Property* _schema_ManagerNetworkService_KVMIP_properties[] =
{
  (const JSON_Property*)&_schema_ManagerNetworkService_KVMIP_Enabled_property,
  (const JSON_Property*)&_schema_ManagerNetworkService_KVMIP_Port_property,
};

static const JSON_ComplexType _schema_ManagerNetworkService_KVMIP_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ManagerNetworkService.KVMIP", /* name */
  _schema_ManagerNetworkService_KVMIP_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ManagerNetworkService_KVMIP_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_MiscMetrics_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_MiscMetrics_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_MiscMetrics_links_properties[] =
{
  (const JSON_Property*)&_schema_MiscMetrics_links_self_property,
};

static const JSON_ComplexType _schema_MiscMetrics_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "MiscMetrics.links", /* name */
  _schema_MiscMetrics_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_MiscMetrics_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_PowerMetrics_PowerMetrics_complexType
**
*********************************************************************************/

static const JSON_Property _schema_PowerMetrics_PowerMetrics_IntervalInMin_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\015IntervalInMin" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerMetrics_MinConsumedWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\020MinConsumedWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerMetrics_MaxConsumedWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\020MaxConsumedWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerMetrics_AverageConsumedWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\024AverageConsumedWatts" /* name */
};

static const JSON_Property* _schema_PowerMetrics_PowerMetrics_properties[] =
{
  (const JSON_Property*)&_schema_PowerMetrics_PowerMetrics_IntervalInMin_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerMetrics_MinConsumedWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerMetrics_MaxConsumedWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerMetrics_AverageConsumedWatts_property,
};

static const JSON_ComplexType _schema_PowerMetrics_PowerMetrics_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "PowerMetrics.PowerMetrics", /* name */
  _schema_PowerMetrics_PowerMetrics_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_PowerMetrics_PowerMetrics_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_PowerMetrics_PowerLimit_complexType
**
*********************************************************************************/

static const JSON_Property _schema_PowerMetrics_PowerLimit_LimitInWatts_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\014LimitInWatts" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerLimit_LimitException_property =
{
  24, /* flags */
  JSON_Type_Integer, /* type */
  28, /* index */
  "\016LimitException" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerLimit_CorrectionInMs_property =
{
  17, /* flags */
  JSON_Type_Integer, /* type */
  0, /* index */
  "\016CorrectionInMs" /* name */
};

static const JSON_Property _schema_PowerMetrics_PowerLimit_CorrelatableID_property =
{
  49, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016CorrelatableID" /* name */
};

static const JSON_Property* _schema_PowerMetrics_PowerLimit_properties[] =
{
  (const JSON_Property*)&_schema_PowerMetrics_PowerLimit_LimitInWatts_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerLimit_LimitException_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerLimit_CorrectionInMs_property,
  (const JSON_Property*)&_schema_PowerMetrics_PowerLimit_CorrelatableID_property,
};

static const JSON_ComplexType _schema_PowerMetrics_PowerLimit_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "PowerMetrics.PowerLimit", /* name */
  _schema_PowerMetrics_PowerLimit_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_PowerMetrics_PowerLimit_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_PowerMetrics_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_PowerMetrics_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_PowerMetrics_links_properties[] =
{
  (const JSON_Property*)&_schema_PowerMetrics_links_self_property,
};

static const JSON_ComplexType _schema_PowerMetrics_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "PowerMetrics.links", /* name */
  _schema_PowerMetrics_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_PowerMetrics_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_SchemaFile_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_SchemaFile_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_SchemaFile_links_properties[] =
{
  (const JSON_Property*)&_schema_SchemaFile_links_self_property,
};

static const JSON_ComplexType _schema_SchemaFile_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "SchemaFile.links", /* name */
  _schema_SchemaFile_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_SchemaFile_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ServiceRoot_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ServiceRoot_links_Systems_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Systems" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_Chassis_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Chassis" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_Managers_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Managers" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_Tasks_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005Tasks" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_AccountService_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\016AccountService" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_Sessions_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\010Sessions" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_EventService_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\014EventService" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_Schemas_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\007Schemas" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_Registries_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\012Registries" /* name */
};

static const JSON_Property _schema_ServiceRoot_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_ServiceRoot_links_properties[] =
{
  (const JSON_Property*)&_schema_ServiceRoot_links_Systems_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_Chassis_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_Managers_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_Tasks_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_AccountService_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_Sessions_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_EventService_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_Schemas_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_Registries_property,
  (const JSON_Property*)&_schema_ServiceRoot_links_self_property,
};

static const JSON_ComplexType _schema_ServiceRoot_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ServiceRoot.links", /* name */
  _schema_ServiceRoot_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ServiceRoot_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Session_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Session_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_Session_links_properties[] =
{
  (const JSON_Property*)&_schema_Session_links_self_property,
};

static const JSON_ComplexType _schema_Session_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Session.links", /* name */
  _schema_Session_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Session_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_Task_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_Task_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_Task_links_properties[] =
{
  (const JSON_Property*)&_schema_Task_links_self_property,
};

static const JSON_ComplexType _schema_Task_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "Task.links", /* name */
  _schema_Task_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_Task_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_TaskService_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_TaskService_links_Tasks_property =
{
  33, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\005Tasks" /* name */
};

static const JSON_Property _schema_TaskService_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_TaskService_links_properties[] =
{
  (const JSON_Property*)&_schema_TaskService_links_Tasks_property,
  (const JSON_Property*)&_schema_TaskService_links_self_property,
};

static const JSON_ComplexType _schema_TaskService_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "TaskService.links", /* name */
  _schema_TaskService_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_TaskService_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_ThermalMetrics_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_ThermalMetrics_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_ThermalMetrics_links_properties[] =
{
  (const JSON_Property*)&_schema_ThermalMetrics_links_self_property,
};

static const JSON_ComplexType _schema_ThermalMetrics_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "ThermalMetrics.links", /* name */
  _schema_ThermalMetrics_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_ThermalMetrics_links_properties), /* propertiesSize */
};

/*
**********************************************************************************
** schema_VirtualMedia_links_complexType
**
*********************************************************************************/

static const JSON_Property _schema_VirtualMedia_links_self_property =
{
  1, /* flags */
  JSON_Type_String, /* type */
  0, /* index */
  "\004self" /* name */
};

static const JSON_Property* _schema_VirtualMedia_links_properties[] =
{
  (const JSON_Property*)&_schema_VirtualMedia_links_self_property,
};

static const JSON_ComplexType _schema_VirtualMedia_links_complexType =
{
  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */
  "VirtualMedia.links", /* name */
  _schema_VirtualMedia_links_properties, /* properties */
  ODATA_ARRAYSIZE(_schema_VirtualMedia_links_properties), /* propertiesSize */
};

static const JSON_ComplexType* _schema_complexTypes[] =
{
  (const JSON_ComplexType*)&_schema_AccountService_links_complexType,
  (const JSON_ComplexType*)&_schema_Chassis_links_complexType,
  (const JSON_ComplexType*)&_schema_Collection_links_complexType,
  (const JSON_ComplexType*)&_schema_ComputerSystem_links_complexType,
  (const JSON_ComplexType*)&_schema_ComputerSystem_HostCorrelation_complexType,
  (const JSON_ComplexType*)&_schema_ComputerSystem_Boot_complexType,
  (const JSON_ComplexType*)&_schema_ComputerSystem_Bios_complexType,
  (const JSON_ComplexType*)&_schema_ComputerSystem_Processors_complexType,
  (const JSON_ComplexType*)&_schema_ComputerSystem_Memory_complexType,
  (const JSON_ComplexType*)&_schema_EthernetNetworkInterface_links_complexType,
  (const JSON_ComplexType*)&_schema_EventService_links_complexType,
  (const JSON_ComplexType*)&_schema_ListenerDestination_links_complexType,
  (const JSON_ComplexType*)&_schema_LogEntry_links_complexType,
  (const JSON_ComplexType*)&_schema_LogService_links_complexType,
  (const JSON_ComplexType*)&_schema_Manager_links_complexType,
  (const JSON_ComplexType*)&_schema_Manager_SerialConsole_complexType,
  (const JSON_ComplexType*)&_schema_Manager_CommandShell_complexType,
  (const JSON_ComplexType*)&_schema_Manager_GraphicalConsole_complexType,
  (const JSON_ComplexType*)&_schema_ManagerAccount_links_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_links_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_HTTP_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_HTTPS_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_SNMP_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_VirtualMedia_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_Telnet_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_SSDP_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_IPMI_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_SSH_complexType,
  (const JSON_ComplexType*)&_schema_ManagerNetworkService_KVMIP_complexType,
  (const JSON_ComplexType*)&_schema_MiscMetrics_links_complexType,
  (const JSON_ComplexType*)&_schema_PowerMetrics_PowerMetrics_complexType,
  (const JSON_ComplexType*)&_schema_PowerMetrics_PowerLimit_complexType,
  (const JSON_ComplexType*)&_schema_PowerMetrics_links_complexType,
  (const JSON_ComplexType*)&_schema_SchemaFile_links_complexType,
  (const JSON_ComplexType*)&_schema_ServiceRoot_links_complexType,
  (const JSON_ComplexType*)&_schema_Session_links_complexType,
  (const JSON_ComplexType*)&_schema_Task_links_complexType,
  (const JSON_ComplexType*)&_schema_TaskService_links_complexType,
  (const JSON_ComplexType*)&_schema_ThermalMetrics_links_complexType,
  (const JSON_ComplexType*)&_schema_VirtualMedia_links_complexType,
};

/*
**********************************************************************************
** schema
**
*********************************************************************************/

const JSON_Schema _schema =
{
  _schema_entityTypes, /* entityTypes */
  ODATA_ARRAYSIZE(_schema_entityTypes), /* entityTypesSize */
  _schema_enumTypes, /* enumTypes */
  ODATA_ARRAYSIZE(_schema_enumTypes), /* enumTypesSize */
  _schema_complexTypes, /* complexTypes */
  ODATA_ARRAYSIZE(_schema_complexTypes), /* complexTypesSize */
};

