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

struct node create_node(struct address *addr)
{
    struct node new;
    new.addr = addr;
    new.next = NULL;

    return new;
}

void add_entry_end(struct node **list, struct node *entry)
{
    if(*list == NULL){
        *list = entry;
    } else {
        struct node *temp = *list;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = entry;
    }
    return;
}

int add_entry_pos(struct node **list, struct node *entry, int pos)
{
    if(pos == 0){
        entry->next = (*list);
        *list = entry;

        return 1;
    }
    else
    {
        if(*list == NULL){
            return -2;
        }
        int count = 0;

        struct node *temp = *list;
        while(count != pos - 1){
            if(temp->next != NULL){
                temp = temp->next;
                count++;
            }
            else{
                return -2;
            }

        }
        entry-> next = temp->next;
        temp->next = entry;
    }
    return 1;

}
int delete_entry_pos(struct node **list, int pos)
{
    if(*list == NULL){
        return -2;
    }
    if(pos == 0){
        if((*list)->next == NULL){
            free((*list)->addr);
            free(*list);
            *list = NULL;
            return 1;
        }
        (*list)->addr = (*list)->next->addr;
        (*list)->next = (*list)->next->next;
    }
    else{
        int count = 0;

        struct node *temp = *list;
        while(count != pos - 1){
            if(temp->next == NULL){
                return -1;
            }
            temp = temp->next;
            count++;
        }
        if(temp->next->next == NULL){
            free(temp->next->addr);
            free(temp->next);
            temp->next = NULL;
        }
        else{
            free(temp->next->addr);
            temp->next = temp->next->next;
        }
    }
    return 1;

}

void delete_list(struct node **list)
{   
    struct node *to_delete = *list;
    while (*list != NULL) {
        *list = (*list)->next;
        free(to_delete->addr);
        free(to_delete);
        to_delete = *list;
    }
    *list = NULL;
}

struct address *find_entry_pos(struct node *list, int pos)
{
    if(list == NULL){
        return NULL;
    }
    int count = 0;

    struct node *temp = list;
    while(count != pos){
        if(temp->next != NULL){
            temp = temp->next;
            count++;
        }
        else{
            return NULL;
        }
    }
    return temp->addr;
}

/*
#define NAME 1
#define SURNAME 2
#define EMAIL 3
#define PHONE 4
*/

int find_entry_value(int type, struct node *list, char *value, struct address **found_addr)
{
    int count = 0;
    switch(type){
        case 1:
            count = find_entry_name(list, value, found_addr);
            break;
        case 2:
            count = find_entry_surname(list, value, found_addr);
            break;
        case 3:
            count = find_entry_email(list, value, found_addr);
            break;
        case 4:
            count = find_entry_phone(list, value, found_addr);
            break;
        default:
            return -1;
            break;
    }

    return count;
}

int find_entry_name(struct node *list, char *value, struct address **found_addr)
{
    struct node *temp = list;
    int count = 0;
    while(temp != NULL){
        if(strcmp(temp->addr->name, value) == 0){
            struct address *temp_realloc = realloc(*found_addr, (count + 1) * sizeof(struct address));
            if(temp_realloc == NULL){
                return -1;
            }
            *found_addr = temp_realloc;
            (*found_addr)[count] = *(temp->addr);
            count++;
        }
        temp = temp->next;
    }
    return count;
}

int find_entry_surname(struct node *list, char *value, struct address **found_addr)
{
    struct node *temp = list;
    int count = 0;
    while(temp != NULL){
        if(strcmp(temp->addr->surname, value) == 0){
            *found_addr = realloc(*found_addr, (count + 1) * sizeof(struct address));
            if(*found_addr == NULL){
                return -1;
            }
            (*found_addr)[count] = *(temp->addr);
            count++;
        }
        temp = temp->next;
    }
    return count;
}

int find_entry_email(struct node *list, char *value, struct address **found_addr)
{
    struct node *temp = list;
    int count = 0;
    while(temp != NULL){
        if(strcmp(temp->addr->email, value) == 0){
            *found_addr = realloc(*found_addr, (count + 1) * sizeof(struct address));
            if(*found_addr == NULL){
                return -1;
            }
            (*found_addr)[count] = *(temp->addr);
            count++;
        }
        temp = temp->next;
    }
    return count;
}

int find_entry_phone(struct node *list, char *value, struct address **found_addr)
{
    struct node *temp = list;
    int count = 0;
    while(temp != NULL){
        if(strcmp(temp->addr->phone_number, value) == 0){
            *found_addr = realloc(*found_addr, (count + 1) * sizeof(struct address));
            if(*found_addr == NULL){
                return -1;
            }
            (*found_addr)[count] = *(temp->addr);
            count++;
        }
        temp = temp->next;
    }
    return count;
}
