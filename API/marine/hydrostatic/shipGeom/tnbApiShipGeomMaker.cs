using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace tnbApiShipGeomMaker
{
    class tnbApiShipGeomMaker
    {
        static string hullDirectory = "hull";
        static string tankDirectory = "tanks";
        static string sailsDirectory = "sails";

        static string resutDirectory = "result";

        private void ClearFolder(string folder)
        {
            DirectoryInfo dir = new DirectoryInfo(folder);
            foreach(var fi in dir.GetFiles())
            {
                fi.Delete();
            }
            foreach(var fi in dir.GetDirectories())
            {
                ClearFolder(fi.FullName);
                fi.Delete();
            }
        }

        static void Main(string[] args)
        {

            //- check if the hull directory exists
            if(!Directory.Exists(hullDirectory))
            {
                Console.WriteLine("");
                Console.WriteLine("no 'hull' directory is found!");
                Environment.Exit(1);
            }


        }
    }
}
