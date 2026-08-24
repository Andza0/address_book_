#include <stdio.h>
#include "address.h"
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "gui.h"
#include <locale.h>
#include "parse.h"

int main(void){

    struct node *list = NULL;

    char *home_dir = getenv("HOME");
    char *csv_file = "addresses.csv";

    char file_dir[40];
    snprintf(file_dir, sizeof(file_dir), "%s/%s", home_dir, csv_file);


    FILE *stream;

    char *error_msg = NULL;
    int ret;

    if((stream = fopen(file_dir, "r"))){
        ret = parse_csv(stream, &list);
        if(ret != 1){
            error_msg = "Nepavyko nuskaityti failo";
        }
        fclose(stream);
    }


    setlocale(LC_ALL, "");
    setenv("NCURSES_NO_UTF8_ACS", "1", 1);

    initscr();

    ret = draw_gui(&list, error_msg);

    if(ret == -1){
        endwin();
        delete_list(&list);
        return 1;
    }
    endwin();
    delete_list(&list);

    return 0;
}