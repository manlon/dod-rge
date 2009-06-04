@echo off 
title make for PSP【自动复制游戏到PSP】
cd /d %~dp0

set PSPGAMEPATH=\PSP\GAME150\psprge
set PATH=%PATH%;f:\PSP\devkitPro\msys\bin;f:\PSP\devkitPro\devkitPSP\bin;
set PSPDEV=
set PSPSDK=

rem ============================== 以下是编译工程 ========================
echo 正在编译工程...
make clean >nul 2>nul
make %~1 
if %ERRORLEVEL% GTR 0 goto end

rem ============================== 以下是复制文件 ========================
if NOT EXIST EBOOT.pbp goto end
echo 正在复制游戏到PSP...
:again 
del /Q /f "%temp%\copy.tmp" >nul 2>nul 
for %%i in (c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z) do @fsutil fsinfo drivetype %%i: >>"%temp%\copy.tmp" 
findstr /i "可移动" "%temp%\copy.tmp"  >nul 2>nul
if %ERRORLEVEL% EQU 1 goto connect 
if %ERRORLEVEL% EQU 0 goto copy

:connect  
printf "\r请先连接PSP数据线，并设定为USB模式..." 
ping 127.0.0.1 -n 2 >nul 2>nul 
goto again 

:copy
printf "\r"
for /f "tokens=1" %%i in ('findstr /i "可移动" "%temp%\copy.tmp"') do ( 
xcopy /f /y EBOOT.pbp %%i%PSPGAMEPATH%\ 
) 
goto end

rem ============================== 退出 ========================
:end
ping 127.0.0.1 -n 3 >nul 2>nul 

@echo on