@echo off

call "../config.bat"


set MAKEFILE="makefile.mk"
set RULE="clean"


%MAKE% %RULE% -f %MAKEFILE%