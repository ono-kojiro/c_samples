<!-- : Begin batch script
@ECHO OFF
@SETLOCAL ENABLEDELAYEDEXPANSION

SET PATH=%SYSTEMROOT%\System32
CALL C:\opt\PortableGit-2.36.1-64-bit.bat
CALL C:\opt\python-3.10.4-embed-amd64.bat

CALL C:\opt\cuda-v11.7.bat
CALL C:\opt\cudnn-windows-x86_64-8.4.0.27_cuda11.6.bat
CALL C:\opt\cmake-3.23.1-windows-x86_64.bat
CALL C:\opt\strawberry-perl-5.32.1.1-64bit-portable.bat


SET MODEL=models/mymodel

IF "x%1" == "x" (
	CALL :ALL
	REM disable echo because subroutine might enable echo
	@ECHO OFF
	IF NOT !ERRORLEVEL! == 0 (
		ECHO ERROR : ALL returned !ERRORLEVEL!
		EXIT /B !ERRORLEVEL!
	)
) else (
	FOR %%i IN (%*) DO (
		CALL :_CHECK_LABEL %%i
		IF !ERRORLEVEL! == 0 (
			CALL :%%i
			REM disable echo because subroutine might enable echo
			@ECHO OFF

			IF NOT !ERRORLEVEL! == 0 (
				ECHO ERROR : %%i returned !ERRORLEVEL!
				EXIT /B !ERRORLEVEL!
			)
		) ELSE (
			ECHO ERROR : no such label, "%%i"
			EXIT /B 1
		)
		
	)
)

ENDLOCAL & SET ERRORLEVEL=%ERRORLEVEL%
@ECHO ON
@EXIT /B !ERRORLEVEL!

REM ===============================
REM === All
REM ===============================
:ALL
CALL :CONFIG
GOTO :EOF

REM ===============================
REM === Help
REM ===============================
:HELP
ECHO "Usage : build.bat command [command...]"
GOTO :EOF

REM ===============================
REM === Version
REM ===============================
:VERSION
ECHO %PATH%
git --version
python --version
GOTO :EOF

REM ===============================
REM === VS
REM ===============================
:VS
IF NOT EXIST build ( MD build )
cd build
echo hoge
DEL /Q /S CMakeCache.txt 1>NUL 2>NUL
cmake -G "Visual Studio 12 2013" -A Win32 ..
cd ..
GOTO :EOF

REM ===============================
REM === Config
REM ===============================
:CONFIG
IF NOT EXIST _build_mingw ( MD _build_mingw )
DEL /Q /S CMakeCache.txt 1>NUL 2>NUL
cmake -B _build_mingw -G "MinGW Makefiles" ^
  -DCMAKE_C_COMPILER=gcc ^
  -DCMAKE_MAKE_PROGRAM=gmake ^
  -DCMAKE_INSTALL_PREFIX=/c ^
  .
GOTO :EOF

REM ===============================
REM === Build
REM ===============================
:BUILD
cmake --build _build_mingw
GOTO :EOF

REM ===============================
REM === Test
REM ===============================
:TEST
ctest --test-dir _build_mingw
GOTO :EOF

REM ===============================
REM === Install
REM ===============================
:INSTALL
gmake -C _build_mingw install DESTDIR=c:\opt\strawberry-perl-5.32.1.1-64bit-portable
GOTO :EOF

REM ===============================
REM === Predict
REM ===============================
:PREDICT
REM SET TF_CPP_MIN_LOG_LEVEL=2
python predict.py -m !MODEL! -o predict.png -e prediction_error.png
GOTO :EOF

REM ===============================
REM === Clean
REM ===============================
:CLEAN
ECHO This is clean.
CSCRIPT //NOLOGO "%~f0?.wsf" //job:Clean
@GOTO :EOF

REM ===============================
REM === _CHECK_LABEL
REM ===============================
:_CHECK_LABEL
FINDSTR /I /R /C:"^[ ]*:%1\>" "%~f0" >NUL 2>NUL
@GOTO :EOF

----- Begin wsf script --->
<package>
	<job id="Main">
		<?job debug="true"?>
		<script language="JavaScript">
			WScript.Echo("Hello JavaScript World");
			WScript.Quit(0);
		</script>
	</job>

	<job id="Clean">
		<?job debug="true"?>
		<script language="JavaScript">
			WScript.Echo("This is clean job");
			WScript.Quit(0);
		</script>
	</job>
</package>
