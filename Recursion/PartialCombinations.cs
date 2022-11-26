using System.Diagnostics;

namespace Recursion
{
    internal class Combinations
    {
        public static void partialcombine(String s, String first, int start, int count, int fixcount)
        {
            for (int i = start; i <= s.Length - count; i++)
            {
                if (first.Length + 1 == fixcount)
                {
                    Console.WriteLine(first + s[i]);
                }

                if (count > 1)
                {
                    partialcombine(s, first + s[i], i + 1, count - 1, fixcount);
                }
            }
        }

        public static int Main(String[] args)
        {
            Stopwatch clock = Stopwatch.StartNew();

            partialcombine("ABCDE", "", 0, 3, 3);

            clock.Stop();
            Console.WriteLine("\n{0} ms", clock.ElapsedMilliseconds);

            return 0;
        }
    }
}
