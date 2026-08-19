#include <stdio.h>
#include "address.h"
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>

#define DELIMITER ","

void parse_csv(FILE *stream, struct node **list);

int main(void){

    struct node *list = NULL;

    char *csv_file = "addresses.csv";
    FILE *stream;

    if((stream = fopen(csv_file, "r")) == NULL){
        perror("Klaida atidarant faila:");
        exit(1);
    }
    parse_csv(stream, &list);
    fclose(stream);

    print_list(list);

    delete_list(list);

    return 0;
}

void parse_csv(FILE *stream, struct node **list){
    char line[120];

    while(fgets(line, sizeof(line), stream) != NULL){
        char *name = strtok(line, DELIMITER);
        char *surname = strtok(NULL, DELIMITER);
        char *email = strtok(NULL, DELIMITER);
        char *phone_number = strtok(NULL, DELIMITER);
        size_t pos = strcspn(phone_number, "\r\n");
        phone_number[pos] = '\0';
        
        //printf("%s\n",name);
        struct address *addr;
        addr = create_object(name, surname, email, phone_number);
        struct node *entry = malloc(sizeof(struct node));
        if(entry == NULL){
            perror("Nepavyko priskirti atminties: ");
            exit(1);
        }
        *entry = create_node(addr);
        add_entry_end(list, entry);
        
    }
}