using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace tnbApiDiscretize
{
    class Program
    {

        static public string systemDirectoty = "system";
        static public string appName = "tnbDiscretizeShape";

        static void checkSystemDirectory()
        {
            string subPath = "system";
            bool exists = Directory.Exists(subPath);
            if (!exists)
            {
                Directory.CreateDirectory(subPath);
            }
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

        static void Main(string[] args)
        {
            checkSystemDirectory();

            var parentDirectory = Directory.GetCurrentDirectory();
            var globalSystemFilePath = Path.Combine(parentDirectory, systemDirectoty, appName);
            bool exists = File.Exists(globalSystemFilePath);
            if (!exists)
            {
                Console.WriteLine("");
                Console.WriteLine("no system file has been found for the application: " + appName);
                Console.WriteLine("");

                Environment.Exit(1);
            }

            var subs = Directory.GetDirectories(parentDirectory).ToList();
            int i = 0;
            while(subs.Contains(i.ToString()))
            {
                var subPath = Path.Combine(parentDirectory, i.ToString());
                Directory.SetCurrentDirectory(subPath);

                bool deleteSubDir = false;
                if(!Directory.Exists(systemDirectoty))
                {
                    deleteSubDir = true;
                    Directory.CreateDirectory(systemDirectoty);

                    var destPath = Path.Combine(subPath, systemDirectoty, appName);
                    File.Copy(globalSystemFilePath, destPath, true);
                }

                bool hasMesh = false;

                {
                    var proc = new Process
                    {
                        StartInfo = new ProcessStartInfo
                        {
                            FileName = "tnbHasShapeMesh",
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

                    if(proc.ExitCode == 0)
                    {
                        hasMesh = true;
                    }
                    else if(proc.ExitCode == 1)
                    {
                        hasMesh = false;
                    }
                    else if(proc.ExitCode > 1)
                    {
                        Environment.Exit(1);
                    }
                    
                }

                if(!hasMesh)
                {
                    var proc = new Process
                    {
                        StartInfo = new ProcessStartInfo
                        {
                            FileName = appName,
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

                if(deleteSubDir)
                {
                    clearFolder(Path.Combine(subPath, systemDirectoty));
                }

                i++;
            }
        }
    }
}
