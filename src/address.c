#include "address.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct address *create_object(char *name, char *surname, char *email, char *phone_number){
    struct address *ret = malloc(sizeof(struct address));
    if(ret == NULL){
        return NULL;
    }
    if(name == NULL || surname == NULL || email == NULL || phone_number == NULL){
        return NULL;
    }
    if(strcmp(name, "") == 0|| strcmp(surname, "")  == 0|| strcmp(email, "")  == 0|| strcmp(phone_number, "") == 0){
        return NULL;
    }

    strncpy(ret->name, name, sizeof(ret->name));
    strncpy(ret->surname, surname, sizeof(ret->surname));
    strncpy(ret->email, email, sizeof(ret->email));
    strncpy(ret->phone_number, phone_number, sizeof(ret->phone_number));


    ret->name[sizeof(ret->name) - 1] = '\0';
    ret->surname[sizeof(ret->surname) - 1] = '\0';
    ret->email[sizeof(ret->email) - 1] = '\0';
    ret->phone_number[sizeof(ret->phone_number) - 1] = '\0';

    return ret;
}