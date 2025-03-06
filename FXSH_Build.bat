@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist STTT.G1A  del STTT.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\Users\henry\Documents\CASIO\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\Users\henry\Documents\CASIO\Tools\MakeAddinHeader363.exe" "C:\Users\henry\Documents\github\superTicTacToe"
if not exist STTT.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

