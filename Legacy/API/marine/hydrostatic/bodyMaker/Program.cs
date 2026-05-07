using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace tnbApiHydstcBodyMaker
{
    class Program
    {

        //static string extension1 = "hsshape";
        static string extension2 = "hsssects";
        static string extension3 = "hsdsects";
        static string extension4 = "hsasects";
        static string extension5 = "hsasectsr";
        static string extension6 = "hsslst";


        static string getFirstFileName(DirectoryInfo dir)
        {
            string file =
                dir.GetFiles()
                .Select(fi => fi.Name)
                .FirstOrDefault(name => name != "Thumbs.db");
            return file;
        }

        static void removeFiles(string path, string extension)
        {
            var files = Directory.GetFiles(path, "*." + extension, SearchOption.TopDirectoryOnly).ToList();
            foreach(string name in files)
            {
                try
                {
                    if(File.Exists(Path.Combine(path,name)))
                    {
                        File.Delete(Path.Combine(path, name));
                    }
                }
                catch(IOException ioExp)
                {
                    Console.WriteLine(ioExp.Message);
                    Environment.Exit(1);
                }
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

        static void Main(string[] args)
        {

            Console.WriteLine("This application is aimed to create a body from a shape.");
            Console.WriteLine("");
            Console.WriteLine("");
            Console.WriteLine("Retrieving sections of the shape...");
            Console.WriteLine("Starting the tnbHydstcDiscretizeSections application:");
            Console.WriteLine("");

            var root = Directory.GetCurrentDirectory();

            runApplicationRunArg("tnbHydstcShapeSections");

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcShapeSections application is completed(1/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Discretizing the edges of the sections...");
            Console.WriteLine("Starting the tnbHydstcDiscretizeSections application:");


            runApplicationRunArg("tnbHydstcDiscretizeSections");

            //removeFiles(root, extension2);

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcDiscretizeSections application is completed(2/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Analyzing the sections...");
            Console.WriteLine("Starting the tnbHydstcSectionAnalysis application:");

            runApplicationRunArg("tnbHydstcSectionAnalysis");

            //removeFiles(root, extension3);

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcSectionAnalysis application is completed(3/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Reporting the Analyzing of the sections...");
            Console.WriteLine("Starting the tnbHydstcSectionAnalysisReport application:");

            runApplicationRunArg("tnbHydstcSectionAnalysisReport");

            //removeFiles(root, extension4);

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcSectionAnalysisReport application is completed(4/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Making the sections...");
            Console.WriteLine("Starting the tnbHydstcSectionCreator application:");

            runApplicationRunArg("tnbHydstcSectionCreator");

            //removeFiles(root, extension5);

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcSectionCreator application is completed(5/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Making the body...");
            Console.WriteLine("Starting the tnbHydstcBodyMaker application:");

            runApplicationRunArg("tnbHydstcBodyMaker");

            //removeFiles(root, extension6);

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcBodyMaker application is completed(6/6), successfully!");
        }
    }
}
