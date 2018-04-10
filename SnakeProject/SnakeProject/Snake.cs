using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SnakeProject
{
    class Snake
    {
        public List<String> snake { get; set; }
        public int Score { get; set; }
        public string  food { get; set; }
        public int fX { get; set; }
        public int fY { get; set; }
        public int mX { get; set; }
        public int mY { get; set; }
        public int x { get; set; }
        public int y { get; set; }
        Random rnd;
        public Snake(int x,int y)
        {
            mX = x;
            mY = y;
            rnd = new Random();
            snake = new List<string>();

        }
       

        public void menu()
        {
            Console.ForegroundColor = ConsoleColor.DarkMagenta;
            Console.SetCursorPosition(10, 3);
            Console.Write("Welcome to my Snake Game");
            Console.SetCursorPosition(10, 5);
            Console.Write("Plays with W-A-S-D");
            Console.SetCursorPosition(10, 7);
            Console.Write("Good Lock");
        }
        public void printMap()
        {
            for (int i = 0; i < mX; i++)
            {
                Console.BackgroundColor = ConsoleColor.Red;
                Console.SetCursorPosition(1,i);
                Console.Write(" ");
                Console.SetCursorPosition(mY, i);
                Console.Write(" ");
                for (int i = 0; i < length; i++)
                {

                }
            }
        }
        
    }
}
