#include "parse.h"

int parse_csv(FILE *stream, struct node **list){
    char line[120];

    while(fgets(line, sizeof(line), stream) != NULL){

        if(strcmp(line, "\n") == 0){
            continue;
        }
        
        char *name = strtok(line, DELIMITER);
        char *surname = strtok(NULL, DELIMITER);
        char *email = strtok(NULL, DELIMITER);
        char *phone_number = strtok(NULL, DELIMITER);

        size_t pos = strcspn(phone_number, "\n");
        phone_number[pos] = '\0';
        
        struct address *addr;
        addr = create_object(name, surname, email, phone_number);
        if(addr == NULL){
            continue;
        }
        struct node *entry = malloc(sizeof(struct node));
        if(entry == NULL){
            return -1;
        }
        *entry = create_node(addr);
        add_entry_end(list, entry);
        
    }

    return 1;
}