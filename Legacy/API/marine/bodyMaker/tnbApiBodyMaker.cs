using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Web;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tnbApiBodyMaker
{
    class tnbApiBodyMaker
    {
        static void checkTempDirectory()
        {
            string subPath = ".temp";
            bool exists = System.IO.Directory.Exists(subPath);
            if(!exists)
            {
                System.IO.Directory.CreateDirectory(subPath);
            }
        }

        static void checkResultDirectory()
        {
            string subPath = "result";
            bool exists = System.IO.Directory.Exists(subPath);
            if (!exists)
            {
                System.IO.Directory.CreateDirectory(subPath);
            }
        }

        static void Main(string[] args)
        {

            checkTempDirectory();
            checkResultDirectory();

            Console.WriteLine("This application is aimed to create a body from a shape.");
            Console.WriteLine("");
            Console.WriteLine("");
            Console.WriteLine("Retrieving sections of the shape...");
            Console.WriteLine("Starting the tnbHydstcDiscretizeSections application:");
            Console.WriteLine("");

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcShapeSections.exe",
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

                if(proc.ExitCode > 0)
                {
                    System.Environment.Exit(1);
                }
            }

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcShapeSections application is completed(1/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Discretizing the edges of the sections...");
            Console.WriteLine("Starting the tnbHydstcDiscretizeSections application:");

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcDiscretizeSections.exe",
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
                    System.Environment.Exit(1);
                }
            }

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcDiscretizeSections application is completed(2/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Analyzing the sections...");
            Console.WriteLine("Starting the tnbHydstcSectionAnalysis application:");

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcSectionAnalysis.exe",
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
                    System.Environment.Exit(1);
                }
            }

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcSectionAnalysis application is completed(3/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Reporting the Analyzing of the sections...");
            Console.WriteLine("Starting the tnbHydstcSectionAnalysisReport application:");

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcSectionAnalysisReport.exe",
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
                    System.Environment.Exit(1);
                }
            }

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcSectionAnalysisReport application is completed(4/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Making the sections...");
            Console.WriteLine("Starting the tnbHydstcSectionCreator application:");

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcSectionCreator.exe",
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
                    System.Environment.Exit(1);
                }
            }

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcSectionCreator application is completed(5/6), successfully!");

            Console.WriteLine("");
            Console.WriteLine("");

            Console.WriteLine("Making the body...");
            Console.WriteLine("Starting the tnbHydstcBodyMaker application:");

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcBodyMaker.exe",
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
                    System.Environment.Exit(1);
                }
            }

            Console.WriteLine("");
            Console.WriteLine("The tnbHydstcBodyMaker application is completed(6/6), successfully!");
        }
    }
}
