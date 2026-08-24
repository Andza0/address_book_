#ifndef GUI_H_
#define GUI_H_

#include <ncurses.h>
#include "linked_list.h"
#include <signal.h>

WINDOW *create_win(int rows, int cols, int starty, int startx);

int draw_gui(WINDOW **win_output, WINDOW **win_logs, WINDOW **win_control);

void print_controls(WINDOW *win);
void print_output_arr(WINDOW *win_output, struct address *arr, int count);
void print_log(WINDOW *win_logs, char *log_text);
void print_output_list(WINDOW *win_output, struct node *list);
void print_arr(WINDOW *win, struct address *arr, int count);

int control_handler(WINDOW *win_logs, WINDOW *win_output, struct node **list);

int get_input_full_entry(WINDOW *win, struct node **list, struct node *entry);
void get_single_input(WINDOW *win, int type, char value[]);
int get_position(WINDOW *win);



#endif