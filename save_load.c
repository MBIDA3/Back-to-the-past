#include <stdio.h>
#include <string.h>
#include "includes/save_load.h"


void save_current_section(const char *story_filename, int current_section_id) {
    // Construire le chemin du fichier de sauvegarde
    char save_filename[256];
    snprintf(save_filename, sizeof(save_filename), "%s_save.json", story_filename);

    FILE *file = fopen(save_filename, "w");
    if (!file) {
        printf("Erreur : Impossible de sauvegarder la partie.\n");
        return;
    }
    fprintf(file, "%d\n", current_section_id); // Sauvegarde l'ID de la section actuelle
    fclose(file);

    printf("Partie sauvegardée avec succès dans %s.\n", save_filename);
}

int load_current_section(const char *story_filename) {
    // Construire le chemin du fichier de sauvegarde
    char save_filename[256];
    snprintf(save_filename, sizeof(save_filename), "%s_save.json", story_filename);

    FILE *file = fopen(save_filename, "r");
    if (!file) {
        return 0; // Aucune sauvegarde trouvée
    }

    int current_section_id;
    fscanf(file, "%d", &current_section_id); // Lit l'ID de la section
    fclose(file);

    return current_section_id;
}
