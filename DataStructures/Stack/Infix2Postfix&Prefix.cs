namespace Stack
{
    internal class Program
    {
        static int[,] values = new int[7,2];
        static String valch = "+-*/^()";
        static String inf = "A+B*C-D/E*T+F-G"; // "A*(B^F+C)*D"

        static STC stack = new STC(inf.Length);

        static int Val(char k, int mode)
        {
            return values[valch.IndexOf(k), mode];
        }

        public static string StringRev(String s)
        {
            char[] w = s.ToCharArray();
            Array.Reverse(w);

            return new String(w);
        }

        static void Push(String txt)
        {
            stack.str[++stack.index] = txt;
        }

        static String Pop()
        {
            String temp = stack.str[stack.index];

            stack.str[stack.index--] = "";

            return temp;
        }

        static String Infix2Postfix(String infix)
        {
            String postfix = "";

            for (int i = 0; i < infix.Length; i++)
            {
                String k = infix[i].ToString();

                if ((k[0] >= 'A' && k[0] <= 'Z') || (k[0] >= 'a' && k[0] <= 'z'))
                {
                    postfix += k;
                }
                else if (k[0] == '+' || k[0] == '-' || k[0] == '*' || k[0] == '/' || k[0] == '^' || k[0] == '(' || k[0] == ')')
                {
                    if (stack.index > -1)
                    {
                        if ((k[0] == ')') || (Val(k[0], 0) <= Val(stack.str[stack.index][0], 1)))
                        {
                            while (k[0] == ')' ? stack.str[stack.index][0] != '(' : Val(k[0], 0) <= Val(stack.str[stack.index][0], 1))
                            {
                                postfix += stack.str[stack.index];
                                stack.str[stack.index--] = "";

                                if (stack.index == -1)
                                {
                                    break;
                                }
                            }

                            if (k[0] == ')')
                            {
                                stack.str[stack.index--] = "";
                            }
                        }
                    }

                    if (k[0] != ')')
                    {
                        Push(k);
                    }
                }
            }

            for (; stack.index > -1; postfix += Pop());

            return postfix;
        }

        static String Infix2Prefix(String infix)
        {
            char[] temp = StringRev(infix).ToCharArray();

            for (int i = 0; i < temp.Length; i++)
            {
                if (temp[i] == '(')
                {
                    temp[i] = ')';
                }
                else if (temp[i] == ')')
                {
                    temp[i] = '(';
                }
            }

            String prefix = new String(temp);

            return StringRev(Infix2Postfix(prefix));
        }

        static int Main(string[] args)
        {
            values[6, 0] =     values[6, 1] = -1; // ) -1 -1
            
            values[0, 0] =     values[0, 1] =  1; // +  1  1
            values[1, 0] =     values[1, 1] =  1; // -  1  1
            values[2, 0] =     values[2, 1] =  2; // *  2  2
            values[3, 0] =     values[3, 1] =  2; // /  2  2
            values[4, 0] =  4; values[4, 1] =  3; // ^  4  3
            values[5, 0] =  4; values[5, 1] =  0; // (  4  0

            Console.WriteLine(Infix2Prefix(inf));
            Console.WriteLine(Infix2Postfix(inf));

            return 0;
        }

        class STC
        {
            public String[] str;
            public int index = -1;

            public STC(int max_s)
            {
                str = new String[max_s];
            }
        }
    }
}
