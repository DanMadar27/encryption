@echo off

Rem doing this in order to use updated %errorlevel% in if block 
setlocal ENABLEDELAYEDEXPANSION


call "../../../config.bat"


set ROOT="../../../../../"

set MAKEFILE="makefile.mk"
set RULE="all"
set APP=%ROOT%"build/windows/test/files/encrypt/app.exe"


%MAKE% %RULE% -f %MAKEFILE%


if %errorlevel%==0 (

    %APP%

    if !errorlevel!==0 (

        echo %EXECUTION_SUCCESS%

    ) else (

        echo %EXECUTION_FAILED% !errorlevel!
    
    )

) else (

    echo %COMPILATION_FAILED% !errorlevel!

)