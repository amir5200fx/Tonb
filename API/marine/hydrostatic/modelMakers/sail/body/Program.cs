using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace tnbApiHydstcHullModelMaker
{
    class Program
    {

        static string bodyDir = "body";

        static void checkBodyDirectory()
        {
            string subPath = bodyDir;
            bool exists = Directory.Exists(subPath);
            if (!exists)
            {
                Directory.CreateDirectory(subPath);
            }
        }

        static void checkSystemDirectory()
        {
            string subPath = "system";
            bool exists = Directory.Exists(subPath);
            if (!exists)
            {
                Directory.CreateDirectory(subPath);
            }
        }

        static void Main(string[] args)
        {
            checkBodyDirectory();
            checkSystemDirectory();

            {
                var proc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "tnbHydstcBodySailModelMaker.exe",
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
        }
    }
}
