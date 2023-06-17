using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            // Get the current working directory
            string directory = Directory.GetCurrentDirectory();

            // Check if user has provided address argument
            string address;
            if (args.Length == 0)
            {
                address = directory;
            }
            else
            {
                // Get the address from the argument
                address = args[0];
            }

            // Create a unique filename with .PATH extension in the current working directory
            //string path = Path.Combine(directory, $"{Guid.NewGuid()}.PATH");
            string path = Path.Combine(directory, $".PATH");

            // Write the address to the file
            using (StreamWriter writer = new StreamWriter(path))
            {
                writer.WriteLine(address);
            }

            Console.WriteLine($"File created at: {path}");
        }
    }
}
