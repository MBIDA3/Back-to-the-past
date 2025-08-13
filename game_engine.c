#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "includes/game_engine.h"
#include "includes/inventor.h"
#include "includes/save_load.h"
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"

void start_game(Section sections[], int section_count, const char *story_filename) {
    char replay_choice;
    do {
        int current_section_id = load_current_section(story_filename); // Charger la sauvegarde
        if (current_section_id == 0) {
            printf("Aucune sauvegarde trouvée pour %s. Nouvelle partie commencée.\n", story_filename);
            current_section_id = 0; // Commencer à la première section
        } else {
            printf("Sauvegarde chargée pour %s. Reprise à la section %d.\n", story_filename, current_section_id);
        }

        Inventory player_inventory;
        init_inventory(&player_inventory); // Réinitialise l'inventaire

        while (current_section_id != -1) {
            current_section_id = play_section(&sections[current_section_id], &player_inventory, current_section_id, story_filename);
        }

        printf("\n=== GAME OVER ===\n");
        printf("Voulez-vous rejouer ? (o/n) : ");
        scanf(" %c", &replay_choice);

        while (getchar() != '\n');
    } while (replay_choice == 'o' || replay_choice == 'O');

    printf("Merci d'avoir joué %s !\n", story_filename);
}


int play_section(Section *section, Inventory *inventory, int current_section_id, const char *story_filename) {
    narration(section->narration);
    collect_items(section, inventory);

    if (section->dialogue_count > 0) {
        dialogues(section->dialogues, section->dialogue_count);
    }

    if (section->choice_count > 0) {
        return process_choices(section->choices, section->choice_count, inventory, current_section_id, story_filename);
    }

    if (section->is_ending) {
        ending(section->narration);
        return -1;
    }
    return -1;
}

void narration(const char *narration) {
//    printf("\033[37m\n--- Narrateur ---\n%s\n\033[0m", narration);
    typewriter_effect(narration,30);
    printf("\n");
}


void dialogues(Dialogue dialogues[], int dialogue_count) {
    for (int i = 0; i < dialogue_count; i++) {
        if (strcmp(dialogues[i].character, "Vous") == 1 || strcmp(dialogues[i].character, "\"Vous\"") == 0) {
            // Affiche "Vous" en vert
            printf("\033[32m%s\033[0m\n", dialogues[i].character);
        } else {
            // Affiche les autres personnages en rouge
            printf("\033[31m%s\033[0m\n", dialogues[i].character);
        }
        // Affiche le texte des dialogues en blanc
//        printf("\033[37m%s\033[0m\n", dialogues[i].text);
        typewriter_effect(dialogues[i].text,50);
    }
}

int process_choices(Choice choices[], int choice_count, Inventory *inventory, int current_section_id, const char *story_filename) {
    printf("\n--- Vos Choix  ---\n");

    for (int i = 0; i < choice_count; i++) {
        printf("\033[32m%d. %s\033[0m\n", i + 1, choices[i].text); // Vert pour choix normaux
    }
    printf("\033[33m%d. Consulter l'inventaire\033[0m\n", choice_count + 1);
    printf("\033[33m%d. Sauvegarder la partie\033[0m\n", choice_count + 2);

    int choice;
    printf("Votre choix : ");
    scanf("%d", &choice);

    while (choice < 1 || choice > choice_count + 2) {
        printf("\033[31mChoix invalide. Veuillez réessayer : \033[0m");
        scanf("%d", &choice);
    }

    if (choice == choice_count + 1) {
        display_inventory(inventory); // Affiche l'inventaire
        return process_choices(choices, choice_count, inventory, current_section_id, story_filename);
    }

    if (choice == choice_count + 2) { // Sauvegarder
        save_current_section(story_filename, current_section_id); // Passe le nom de l'histoire et la section
//        printf("Partie sauvegardée.\n");
        return process_choices(choices, choice_count, inventory, current_section_id, story_filename);
    }

    return choices[choice - 1].next_section_id;

}


void apply_consequence(int consequence_id, Inventory *inventory, const char *item_add, const char *item_remove) {
    if (consequence_id == 1 && item_add && strlen(item_add) > 0) {
        if (add_item(inventory, item_add)) {
            printf("Vous avez obtenu : %s\n", item_add);
        }
    } else if (consequence_id == 2 && item_remove && strlen(item_remove) > 0) {
        if (remove_item(inventory, item_remove)) {
            printf("Vous avez utilisé : %s\n", item_remove);
        } else {
            printf("Erreur : %s n'est pas dans votre inventaire.\n", item_remove);
        }
    }
}


int ending(const char *ending_text) {
    printf("\n=== Fin de l'histoire ===\n");
    typewriter_effect(ending_text, 50);

    char replay_choice;
    display_game_over_ascii();
    printf("Voulez-vous rejouer ? (o/n) : ");
    scanf(" %c", &replay_choice); // Nettoyer le buffer d'entrée pour éviter des erreurs de lecture
    while (getchar() != '\n');

    return (replay_choice == 'o' || replay_choice == 'O') ? 1 : 0;
}


void typewriter_effect(const char *text, int delay_ms) {
    while (*text) {
        usleep(delay_ms * 1000);
        putchar(*text++);
        fflush(stdout);
    }
    putchar('\n');
}
void collect_items(Section *section, Inventory *inventory) {
    for (int i = 0; i < section->item_count; i++) {
        if (section->items[i].type == ITEM_ADD) {
            add_item(inventory, section->items[i].name);
//            printf("Vous avez obtenu : %s\n", section->items[i].name);
        } else if (section->items[i].type == ITEM_REMOVE) {
            if (remove_item(inventory, section->items[i].name)) {
//                printf("Vous avez utilisé : %s\n", section->items[i].name);
            } else {
                printf("Erreur : %s n'est pas dans votre inventaire.\n", section->items[i].name);
            }
        }
    }
}

void display_game_over_ascii() {
    printf("\n");
    printf("  ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ \n");
    printf(" ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
    printf(" ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n");
    printf(" ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║██║   ██║██╔══╝  ██╔═══╝ \n");
    printf(" ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝╚██████╔╝███████╗██║     \n");
    printf("  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═╝     \n");
    printf("\n");
    printf("                            === GAME OVER ===\n");
    printf("   Merci d'avoir joué !\n");
    printf("\n");
}

void display_back_to_the_past() {
    printf(YELLOW "\n");
    printf("\n");
    printf("  █████═╗  █████╗  ██████╗██╗  ██╗    ████████╗ ██████╗     ████████╗██╗  ██╗███████╗     \n");
    printf("  ██╔═██║ ██╔══██╗██╔════╝██║ ██╔╝    ╚══██╔══╝██╔═══██╗    ╚══██╔══╝██║  ██║██╔════╝     \n");
    printf("  █████═║ ███████║██║     █████╔╝        ██║   ██║   ██║       ██║   ███████║█████╗       \n");
    printf("  ██══██╝ ██╔══██║██║     ██╔═██╗        ██║   ██║   ██║       ██║   ██╔══██║██╔══╝       \n");
    printf("  █████═╗ ██║  ██║╚██████╗██║  ██╗       ██║   ╚██████╔╝       ██║   ██║  ██║███████╗     \n");
    printf("  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝       ╚═╝    ╚═════╝        ╚═╝   ╚═╝  ╚═╝╚══════╝     \n");
    printf(GREEN"\n");
    printf("                          ██████═╗ █████╗ ███████╗████████╗\n");
    printf("                          ██   ██║██╔══██╗██╔════╝╚══██╔══╝\n");
    printf("                          ██████╔╝███████║███████╗   ██║\n");
    printf("                          ██╔═══╝ ██╔══██║╚════██║   ██║\n");
    printf("                          ██║     ██║  ██║███████║   ██║\n");
    printf("                          ╚═╝     ╚═╝  ╚═╝╚══════╝   ╚═╝\n");
    printf("                              === BACK TO THE PAST ===             \n");
    printf(RESET "\n");
}
