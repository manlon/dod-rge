@echo off 
title make for PSP���Զ�������Ϸ��PSP��
cd /d %~dp0

set PSPGAMEPATH=\PSP\GAME150\psprge
set PATH=%PATH%;f:\PSP\devkitPro\msys\bin;f:\PSP\devkitPro\devkitPSP\bin;
set PSPDEV=
set PSPSDK=

rem ============================== �����Ǳ��빤�� ========================
echo ���ڱ��빤��...
make clean >nul 2>nul
make %~1 
if %ERRORLEVEL% GTR 0 goto end

rem ============================== �����Ǹ����ļ� ========================
if NOT EXIST EBOOT.pbp goto end
echo ���ڸ�����Ϸ��PSP...
:again 
del /Q /f "%temp%\copy.tmp" >nul 2>nul 
for %%i in (c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z) do @fsutil fsinfo drivetype %%i: >>"%temp%\copy.tmp" 
findstr /i "���ƶ�" "%temp%\copy.tmp"  >nul 2>nul
if %ERRORLEVEL% EQU 1 goto connect 
if %ERRORLEVEL% EQU 0 goto copy

:connect  
printf "\r��������PSP�����ߣ����趨ΪUSBģʽ..." 
ping 127.0.0.1 -n 2 >nul 2>nul 
goto again 

:copy
printf "\r"
for /f "tokens=1" %%i in ('findstr /i "���ƶ�" "%temp%\copy.tmp"') do ( 
xcopy /f /y EBOOT.pbp %%i%PSPGAMEPATH%\ 
) 
goto end

rem ============================== �˳� ========================
:end
ping 127.0.0.1 -n 3 >nul 2>nul 

@echo on