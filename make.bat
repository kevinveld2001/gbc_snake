@echo off

set GBDK_PATH=c:\gbdk\bin
set BGB_PATH=c:\gb\bgb
set SOURCE_PATH=src
set OUTPUT_PATH=out

mkdir %OUTPUT_PATH% 2>nul

for /r %SOURCE_PATH% %%i in (*.c) do (
    %GBDK_PATH%\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o %OUTPUT_PATH%\%%~ni.o "%%i"
)

%GBDK_PATH%\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yp0x143=0x80 -o %OUTPUT_PATH%\main.gbc %OUTPUT_PATH%\*.o

DEL %OUTPUT_PATH%\*.o
DEL %OUTPUT_PATH%\*.lst
DEL %OUTPUT_PATH%\*.sym
DEL %OUTPUT_PATH%\*.asm
DEL %OUTPUT_PATH%\*.ihx
DEL %OUTPUT_PATH%\*.map
DEL %OUTPUT_PATH%\*.noi

echo "start game..."
%BGB_PATH%\bgb.exe ./out/main.gbc