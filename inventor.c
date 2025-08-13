// inventor.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "includes/inventor.h"

void init_inventory(Inventory *inv) {
    inv->item_count = 0;
    for (int i = 0; i < MAX_ITEMS; i++) {
        inv->items[i] = NULL;
    }
    inv->points = 0; // Initialisation des points
}


int add_item(Inventory *inv,  char *item) {
//    printf("ADD_ITEM\n");
    if (inv->item_count >= MAX_ITEMS) {
        printf("Erreur : Inventaire plein !\n");
        return 0;
    }
//    printf("Addinv %p\n",inv);
    inv->items[inv->item_count] = malloc(strlen(item) + 1);
    if (!inv->items[inv->item_count]) {
        printf("Erreur : Échec de l'allocation de mémoire.\n");
        return 0;
    }
    strcpy(inv->items[inv->item_count], item);
    inv->item_count++;
    return 1;
}

int remove_item(Inventory *inv, char *item) {
    for (int i = 0; i < inv->item_count; i++) {
        if (strcmp(inv->items[i], item) == 0) {
//            printf("REMOVE_ITEM: Suppression de l'objet '%s'.\n", item);
            free(inv->items[i]);
            // Déplacer le dernier élément à l'emplacement de l'élément supprimé
            if (i != inv->item_count - 1) {
                inv->items[i] = inv->items[inv->item_count - 1];
            }
            // Nettoyer la dernière case et décrémenter item_count
            inv->items[inv->item_count - 1] = NULL;
            inv->item_count--;
            return 1; // Succès
        }
    }
    printf("REMOVE_ITEM: Objet '%s' introuvable dans l'inventaire.\n", item);
    return 0; // Échec : Objet non trouvé
}



void display_inventory(const Inventory *inv) {
//    printf("Dispinv %p",inv);
    printf("\n--- Inventaire ---\n");
    if (inv->item_count == 0) {
        printf("Votre inventaire est vide.\n");
    } else {
        for (int i = 0; i < inv->item_count; i++) {
            printf("- %s\n", inv->items[i]);
        }
    }
}