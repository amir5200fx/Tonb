using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace tnbApiBodyListMaker
{
    class tnbApiBodyListMaker
    {
        static string resultDirName = "result";
        static string newFileName = "myBody";

        static void checkTempDirectory()
        {
            string subPath = ".temp";
            bool exists = Directory.Exists(subPath);
            if (!exists)
            {
                Directory.CreateDirectory(subPath);
            }
        }

        static void checkResultDirectory()
        {
            string subPath = resultDirName;
            bool exists = Directory.Exists(subPath);
            if (!exists)
            {
                Directory.CreateDirectory(subPath);
            }
        }

        static string getFirstFileName(DirectoryInfo dir)
        {
            string file =
                dir.GetFiles()
                .Select(fi => fi.Name)
                .FirstOrDefault(name => name != "Thumbs.db");
            return file;
        }

        static void Main(string[] args)
        {            
            int iter = 0;
            while(Directory.Exists(iter.ToString()))
            {
                var dir = new DirectoryInfo(iter.ToString());
                var fileName = getFirstFileName(dir);

                { //- getting the result file
                    string newPath = Directory.GetCurrentDirectory();
                    FileInfo fileInfo = new FileInfo(iter.ToString() + @"\" + fileName);
                    if (fileInfo.Exists)
                    {
                        fileInfo.CopyTo(newPath + @"\" + newFileName, true);
                    }

                    {//- running the application
                        var proc = new Process
                        {
                            StartInfo = new ProcessStartInfo
                            {
                                FileName = "tnbApiBodyMaker.exe",
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
                    
                    File.Delete(newFileName);
                }

                { //- moving the result file into a list
                    FileInfo fileInfo = new FileInfo(resultDirName + @"\" + newFileName);
                    string newPath = resultDirName + @"\" + iter.ToString();

                    bool exists = Directory.Exists(newPath);
                    if (!exists)
                    {
                        Directory.CreateDirectory(newPath);
                    }

                    if (fileInfo.Exists)
                    {
                        fileInfo.MoveTo(newPath + @"\" + fileName);
                    }
                }

                iter++;
            }
        }
    }
}
