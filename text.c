//By Ryan Anthony Khireddine 

#include "assignment1.h"

extern void add_update_to_list(FileUpdate **updates_list, int *list_size, FileUpdate new_update); //Declares the helper function from traversal.c

static void to_uppercase(char *str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

static int find_and_replace(char *buffer, const char *target_string) { //FOr the search function
    int count = 0;
    char *current_pos = buffer;
    size_t target_len = strlen(target_string);

    if (target_len == 0) {
        return 0;
    }

    while (*current_pos != '\0') { //Loops through the buffer
        
        if (strncasecmp(current_pos, target_string, target_len) == 0) { //If there is a match. strncasecmp performs a case-insenisitve comparaison. I found this out with this source: https://www.ibm.com/docs/en/i/7.4.0?topic=functions-strncasecmp-compare-strings-without-case-sensitivity
            
            to_uppercase(current_pos, target_len); //The match is found so it converts it to uppercase
            count++;
            current_pos += target_len; //Advances pointer
        } 
        else { //If theres no match
            current_pos++;
        }
    }
    return count;
}

char *read_file_to_buffer(const char *file_path, long *file_size) { //For the full implementation of the file reader
    FILE *fp;
    char *buffer = NULL;

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        perror("Error opening the file");
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0) { //Determines the file size
        fclose(fp);
        return NULL;
    }
    *file_size = ftell(fp); 
    rewind(fp); //Resets file pointer (from https://www.tutorialspoint.com/c_standard_library/c_function_rewind.htm)

    buffer = (char *)malloc((*file_size) + 1); //Dynamically allocates a buffer using mallo, and I added c +1 for null terminator
    if (buffer == NULL) {
        perror("Error allocating memory buffer");
        fclose(fp);
        return NULL;
    }
    
    size_t bytes_read = fread(buffer, 1, *file_size, fp); //Reads the entire content
    if (bytes_read != *file_size) {
        fprintf(stderr, "Error reading file content.\n");
        free(buffer); 
        fclose(fp);
        return NULL;
    }

    buffer[*file_size] = '\0'; // Null-terminate
    fclose(fp);

    return buffer;
}

int process_file(const char *file_path, const char *target_string, FileUpdate **updates_list, int *list_size) { //The main file processing function, which uses the reader
    long file_size = 0;
    char *content = read_file_to_buffer(file_path, &file_size);
    if (content == NULL) return 0;
    int nbOfChanges = 0; 
    nbOfChanges = find_and_replace(content, target_string);

if (nbOfChanges > 0) {
        
        FILE *fp_out = fopen(file_path, "w"); // If changes were made, it writes the modified content back to the original file. ALso, "w" empties the file
        if (fp_out == NULL) {
            perror("Error opening file for writing");
        } 
        else {
            if (fwrite(content, 1, file_size, fp_out) != file_size) {
                fprintf(stderr, "Error writing back to file: %s\n", file_path); //Writes the modified buffer back to the disk file. 
            }
            fclose(fp_out);
        
            FileUpdate new_update; //Adds the update to report list 
            new_update.fileName = strdup(file_path); //Uses strdup/malloc to copy the file path 
            new_update.changeCount = nbOfChanges;

            if (new_update.fileName != NULL) {
                add_update_to_list(updates_list, list_size, new_update); //Grows the list using my function in the traversal.c
            } 
            else {
                perror("Error allocating memory for file name in report");
                free(content); 
                return 0;
            }
        }
    }

    if (content != NULL) {
        free(content); 
    }
    return nbOfChanges;
}