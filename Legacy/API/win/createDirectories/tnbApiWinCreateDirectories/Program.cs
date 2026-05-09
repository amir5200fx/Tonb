using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tnbApiWinCreateDirectories
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: CreateFolders <n>");
                return;
            }

            int n;
            if (!int.TryParse(args[0], out n))
            {
                throw new ArgumentException("The argument must be an integer.");
            }

            for (int i = 0; i < n; i++)
            {
                string folderName = i.ToString();
                Directory.CreateDirectory(folderName);
            }
        }
    }
}
