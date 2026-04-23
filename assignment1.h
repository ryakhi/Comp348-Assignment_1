//By Ryan Anthony Khireddine

#ifndef ASSIGNMENT1_H
#define ASSIGNMENT1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

#define FILE_SUFFIX ".txt"

//THe report structure
typedef struct{
    char *fileName;
    int changeCount; 
} FileUpdate;

int parse_arguments(int argc, char *argv[]);

void traverse_directory (const char *path, const char *target_string, FileUpdate **update_list, int *list_size); //Will be in traversal.c to handle the recursive directory search

char *read_file_to_buffer(const char *file_path, long *file_size); //Inializes what I will need to handle file I/O
int process_file(const char *file_path, const char *target_string, FileUpdate **update_list, int *list_size); 

int compare_updates(const void *a, const void *b); //Initializes what I will need to generate and sort in the report

void print_report(FileUpdate *updates_list, int list_size, const char *target_string);  //Prints the final sorted report
void free_report_data(FileUpdate *updates_list, int list_size); 

#endif