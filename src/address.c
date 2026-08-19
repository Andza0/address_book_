#include "address.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct address *create_object(char *name, char *surname, char *email, char *phone_number){
    struct address *ret = malloc(sizeof(struct address));
    if(ret == NULL){
        perror("Klaida priskiriant atminti: ");
        exit(1);
    }

    strcpy(ret->name, name);
    strcpy(ret->surname, surname);
    strcpy(ret->email, email);
    strcpy(ret->phone_number, phone_number);

    return ret;
}