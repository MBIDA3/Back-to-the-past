#ifndef STORY_H
#define STORY_H

#define MAX_SECTIONS 100
#define MAX_DIALOGUES 5
#define MAX_CHOICES 5
#define MAX_ITEMS 10
#define MAX_NAME_LENGTH 50
#define MAX_TEXT_LENGTH 1000

#define ITEM_ADD 1
#define ITEM_REMOVE 2

typedef struct {
    int type;
    char name[MAX_NAME_LENGTH]; // Nom de l'objet
} Item;

typedef struct {
    char character[MAX_NAME_LENGTH];
    char text[MAX_TEXT_LENGTH];
} Dialogue;

typedef struct {
    char text[MAX_TEXT_LENGTH];
    int next_section_id;
    int consequence_id;
    char item_add[MAX_NAME_LENGTH];
    char item_remove[MAX_NAME_LENGTH];
    int points;                  // Points gagnés ou perdus pour ce choix
} Choice;


typedef struct {
    int id;
    char narration[MAX_TEXT_LENGTH];
    Dialogue dialogues[MAX_DIALOGUES];
    int dialogue_count;
    Choice choices[MAX_CHOICES];
    int choice_count;
    Item items[MAX_ITEMS];
    int item_count;
    int is_ending;
} Section;

int load_story(const char *filename, Section sections[]);
int select_story(char *selected_file);
void display_select_story();
void set_console_color(int color);
Section* get_section_by_id(Section sections[], int section_count, int id);
void display_story_title(const char *story_title);
void display_back_to_the_past();
#endif
