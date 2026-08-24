#include "gui.h"

WINDOW *create_win(int rows, int cols, int starty, int startx)
{
    WINDOW *win = newwin(rows, cols, starty, startx);
    if(win == NULL){
        return NULL;
    }
    box(win, 0, 0);

    wrefresh(win);

    return win;
}

void print_controls(WINDOW *win)
{
    mvwprintw(win, 1, 2, "A => Append at the end");
    mvwprintw(win, 1, 30, "I => Insert");

    mvwprintw(win, 2, 2, "R => Remove address");
    mvwprintw(win, 2, 30, "D => Delete book");

    mvwprintw(win, 3, 2, "Q => Quit");
    mvwprintw(win, 3, 30, "P => Refresh book");

    mvwprintw(win, 5, 2, "F1 => Find by name");
    mvwprintw(win, 6, 2, "F2 => Find by surname");
    mvwprintw(win, 5, 30, "F3 => Find by email");
    mvwprintw(win, 7, 2, "F4 => Find by phone number");
    mvwprintw(win, 6, 30, "F5 => Find by position");

}

void print_list(struct node *list, WINDOW *win)
{
    int i=1;
    struct node *temp = list;
    while(temp != NULL){
            mvwprintw(win, i, 1, "%-12s |%-15s |%-32s |%-15s\n", temp->addr->name, temp->addr->surname,
        temp->addr->email, temp->addr->phone_number);
        temp = temp->next;
        i++;
    }
}

void print_arr(WINDOW *win, struct address *arr, int count)
{
    for(int i = 0; i < count; i++){
        struct address addr = *(arr + i);
        mvwprintw(win, i+1, 1, "%-12s |%-15s |%-32s |%-15s\n", addr.name, addr.surname,
        addr.email, addr.phone_number);
    }
}

int draw_gui(struct node **list, char *error_msg)
{
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int row,col;
    getmaxyx(stdscr, row, col);


    int height_output = row;
    int width_output = (col / 2) - 1;
    int starty_output = 0;
    int startx_output = 0;

    WINDOW *win_output = create_win(height_output, width_output, starty_output, startx_output);
    if(win_output == NULL){
        return -1;
    }

	int height_control = (row / 2) - 1;
	int width_control = col / 2;
	int starty_control = 0;
	int startx_control = col / 2;	

    WINDOW *win_control = create_win(height_control, width_control, starty_control, startx_control);
    if(win_control == NULL){
        return -1;
    }

    int height_logs = (row / 2);
    int width_logs = col / 2 ;
    int starty_logs = (row / 2);
    int startx_logs = col / 2;
    WINDOW *win_logs = create_win(height_logs, width_logs, starty_logs, startx_logs);
    if(win_logs == NULL)
    {
        return -1;
    }
    keypad(win_logs, TRUE);

    if(error_msg != NULL){
        print_log(win_logs, error_msg);
    }
    else{
       print_list(*list, win_output); 
    }
    wrefresh(win_output);

    print_controls(win_control);
    wrefresh(win_control);

    int ret = 0;
    while(ret != 1){
        ret = control_handler(win_logs, win_output, list);
    }
    if(ret == -1){
        return -1;
    }

    return 1;
}

int control_handler(WINDOW *win_logs, WINDOW *win_output, struct node **list)
{
    int ret;
    int ch;
    int pos;
    int count;
    struct node *entry;
    struct address *found_addr = NULL;
    char value[32];
    char log_msg[60];

    wrefresh(win_logs);
    switch(ch = wgetch(win_logs)){
    case 'A': ;

        entry = malloc(sizeof(struct node));
        if(entry == NULL){
            return -1;
        }
        ret = get_input_full_entry(win_logs, list, entry);
        if(ret == 1){
            add_entry_end(list, entry);
            print_log(win_logs, "Succesfully added new entry to the end of the list");
            print_output_list(win_output, *list);
        }
        else{
            free(entry);
        }
        break;
        //==================================================================================
    case 'I': ;
        pos = get_position(win_logs);
        if(pos == -1){
            print_log(win_logs, "Bad position");
            break;
        }
        entry = malloc(sizeof(struct node));
        if(entry == NULL){
            return -1;
        }
        ret = get_input_full_entry(win_logs, list, entry);
        if(ret > 0){
            ret = add_entry_pos(list, entry, pos);
            if(ret == -2){
                free(entry->addr);
                free(entry);
                print_log(win_logs, "Bad position");
                break;
            }
            print_log(win_logs, "Succesfully added new entry at the specified position");
            print_output_list(win_output, *list);
        } else{
            free(entry);
        }
        break;
        //==================================================================================
    case 'R': ;
        pos = get_position(win_logs);
        if(pos == -1){
            break;
        }
        ret = delete_entry_pos(list, pos);
        if(ret > 0){
            print_output_list(win_output, *list);
            print_log(win_logs, "Specified node has been succesfully removed");
        }else if(ret == -1){
            print_log(win_logs, "Bad position");
        }else if(ret == -2){
            print_log(win_logs, "List is empty");
        }
        break;
        //==================================================================================
    case 'D':
        delete_list(list);
        print_log(win_logs, "The address book has been deleted");
        print_output_list(win_output, *list);
        break;
        //==================================================================================
    case 'Q':
        return 1;
        break;
        //==================================================================================
    case 'P':
        print_output_list(win_output, *list);
        break;
    case KEY_F(1):
        get_single_input(win_logs, NAME, value);
        count = find_entry_value(NAME, *list, value, &found_addr);

        snprintf(log_msg, sizeof(log_msg), "Found %d addresses that match the criteria", count);
        print_log(win_logs, log_msg);
        print_output_arr(win_output, found_addr, count);
        if(found_addr != NULL){
           free(found_addr); 
        }
        break;
        //==================================================================================
    case KEY_F(2):
        get_single_input(win_logs, SURNAME, value);
        count = find_entry_value(SURNAME, *list, value, &found_addr);

        snprintf(log_msg, sizeof(log_msg), "Found %d addresses that match the criteria", count);
        print_log(win_logs, log_msg);
        print_output_arr(win_output, found_addr, count);
        if(found_addr != NULL){
            free(found_addr); 
        }
        break;
        //==================================================================================
    case KEY_F(3):
        get_single_input(win_logs, EMAIL, value);
        count = find_entry_value(EMAIL, *list, value, &found_addr);

        snprintf(log_msg, sizeof(log_msg), "Found %d addresses that match the criteria", count);
        print_log(win_logs, log_msg);
        print_output_arr(win_output, found_addr, count);
        if(found_addr != NULL){
            free(found_addr); 
        }
        break;
        //==================================================================================
    case KEY_F(4):
        get_single_input(win_logs, PHONE, value);
        count = find_entry_value(PHONE, *list, value, &found_addr);

        snprintf(log_msg, sizeof(log_msg), "Found %d addresses that match the criteria", count);
        print_log(win_logs, log_msg);
        print_output_arr(win_output, found_addr, count);
        if(found_addr != NULL){
            free(found_addr); 
        }
        break;
        //==================================================================================
    case KEY_F(5):
        pos = get_position(win_logs);
        found_addr = find_entry_pos(*list, pos);

        if(found_addr != NULL){
            print_output_arr(win_output, found_addr, 1);
        }else{
            print_log(win_logs, "Not found");
        }
        break;
        //==================================================================================
    }
    /*
    #define NAME 1
    #define SURNAME 2
    #define EMAIL 3
    #define PHONE 4
    */

    return 0;
}

int get_position(WINDOW *win)
{
    echo();
    werase(win);
    box(win, 0, 0);

    char pos[10];
    mvwprintw(win, 1, 1, "Enter position on the list: ");
    wgetnstr(win, pos, 10);
    noecho();

    char* end;
    int i = strtol(pos, &end, 10);
    if (pos == end){
        print_log(win, "Position must be a positive integer.");
        return -1;
    }

    return i;
}

int get_input_full_entry(WINDOW *win, struct node **list, struct node *entry)
{
    echo();
    werase(win);
    box(win, 0, 0);

    char name[sizeof(((struct address *)0)->name)];
    char surname[sizeof(((struct address *)0)->surname)];
    char email[sizeof(((struct address *)0)->email)];
    char phone_number[sizeof(((struct address *)0)->phone_number)];


    mvwprintw(win, 1, 1, "Enter name: ");
    wgetnstr(win, name, 11);

    mvwprintw(win, 2, 1, "Enter surname: ");
    wgetnstr(win, surname, 14);

    mvwprintw(win, 3, 1, "Enter email: ");
    wgetnstr(win, email, 31);

    mvwprintw(win, 4, 1, "Enter phone number: ");
    wgetnstr(win, phone_number, 14);

    noecho();

    struct address *addr = create_object(name, surname, email, phone_number);
    if(addr != NULL){
        *entry = create_node(addr);
    }
    else{
        print_log(win, "All fields must be filled correctly");
        return -1;
    }
    return 1;
}

void get_single_input(WINDOW *win, int type, char value[])
{
    echo();
    werase(win);
    box(win, 0, 0);
    switch(type)
    {
        case 1:
            mvwprintw(win, 1, 1, "Enter name: ");
            wgetnstr(win, value, 32);
            break;
        case 2:
            mvwprintw(win, 1, 1, "Enter surname: ");
            wgetnstr(win, value, 32);
            break;
        case 3:
            mvwprintw(win, 1, 1, "Enter email: ");
            wgetnstr(win, value, 32);
            break;
        case 4:
            mvwprintw(win, 1, 1, "Enter phone number: ");
            wgetnstr(win, value, 32);
            break;
        default: ;
            
    }
    noecho();

}

void print_log(WINDOW *win_logs, char *log_text)
{
    werase(win_logs);
    box(win_logs, 0, 0);
    mvwprintw(win_logs, 1, 2, "%s\n", log_text);
    wrefresh(win_logs);
}

void print_output_list(WINDOW *win_output, struct node *list)
{
    werase(win_output);
    box(win_output, 0, 0);
    print_list(list, win_output);
    wrefresh(win_output);
}

void print_output_arr(WINDOW *win_output, struct address *arr, int count)
{
    werase(win_output);
    box(win_output, 0, 0);
    print_arr(win_output, arr, count);
    wrefresh(win_output);
}