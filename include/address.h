#ifndef ADDRESS_H_
#define ADDRESS_H_

struct address{
    char name[60];
    char surname[60];
    char email[60];
    char phone_number[60];
};

struct address *create_object(char *name, char *surname, char *email, char *phone_number);

#endif