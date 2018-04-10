using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SnakeProject
{
    class Program
    {
        static void Main(string[] args)
        {
            Snake game = new Snake(25,100);
            game.printMap();

            Console.ReadKey();
        }
    }
}
