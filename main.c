#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "includes/game_engine.h"
#include "includes/story.h"
#include "includes/inventor.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char selected_file[256]; // Pour stocker le chemin de l'histoire sélectionnée

    // Sélection de l'histoire
    if (!select_story(selected_file)) {
        printf("Erreur : Aucune histoire sélectionnée. Le programme va quitter.\n");
        return 1;
    }


    Section sections[MAX_SECTIONS];
    int section_count = load_story(selected_file, sections);

    if (section_count == 0) {
        printf("Erreur : Impossible de charger l'histoire. Vérifiez le fichier sélectionné.\n");
        return 1;
    }

    printf("Bienvenue dans  !\n");
    display_back_to_the_past();
    printf("\n");
    display_story_title(selected_file);
    start_game(sections, section_count,selected_file);

    return 0;
}
