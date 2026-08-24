#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "address.h"
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include <string.h>
#include <ncurses.h>

struct node{
    struct address *addr;
    struct node *next;
};

/*
    Display all records in the address book

    Add new address to the book (to the end)

    Add new address indicating the position where to put it

    Delete address indicating its position in the book

    Delete whole address book

    Find address by position

    Find addressess by name, surname, email or phone number
*/

struct node create_node(struct address *addr);
void print_list(struct node *list, WINDOW *win);
void add_entry_end(struct node **list, struct node *entry);
int add_entry_pos(struct node **list, struct node *entry, int pos);
int delete_entry_pos(struct node **list, int pos);
void delete_list(struct node **list);
struct address *find_entry_pos(struct node *list, int pos);

int find_entry_value(int type, struct node *list, char *value, struct address **found_addr);

int find_entry_name(struct node *list, char *value, struct address **found_addr);
int find_entry_surname(struct node *list, char *value, struct address **found_addr);
int find_entry_email(struct node *list, char *value, struct address **found_addr);
int find_entry_phone(struct node *list, char *value, struct address **found_addr);

#endif