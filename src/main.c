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
#include <errno.h>

void sig_int_handler(int signal);
void sig_term_handler(int signal);
void sig_quit_handler(int signal);
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
        if(ret == 1){
            print_output_list(win_output, list);
        }
        fclose(stream);
    }
    else {
        print_log(win_logs, "Nepavyko nuskaityti saraso");
    }

    ret = 0;
    while(ret != 1 && int_flag != 1){
        if(ret == KEY_RESIZE){
            delwin(win_output);
            delwin(win_logs);
            delwin(win_control);
            erase();
            refresh();
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
void sig_term_handler(int signal)
{
    if(signal == SIGTERM){
       int_flag = 1; 
    }
    
}
void sig_quit_handler(int signal)
{
    if(signal == SIGQUIT){
       int_flag = 1; 
    }
    
}


void set_signal_action(void)
{
    struct sigaction sig_int;
    bzero(&sig_int, sizeof(sig_int));
    sig_int.sa_handler = &sig_int_handler;

    struct sigaction sig_term;
    bzero(&sig_term, sizeof(sig_term));
    sig_term.sa_handler = &sig_term_handler;
    

    struct sigaction sig_quit;
    bzero(&sig_quit, sizeof(sig_quit));
    sig_quit.sa_handler = &sig_quit_handler;

    sigaction(SIGINT, &sig_int, NULL);
    sigaction(SIGTERM, &sig_term, NULL);
    sigaction(SIGQUIT, &sig_quit, NULL);
}