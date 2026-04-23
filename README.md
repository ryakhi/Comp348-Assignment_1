# Comp348-Assignment_1
This is a search and replace application in C, that recursively traverses directories, modifies text files, and generates a sorted report with dynamic memory management (malloc/free)

How to Compile:
bashgcc -Wall traversal.c text.c report.c replace.c

How to Run:
bash./a.out <search_word>
For example, to search for and uppercase every occurrence of the word apple:
bash./a.out apple

What It Does:
Takes a single search word as a command-line argument
Recursively walks the current directory and all subdirectories
Opens every .txt file it finds
Replaces every case-insensitive match of the search word with its uppercase version (e.g. apple → APPLE, Apple → APPLE)
Writes the modified content back to the original file
Prints a final report listing every .txt file found, sorted by number of changes (descending), with alphabetical ordering for ties
