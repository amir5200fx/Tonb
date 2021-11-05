using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using System.CommandLine;

namespace tnbApiStabilityModelMaker
{
    class Program
    {

        static string currentPath;

        static string hullDirectory;
        static string tanksDirectory;
        static string sailsDirectory;

        static string resutDirectory = "result";

        static string hullExtension = ".hull";
        static string tankListExtension = ".tankList";
        static string sailListExtension = ".sailList";

        static string shapeExtension = ".shape";


        static private List<string> listAllFiles(string dir, string extension)
        {
            return Directory.GetFiles(dir, extension, SearchOption.TopDirectoryOnly).ToList();
        }

        static private string getSingleFile(string dir, string extension)
        {
            var fileList = listAllFiles(dir, extension);
            if (fileList.Count != 1)
            {
                Console.WriteLine("");
                Console.WriteLine("unable to load '*." + extension + "' file in the directory!");
                foreach (var ifile in fileList)
                {
                    Console.WriteLine(ifile);
                }
                Console.WriteLine("");
                Environment.Exit(1);
            }
            return fileList[0];
        }

        static private string getHullFile(string dir)
        {
            var fileList = listAllFiles(dir, hullExtension);
            if(fileList.Count != 1)
            {
                Console.WriteLine("");
                Console.WriteLine("unable to load '*.hull' file in the directory!");
                foreach(var ifile in fileList)
                {
                    Console.WriteLine(ifile);
                }
                Console.WriteLine("");
                Environment.Exit(1);
            }
            return fileList[0];
        }

        static private string getSailListFile(string dir)
        {
            var fileList = listAllFiles(dir, sailListExtension);
            if (fileList.Count != 1)
            {
                Console.WriteLine("");
                Console.WriteLine("unable to load '*.sailList' file in the directory!");
                foreach (var ifile in fileList)
                {
                    Console.WriteLine(ifile);
                }
                Console.WriteLine("");
                Environment.Exit(1);
            }
            return fileList[0];
        }

        static private string getTankListFile(string dir)
        {
            var fileList = listAllFiles(dir, tankListExtension);
            if (fileList.Count != 1)
            {
                Console.WriteLine("");
                Console.WriteLine("unable to load '*.tankList' file in the directory!");
                foreach (var ifile in fileList)
                {
                    Console.WriteLine(ifile);
                }
                Console.WriteLine("");
                Environment.Exit(1);
            }
            return fileList[0];
        }

        static private void clearFolder(string folder)
        {
            DirectoryInfo dir = new DirectoryInfo(folder);
            foreach (var fi in dir.GetFiles())
            {
                fi.Delete();
            }
            foreach (var fi in dir.GetDirectories())
            {
                clearFolder(fi.FullName);
                fi.Delete();
            }
        }

        static private void checkHullDirectory()
        {
            //- check if the hull directory exists
            if (!Directory.Exists(hullDirectory))
            {
                Console.WriteLine("");
                Console.WriteLine("no 'hull' directory is found!");
                Environment.Exit(1);
            }
        }

        static void runApplication(string nameApp)
        {
            var proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = nameApp,
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

        static void runApplicationRunArg(string nameApp)
        {
            var proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = nameApp,
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

        static void createHullModel()
        {
            //- create shape hull
            runApplication("tnbHydstcHullReader.exe");

            //- create hull body
            runApplication("tnbApiHydstcBodyMaker.exe");

            //- create model
            runApplication("tnbHydstcHullModelMaker.exe");
        }

        static void createTankModels()
        {
            var subs = Directory.GetDirectories(tanksDirectory).ToList();
            int i = 0;
            while (subs.Contains(i.ToString()))
            {
                Directory.SetCurrentDirectory(tanksDirectory + @"\" + i.ToString());

                //- create shape hull
                runApplication("tnbHydstcTankReader.exe");

                //- create hull body
                runApplication("tnbApiHydstcBodyMaker.exe");

                //- create model
                runApplication("tnbHydstcTankModelMaker.exe");

                i++;
            }
        }

        static void createBodySailModels()
        {
            var subs = Directory.GetDirectories(sailsDirectory).ToList();
            int i = 0;
            while (subs.Contains(i.ToString()))
            {
                Directory.SetCurrentDirectory(sailsDirectory + @"\" + i.ToString());

                //- create shape hull
                runApplication("tnbHydstcSailReader.exe");

                //- create hull body
                runApplication("tnbApiHydstcBodyMaker.exe");

                //- create model
                runApplication("tnbHydstcBodySailModelMaker.exe");

                i++;
            }
        }

        static void createShapeSailModels()
        {
            var subs = Directory.GetDirectories(sailsDirectory).ToList();
            int i = 0;
            while (subs.Contains(i.ToString()))
            {
                Directory.SetCurrentDirectory(sailsDirectory + @"\" + i.ToString());

                //- create model
                runApplication("tnbHydstcShapeSailModelMaker.exe");

                i++;
            }
        }

        static void createLateralSailModels()
        {
            var subs = Directory.GetDirectories(sailsDirectory).ToList();
            int i = 0;
            while (subs.Contains(i.ToString()))
            {
                Directory.SetCurrentDirectory(sailsDirectory + @"\" + i.ToString());

                //- create model
                runApplication("tnbApiHydstcLateralPlaneSailModelMaker.exe");

                i++;
            }
        }

        static void createSailModels(string currentPath)
        {
            if (Directory.Exists(tanksDirectory))
            {
                var subs = Directory.GetDirectories(tanksDirectory).ToList();
                int i = 0;
                while (subs.Contains(i.ToString()))
                {
                    Directory.SetCurrentDirectory(currentPath + @"\" + tanksDirectory + @"\" + i.ToString());

                    
                }
            }
        }

        static void checkFile(string dir, string extension)
        {
            var fileList = listAllFiles(dir, extension);
            if (fileList.Count != 1)
            {
                Console.WriteLine("");
                Console.WriteLine("unable to load '*." + extension + "' file in the directory!");
                foreach (var ifile in fileList)
                {
                    Console.WriteLine(ifile);
                }
                Console.WriteLine("");
                Environment.Exit(1);
            }
        }

        static void clearAllFilesAndFolders(DirectoryInfo di)
        {
            foreach(FileInfo file in di.GetFiles())
            {
                file.Delete();
            }

            foreach(DirectoryInfo dir in di.GetDirectories())
            {
                dir.Delete(true);
            }
        }

        static void Main(string[] args)
        {
            currentPath = Directory.GetCurrentDirectory();

            hullDirectory = currentPath + @"\hull";
            sailsDirectory = currentPath + @"\sails";
            tanksDirectory = currentPath + @"\tanks";

            {//- hull scope
                checkHullDirectory();

                //- check .shape file
                checkFile(hullDirectory, shapeExtension);

                createHullModel();
            }


            if (Directory.Exists(tanksDirectory))
            {
                createTankModels();
            }

            if (Directory.Exists(sailsDirectory))
            {
                //- check type file
                if(!File.Exists(sailsDirectory + @"\system\type"))
                {
                    Console.WriteLine("");
                    Console.WriteLine("unable to load the 'type' file");
                    Console.WriteLine("");
                    Environment.Exit(1);
                }

                string text = File.ReadAllText(sailsDirectory + @"\system\type");
                if(text == "profileArea")
                {
                    Directory.SetCurrentDirectory(sailsDirectory);

                    runApplication("tnbApiHydstcProfileAreaSailModelMaker.exe");
                }
                else if(text == "constArea")
                {
                    Directory.SetCurrentDirectory(sailsDirectory);

                    runApplication("tnbApiHydstcConstAreaSailModelMaker.exe");
                }
                else if(text == "body")
                {
                    createBodySailModels();
                }
                else if(text == "shape")
                {
                    createShapeSailModels();
                }
                else if(text == "lateralPlane")
                {
                    createLateralSailModels();
                }
                else
                {
                    Console.WriteLine("");
                    Console.WriteLine(" Wrong type of sail has been detected!");
                    Console.WriteLine(" Make sure you have selected one of these sail modeler:");
                    Console.WriteLine(" - body");
                    Console.WriteLine(" - shape");
                    Console.WriteLine(" - constArea");
                    Console.WriteLine(" - profileArea");
                    Console.WriteLine(" - lateralPlane");
                    Console.WriteLine("");
                }
            }

            //- create tank list
            if(Directory.Exists(tanksDirectory))
            {
                var subs = Directory.GetDirectories(tanksDirectory).ToList();
                if(subs.Contains("0"))
                {
                    Directory.SetCurrentDirectory(tanksDirectory);

                    runApplicationRunArg("tnbHydstcModelList");
                }
            }

            //- create sail list
            if(Directory.Exists(sailsDirectory))
            {
                var fileList = listAllFiles(sailsDirectory, ".hsmodel");
                if(fileList.Count > 0)
                {

                    //- copy the file

                    var modelFile = getSingleFile(sailsDirectory, ".hsmodel");

                    if(!Directory.Exists(sailsDirectory + @"\0"))
                    {
                        DirectoryInfo di = Directory.CreateDirectory(sailsDirectory + @"\0");
                        di.Attributes = FileAttributes.Directory | FileAttributes.Hidden;
                    }

                    string sourceFile = Path.Combine(sailsDirectory, modelFile);
                    string destFile = Path.Combine(sailsDirectory + @"\0", modelFile);

                    File.Copy(sourceFile, destFile, true);

                    //- change the current path
                    Directory.SetCurrentDirectory(sailsDirectory);

                    //- run the application
                    runApplicationRunArg("tnbHydstcModelList");

                    //- delete '0' folder
                    clearAllFilesAndFolders(new DirectoryInfo(sailsDirectory + @"\0"));
                }               

            }
        }
    }
}
