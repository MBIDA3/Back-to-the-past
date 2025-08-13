#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
    #include <sys/types.h>
#endif


void save_current_section(const char *story_filename, int current_section_id);
int load_current_section(const char *story_filename);
void create_save_folder();

#endif // SAVE_LOAD_H
