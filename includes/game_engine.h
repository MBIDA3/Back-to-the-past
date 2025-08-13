#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "story.h"
#include "inventor.h"

void start_game(Section sections[], int section_count, const char *story_filename);
int play_section(Section *section, Inventory *inventory, int current_section_id, const char *story_filename);
void narration(const char *narration);
void dialogues(Dialogue dialogues[], int dialogue_count);
int process_choices(Choice choices[], int choice_count, Inventory *inventory, int current_section_id, const char *story_filename) ;
void apply_consequence(int consequence_id, Inventory *inventory, const char *item_add, const char *item_remove);
int ending(const char *ending_text);
void collect_items(Section *section, Inventory *inventory);
void typewriter_effect(const char *text, int delay_ms);
void display_game_over_ascii();
void set_console_color(int color);

#endif