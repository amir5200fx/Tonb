using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tnbApiReconsCylinder
{

    
    
    internal class Program
    {

        static string currentPath;

        static string axisDirectory = "axis";
        static string modelDirectory = "model";
        static string axisCreatorApp = "tnbGeoAxis3d";
        static string planeCreatorApp = "tnbGeoPlnNormalAxis";
        static string circleSectionCreatorApp = "tnbShapeFitCircleSection";
        static string projectApp = "tnbGeoToolProjPolyToPlane";
        static string intersectionApp = "tnbMeshToolPlnIntsct";
        static string retrievePolyApp = "tnbMeshToolPlnIntsctPolygons";
        static string scattersApp = "tnbShapeFitSingleScatterMap2d";
        static string shapeFitSectionApp = "tnbShapeFitSection";
        static string extrudedShapeApp = "tnbShapeFitLinExtruded";

        static string sectionsDirectory = "sections";
        static string planeDirectory = "plane";
        static string sectionDirectory = "section";
        static string meshDirectory = "mesh";
        static string intersectionDirectory = "intersection";
        static string resultsDirectory = "results";
        static string scattersDirectory = "scatters";
        static string polygonDirectory = "polygon";
        static string optimizationDirectory = "optimization";
        static string shapeDirectory = "shape";

        static string systemDirectory = "system";
        static string pathExtension = ".PATH";

        static string axisPath;
        static string modelPath;

        static bool checkDirectory(string path)
        {
            /*bool exists =*/return System.IO.Directory.Exists(path);
            //if (!exists)
            //{
            //    System.IO.Directory.CreateDirectory(path);
            //}
        }

        static void createDirectory(string name)
        {
            if(checkDirectory(name))
            {
                Directory.Delete(name, true);
            }
            Directory.CreateDirectory(name);
        }

        static void createPath(string currentPath, List<string> paths)
        {
            string filePath = currentPath + @"\" + pathExtension;
            using (StreamWriter sw = new StreamWriter(filePath))
            {
                foreach(string path in paths)
                {
                    sw.WriteLine(path);
                }
                sw.Close();
            }
        }

        static void createPath(string currentPath, string path)
        {
            string filePath = currentPath + @"\" + pathExtension;
            using (StreamWriter sw = new StreamWriter(filePath))
            {
                sw.WriteLine(path);
                sw.Close();
            }
        }

        static void runApplicationRunArg(string nameApp, bool runInDebugMode = false)
        {
            try
            {
                if (runInDebugMode)
                {
                    Console.WriteLine(" Warning: the application is going to run in DEBUG mode!");
                    Console.WriteLine(" - Application's Name: " + nameApp);
                }
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = nameApp + ".exe",
                        Arguments = "--run",
                        UseShellExecute = false,
                        RedirectStandardOutput = true,
                        CreateNoWindow = true
                    }
                };

                proc.Start();
                while (!proc.StandardOutput.EndOfStream)
                {
                    var line = proc.StandardOutput.ReadLine();
                    Console.WriteLine(line);
                }

                if (proc.ExitCode > 0)
                {
                    Environment.Exit(1);
                }
            }
            catch (Exception ex)
            {
                if (runInDebugMode)
                {
                    Console.WriteLine(ex.Message);
                    Environment.Exit(1);
                }
                runApplicationRunArg(nameApp + "d", true);
            }
        }

        static void closeProgram(string expression)
        {
            Console.WriteLine(expression);
            Environment.Exit(1);
        }

        static void changeCurrentDirectory(string path)
        {
            Directory.SetCurrentDirectory(path);
        }

        static void createAxis()
        {
            if(!checkDirectory(axisDirectory))
            {
                closeProgram($"cannot find the '{axisDirectory}' directory.");
            }
            changeCurrentDirectory(currentPath + @"\" + axisDirectory);
            if(!checkDirectory(systemDirectory))
            {
                closeProgram("cannot find the system directory of the axis.");
            }
            runApplicationRunArg(axisCreatorApp);
            changeCurrentDirectory(currentPath);
        }

        static void createPlane()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            if (!checkDirectory(planeDirectory))
            {
                closeProgram($"cannot find the '{planeDirectory}' directory.");
            }
            var current = savedCurrent + @"\" + planeDirectory;
            changeCurrentDirectory(current);

            if (!checkDirectory(systemDirectory))
            {
                closeProgram($"cannot find the '{systemDirectory}' directory.");
            }
            createDirectory(axisDirectory);
            createPath(current + @"\" + axisDirectory, axisPath);
            runApplicationRunArg(planeCreatorApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void createCircleSection()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            if(!checkDirectory(sectionDirectory))
            {
                closeProgram($"cannot find the '{sectionDirectory}' directory.");
            }
            var current = savedCurrent + @"\" + sectionDirectory;
            changeCurrentDirectory(current);

            if (!checkDirectory(systemDirectory))
            {
                closeProgram($"cannot find the '{systemDirectory}' directory.");
            }
            runApplicationRunArg(circleSectionCreatorApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void createIntersection()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            var current = savedCurrent + @"\" + intersectionDirectory;
            createDirectory(intersectionDirectory);
            createDirectory(current + @"\" + meshDirectory);
            createPath(current + @"\" + meshDirectory, modelPath);
            createDirectory(current + @"\" + planeDirectory);
            createPath(current + @"\" + planeDirectory, savedCurrent + @"\" + planeDirectory);
            changeCurrentDirectory(current);
            runApplicationRunArg(intersectionApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void projectToSection(string k, string planePath)
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            var current = savedCurrent + @"\" + k;
            changeCurrentDirectory(current);
            createDirectory(planeDirectory);
            createPath(current + @"\" + planeDirectory, planePath);   
            runApplicationRunArg(projectApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void projectToSection()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            var planePath = savedCurrent + @"\" + planeDirectory;
            var current = savedCurrent + @"\" + intersectionDirectory + @"\" + resultsDirectory;
            changeCurrentDirectory(current);
            var directories = Directory.GetDirectories(current).ToList();
            foreach (var directory in directories)
            {
                string lastFolderName = Path.GetFileName(directory);
                projectToSection(lastFolderName, planePath);
            }
            changeCurrentDirectory(savedCurrent);
        }

        static void retrievePolygongsFormIntersection()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            var current = savedCurrent + @"\" + intersectionDirectory;
            changeCurrentDirectory(current);
            runApplicationRunArg(retrievePolyApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void createScatters()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            var current = savedCurrent + @"\" + scattersDirectory;
            createDirectory(scattersDirectory);
            changeCurrentDirectory(current);
            createDirectory(polygonDirectory);
            var resultsPath = savedCurrent + @"\" + intersectionDirectory + @"\" + resultsDirectory;
            var directories = Directory.GetDirectories(resultsPath).ToList();
            createPath(current + @"\" + polygonDirectory, directories);
            runApplicationRunArg(scattersApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void createOptimization()
        {
            var savedCurrent = Directory.GetCurrentDirectory();
            var current = savedCurrent + @"\" + optimizationDirectory;
            changeCurrentDirectory(current);
            if(!checkDirectory(systemDirectory))
            {
                closeProgram($"cannot find the '{systemDirectory}' directory.");
            }
            createDirectory(scattersDirectory);
            createPath(current + @"\" + scattersDirectory, savedCurrent + @"\" + scattersDirectory);
            createDirectory(sectionDirectory);
            createPath(current + @"\" + sectionDirectory, savedCurrent + @"\" + sectionDirectory);
            runApplicationRunArg(shapeFitSectionApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void createSection(string k)
        {
            Console.WriteLine("");
            Console.WriteLine($" ############### Creating the section '{k}' ...");
            Console.WriteLine("");
            var savedCurrent = Directory.GetCurrentDirectory();
            var current = savedCurrent + @"\" + k;
            changeCurrentDirectory(current);
            if(!checkDirectory(optimizationDirectory))
            {
                closeProgram($"cannot find the '{optimizationDirectory}' directory.");
            }
            createCircleSection();
            createPlane();
            createIntersection();
            retrievePolygongsFormIntersection();
            projectToSection();
            createScatters();
            createOptimization();
            changeCurrentDirectory(savedCurrent);
            Console.WriteLine("");
            Console.WriteLine($" ############### The section '{k}' has been created.");
            Console.WriteLine("");
        }

        static void createSections()
        {
            changeCurrentDirectory(currentPath);
            if(!checkDirectory(sectionsDirectory))
            {
                closeProgram("cannot find the 'sections' directory");
            }
            var current = currentPath + @"\" + sectionsDirectory;
            changeCurrentDirectory(current);
            var directories = Directory.GetDirectories(current).ToList();
            //int directoryNb = 0;
            //while(directories.Contains(directoryNb.ToString()))
            //{
            //    createSection(directoryNb);
            //    directoryNb++;
            //}
            foreach (var directory in directories)
            {
                string lastFolderName = Path.GetFileName(directory);
                //int directoryNb = Int32.Parse(lastFolderName);
                //Console.WriteLine(lastFolderName);
                createSection(lastFolderName);
                //try
                //{

                //}
                //catch
                //{
                //    closeProgram($"Unable to parse '{directory}'");
                //}
            }
            changeCurrentDirectory(currentPath);
        }

        static void createShape()
        {
            changeCurrentDirectory(currentPath);
            var savedCurrent=Directory.GetCurrentDirectory();
            createDirectory(shapeDirectory);
            var current = savedCurrent + @"\" + shapeDirectory;
            changeCurrentDirectory(current);
            runApplicationRunArg(extrudedShapeApp);
            changeCurrentDirectory(savedCurrent);
        }

        static void Main(string[] args)
        {
            currentPath = Directory.GetCurrentDirectory();
            axisPath = currentPath + @"\" + axisDirectory;
            modelPath = currentPath + @"\" + modelDirectory;

            {//- create the axis
                Console.WriteLine("creating the axis...");
                createAxis();
                Console.WriteLine("");
                Console.WriteLine(" - the Axis has been created successfully!");
                Console.WriteLine("");
            }

            {//- create the sections

                Console.WriteLine("creating the sections...");
                createSections();
                Console.WriteLine("");
                Console.WriteLine(" - the sections have been created successfully!");
                Console.WriteLine("");
            }

            {//- create the shape
                Console.WriteLine("creating the shape...");
                createShape();
                Console.WriteLine("");
                Console.WriteLine(" - the shape have been created successfully!");
                Console.WriteLine("");
            }
        }
    }
}
