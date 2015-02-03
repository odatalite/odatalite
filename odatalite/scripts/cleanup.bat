@echo off
devenv /clean debug phit.sln
devenv /clean release phit.sln
rmdir /s /q .\Debug
rmdir /s /q .\src\base\Debug
rmdir /s /q .\src\client\Debug
rmdir /s /q .\src\providers\num\Debug
rmdir /s /q .\src\server\Debug
rmdir /s /q .\src\tests\Debug
rmdir /s /q .\Release
rmdir /s /q .\src\base\Release
rmdir /s /q .\src\client\Release
rmdir /s /q .\src\providers\num\Release
rmdir /s /q .\src\server\Release
rmdir /s /q .\src\tests\Release
del phit.sdf
