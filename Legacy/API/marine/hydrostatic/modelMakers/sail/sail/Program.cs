using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace tnbApiHydstcSailModelMaker
{
    class Program
    {
        static string typeFile = @"system\type";

        static void checkSystemDirectory()
        {
            string subPath = "system";
            bool exists = Directory.Exists(subPath);
            if (!exists)
            {
                Directory.CreateDirectory(subPath);
            }
        }

        static void checkTypeFile()
        {       
            bool exists = File.Exists(typeFile);
            if(!exists)
            {
                File.CreateText(typeFile);
            }
        }

        static void Main(string[] args)
        {
            checkSystemDirectory();
            checkTypeFile();

            string text = File.ReadAllText(typeFile);

            if(text == "body")
            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbApiHydstcBodySailModelMaker.exe",
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
            else if(text == "shape")
            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbApiHydstcShapeSailModelMaker.exe",
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
            else if(text == "constArea")
            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbApiHydstcConstAreaSailModelMaker.exe",
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
            else if(text == "profileArea")
            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbApiHydstcProfileAreaSailModelMaker.exe",
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
            else if(text == "lateralPlane")
            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbApiHydstcLateralPlaneSailModelMaker.exe",
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
    }
}
