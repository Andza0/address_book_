#ifndef ADDRESS_H_
#define ADDRESS_H_

#define NAME 1
#define SURNAME 2
#define EMAIL 3
#define PHONE 4

struct address{
    char name[12];
    char surname[15];
    char email[32];
    char phone_number[15];
};

struct address *create_object(char *name, char *surname, char *email, char *phone_number);

#endif