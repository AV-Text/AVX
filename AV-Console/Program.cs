using AVXFramework;
using Blueprint.Blue;

namespace AVConsole
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var singletons = new LocalStatementProcessor();
            var engine = new AVEngine();

            Console.WriteLine("Hello AV-Console!\n");

            bool done = false;
            do
            {
                bool error = false;
                Console.Write("> ");
                string input = Console.ReadLine().Trim();

                if (!string.IsNullOrEmpty(input))
                {
                    var tuple = engine.Execute(input);

                    error = !string.IsNullOrWhiteSpace(tuple.error);
                    if (error)
                    {
                        Console.Error.WriteLine(tuple.error);
                    }
                    if (tuple.stmt != null)
                    {
                        singletons.ProcessStatement(tuple.stmt, tuple.result); // process singletons and persistent settings

                        if (tuple.stmt.Commands != null)
                        {
                            int cnt = 0;
                            foreach (var segment in tuple.stmt.Commands.Searches)
                            {
                                if (++cnt == 1)
                                    Console.Error.WriteLine("SEARCH SEGMENTS:");

                                foreach (var line in segment.AsYaml())
                                {
                                    Console.WriteLine(line);
                                }
                            }
                            cnt = 0;
                            foreach (var segment in tuple.stmt.Commands.Assignments)
                            {
                                if (++cnt == 1)
                                    Console.Error.WriteLine("ASSIGNMENTS:");

                                foreach (var line in segment.AsYaml())
                                {
                                    Console.WriteLine(line);
                                }
                            }
                            cnt = 0;
                            foreach (var segment in tuple.stmt.Commands.Filters)
                            {
                                if (++cnt == 1)
                                    Console.Error.WriteLine("FILTERS:");

                                foreach (var line in segment.AsYaml())
                                {
                                    Console.WriteLine(line);
                                }
                            }
                            if (tuple.stmt.Commands.Display != null)
                            {
                                Console.Error.WriteLine("DISPLAY:");

                                foreach (var line in tuple.stmt.Commands.Display.AsYaml())
                                {
                                    Console.WriteLine(line);
                                }
                            }
                            if (tuple.stmt.Commands.Export != null)
                            {
                                Console.Error.WriteLine("EXPORT:");

                                foreach (var line in tuple.stmt.Commands.Export.AsYaml())
                                {
                                    Console.WriteLine(line);
                                }
                            }
                        }
                    }
                }
                else
                {
                    done = true;
                }
            }   while (!done);
        }
    }
}