# General Algorithms & Utilities

Using the project
-----------------
Just add the headers and sources to your project's include folder.

The codes are:\
-Wall -Wextra clean on Clang++ 18 (even cleaner on -Weverything)\
-Wall clean on MSVC v19.41.34120.0\
Clean on Microsoft Native Recommended rules + optional rules\
Clean on LLVM clang-tidy all settings - some inactive rules

There are some unnecessary warnings so I disabled them.\
You can see them in *.props files and in FatSettings.cmake file.\
Also, I added FatRules.ruleset and .clang-tidy. You can take a look at them.

If you use Microsoft Visual Studio 2022, you can use Ctrl + M + O keyboard key combination to collapse all the methods and functions to read the code easily.
