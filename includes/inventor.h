// inventor.h
#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_ITEMS 50
#define ITEM_NAME_LENGTH 50

typedef struct {
    char *items[MAX_ITEMS];
    int item_count;
    int points;
} Inventory;


void init_inventory(Inventory *inv);
int add_item(Inventory *inv,  char *item);
int remove_item(Inventory *inv,  char *item);
void display_inventory(const Inventory *inv);

#endif