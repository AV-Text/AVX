using AVXFramework;

namespace AVConsole
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var engine = new AVEngine();

            Console.WriteLine("Hello AV-Console!\n");

            bool done = false;
            do
            {
                Console.Write("> ");
                string input = Console.ReadLine().Trim();

                if (!string.IsNullOrEmpty(input))
                {
                    var ignore = engine.Execute(input);
                }
                else
                {
                    done = true;
                }
            }   while (!done);
        }
    }
}