@echo off

echo. 
echo This application is aimed to create a body from a shape.
echo.
echo.
echo Retrieving sections of the shape...
echo Starting the tnbHydstcShapeSections application:
start /wait tnbHydstcShapeSectionsd.exe --run
if %errorlevel% geq 1 exit /B 1
echo The tnbHydstcShapeSections application is completed(1/6), successfully!
echo.

echo Discretizing the edges of the sections...
echo Starting the tnbHydstcDiscretizeSections application:
start /wait tnbHydstcDiscretizeSectionsd.exe --run
if %errorlevel% geq 1 exit /B 1
echo The tnbHydstcDiscretizeSections application is completed(2/6), successfully!
echo.

echo Analysing the sections...
echo Starting the tnbHydstcSectionAnalysis application:
start /wait tnbHydstcSectionAnalysisd.exe --run
if %errorlevel% geq 1 exit /B 1
echo The tnbHydstcSectionAnalysis application is completed(3/6), successfully!
echo.

echo Reporting the Analyzing of the sections...
echo Starting the tnbHydstcSectionAnalysisReport application:
start /wait tnbHydstcSectionAnalysisReportd.exe --run
if %errorlevel% geq 1 exit /B 1
echo The tnbHydstcSectionAnalysisReport application is completed(4/6), successfully!
echo.

echo Making the sections...
echo Starting the tnbHydstcSectionCreator application:
start /wait tnbHydstcSectionCreatord.exe --run
if %errorlevel% geq 1 exit /B 1
echo The tnbHydstcSectionCreator application is completed(5/6), successfully!
echo.

echo Making the body...
echo Starting the tnbHydstcBodyMaker application:
start /wait tnbHydstcBodyMakerd.exe --run
if %errorlevel% geq 1 exit /B 1
echo The tnbHydstcBodyMaker application is completed(6/6), successfully!
echo.

pause