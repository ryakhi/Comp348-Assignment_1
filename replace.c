//By Ryan Anthony Khireddine 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment1.h"

int main(int argc, char *argv[]){

    if (argc != 2){ //Checks for the single command line argument
        fprintf(stderr, "Usage: %s <search_phrase>\n", argv[0]);
        return 1; //Returns a non-zero number, 1, to indicate an error
    }

    char *target_string = argv[1];

    FileUpdate *report_list = NULL; //Initializes the report list
    int num_updates = 0; //The intial size is zero 

    printf("Search Target: %s\n", target_string);
    printf("Starting directory traversal...\n"); 

    traverse_directory(".", target_string, &report_list, &num_updates);  //Calls the traversal function
    print_report(report_list, num_updates, target_string); //Reports and cleans-up 
 
    free_report_data(report_list, num_updates); //Frees te allocated memory

    return 0; 
}