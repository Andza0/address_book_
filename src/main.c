#include <stdio.h>
#include "address.h"
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "gui.h"
#include <locale.h>
#include "parse.h"
#include <signal.h>

void sig_int_handler(int signal);
void set_signal_action(void);
volatile sig_atomic_t int_flag = 0;

int main(void){
    set_signal_action();

    initscr();

    WINDOW *win_output = NULL;
    WINDOW *win_logs = NULL;
    WINDOW *win_control = NULL;

    int ret;
    
    setlocale(LC_ALL, "");
    setenv("NCURSES_NO_UTF8_ACS", "1", 1);

    ret = draw_gui(&win_output, &win_logs, &win_control);
    if(ret == -1){
        perror("Nepavyko sukurti lango: ");
        goto cleanup;
    }

    struct node *list = NULL;

    char *home_dir = getenv("HOME");
    char *csv_file = "addresses.csv";

    char file_dir[40];
    snprintf(file_dir, sizeof(file_dir), "%s/%s", home_dir, csv_file);


    FILE *stream;   

    if((stream = fopen(file_dir, "r"))){
        ret = parse_csv(stream, &list);
        if(ret != 1){
            print_log(win_logs, "Nepavyko nuskaityti failo");
        }
        fclose(stream);
    }
    print_output_list(win_output, list);

    ret = 0;
    while(ret != 1 && int_flag != 1){
        if(ret == KEY_RESIZE){
            delwin(win_output);
            delwin(win_logs);
            delwin(win_control);
            ret = draw_gui(&win_output, &win_logs, &win_control);
            if(ret == -1){
                perror("Nepavyko sukurti lango: ");
                goto cleanup;
            }
            print_output_list(win_output, list);
        }
        ret = control_handler(win_logs, win_output, &list);
    }

    cleanup:
        delwin(win_output);
        delwin(win_logs);
        delwin(win_control);
        endwin();
        delete_list(&list);

    return 0;
}

void sig_int_handler(int signal)
{
    if(signal == SIGINT){
       int_flag = 1; 
    }
    
}

void set_signal_action(void)
{
    struct sigaction sig_int;
    bzero(&sig_int, sizeof(sig_int));
    sig_int.sa_handler = &sig_int_handler;


    sigaction(SIGINT, &sig_int, NULL);
}