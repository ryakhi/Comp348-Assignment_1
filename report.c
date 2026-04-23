//By Ryan Anthony Khireddine
 
#include "assignment1.h"
 
int compare_updates(const void *a, const void *b) {
    
    const FileUpdate *update_a = (const FileUpdate *)a; // Casts the void pointers back to FileUpdate pointers
    const FileUpdate *update_b = (const FileUpdate *)b; // Casts the void pointers back to FileUpdate pointers
 
    if (update_b->changeCount != update_a->changeCount) {
        return update_b->changeCount - update_a->changeCount; //TO sort in descending order, I return b.count - a.count
    }
    return strcmp(update_a->fileName, update_b->fileName); //Alphabetical order for ties
}
 
void free_report_data(FileUpdate *updates_list, int list_size) {
    if (updates_list == NULL) 
        return;
 
    for (int i = 0; i < list_size; i++) {
        free(updates_list[i].fileName); // Frees the dynamically allocated filename string
    }
    free(updates_list); //Frees the array 
}
 
void print_report(FileUpdate *updates_list, int list_size, const char *target_string) { //Prints the final and sorted report
    char cwd[1024]; //The buffer for the currently working directory
    
    if (getcwd(cwd, sizeof(cwd)) == NULL) { //Gets the starting folder 
        perror("Error getting current working directory");
        strcpy(cwd, "UNKNOWN_PATH");
    }
 
    printf("\n--- Search and Replace Report ---\n");
    printf("Target String: %s\n", target_string);
    printf("Starting Folder: %s\n", cwd);
    printf("Total Files Updated: %d\n\n", list_size);
 
    if (list_size == 0) {
        printf("No changes were made to any files.\n");
        return;
    }
 
    qsort(updates_list, list_size, sizeof(FileUpdate), compare_updates); //SOrts the list
    printf("Files Modified (Sorted by Changes):\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < list_size; i++) {
        if (updates_list[i].fileName[0] == '.') {
            printf("  %s/%s: %d change(s)\n", cwd, updates_list[i].fileName + 2, updates_list[i].changeCount);
        } else {
            printf("  %s/%s: %d change(s)\n", cwd, updates_list[i].fileName, updates_list[i].changeCount);
        }
    }
    printf("-----------------------------------\n");
}