#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
/*
    Display all records in the address book

    Add new address to the book (to the end)

    Add new address indicating the position where to put it

    Delete address indicating its position in the book

    Delete whole address book

    Find address by position

    Find addressess by name, surname, email or phone number
*/

void print_list(struct node *list){
    struct node *temp = list;
    printf("========== Adresu knyga ==============================\n");
    while(temp != NULL){
        printf("| %s | %s | %s | %s |\n", temp->addr->name, temp->addr->surname,
        temp->addr->email, temp->addr->phone_number);
        temp = temp->next;
    }
    printf("======================================================\n");
}

struct node create_node(struct address *addr){
    struct node new;
    new.addr = addr;
    new.next = NULL;

    return new;
}

void add_entry_end(struct node **list, struct node *entry){
    printf("%s\n", entry->addr->name);
    if(*list == NULL){
        *list = entry;
    } else {
        struct node *temp = *list;
        //printf("%s\n", temp->addr->name);
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp = entry;
    }
    return;
}

void add_entry_pos(struct node list, int pos);
void delete_entry_pos(struct node list, int pos);

void delete_list(struct node *list){
    struct node *to_delete = list;
    while (list != NULL) {
        list = list->next;
        free(to_delete);
        to_delete = list;
    }
}

struct node find_entry_pos(struct node list, int pos);

struct node find_entry_value(struct node list, int type, char *value);

struct node find_entry_name(struct node list, char *value);
struct node find_entry_surname(struct node list, char *value);
struct node find_entry_email(struct node list, char *value);
struct node find_entry_phone(struct node list, char *value);