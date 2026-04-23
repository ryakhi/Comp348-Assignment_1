//By Ryan Anthony Khireddine

#include "assignment1.h"
 
void add_update_to_list(FileUpdate **updates_list, int *list_size, FileUpdate new_update) { //Manages the array of FileUpdate
 
    FileUpdate *new_list = (FileUpdate *)realloc(*updates_list, (*list_size + 1) * sizeof(FileUpdate));
 
    if (new_list == NULL) {
        perror("Error reallocating memory for report list");
        return; 
    }
 
    new_list[*list_size] = new_update; //Adds the new update to the end of the nrw list
    *updates_list = new_list; //Updates the pointer and size in the calling function
    (*list_size)++;
}
 
void traverse_directory(const char *path, const char *target_string, FileUpdate **updates_list, int *list_size) {
    
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
 
    dir = opendir(path); //Opens the firectory 
    if (dir == NULL) {
        perror("Error opening the directory");
        return; 
    }
 
    while ((entry = readdir(dir)) != NULL) { //Loops through the directory content. I Got some info on readdir using this source: https://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
        
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { //Skips the current directory and the parent directory 
            continue;
        }
 
        //This will dynamically build the full path for the entry
        int path_len = strlen(path);
        int name_len = strlen(entry->d_name);
        char *full_path = (char *)malloc(path_len + name_len + 2); //This is the allocated space for path 
        
        if (full_path == NULL) {
            perror("Memory allocation failed for full_path");
            break; 
        }
 
        sprintf(full_path, "%s/%s", path, entry->d_name); //Constructs the full path 
 
        if (lstat(full_path, &statbuf) < 0) {
            perror("Error getting type of directory entry");
            free(full_path);
            continue;
        }
        
        if (S_ISDIR(statbuf.st_mode)) {
        
            traverse_directory(full_path, target_string, updates_list, list_size); //Uses a Recursive call 
        } 
        else if (S_ISREG(statbuf.st_mode)) {
        
            int full_len = strlen(full_path);
            int suffix_len = strlen(FILE_SUFFIX); //THis uses the constant from assignment1.h
 
            if (full_len >= suffix_len && strcmp(full_path + full_len - suffix_len, FILE_SUFFIX) == 0) {
                
                int changes_made = process_file(full_path, target_string, updates_list, list_size); //Processes the text file 
 
                if (changes_made > 0) {
                    printf("  -> Updated file: %s (%d change(s))\n", full_path, changes_made);
                } else {
                    FileUpdate new_update;
                    new_update.fileName = strdup(full_path);
                    new_update.changeCount = 0;
                    if (new_update.fileName != NULL) {
                        add_update_to_list(updates_list, list_size, new_update);
                    }
                }
            }
        }
        free(full_path); 
    }
    closedir(dir);
}