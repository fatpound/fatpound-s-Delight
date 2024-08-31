# General Algorithms & Utilities

Using the project
-----------------
Just add the headers and sources to your project's include folder.

The codes are:\
-Wall -Wextra clean on Clang++ 18\
-Wall clean on MSVC v19.41.34120.0

There are some disabled unnecessary warnings.\
You can see them in Visual Studio property sheet files and CMakeSetings_*.cmake files

If you use Microsoft Visual Studio 2022, you can use Ctrl + M + O keyboard key combination to collapse all the methods and functions to read the code easily.

Note : NONE of these classes support SIMD or other vectorizations. Except unique cases, there is no need to implement those whilst there is a pre-made or built libraries for almost any kind of job that needs to be done. The codes are just there to learn some of the algorithms while using latest C++ standards.
