@echo off

set PATH=%PATH%;%PSPENV%
set PSPDEV=
set PSPSDK=

make clean && make

@echo on