#ifndef PARSE_H_
#define PARSE_H_

#define DELIMITER ","

#include <stdio.h>
#include "linked_list.h"
#include <string.h>
#include "address.h"

int parse_csv(FILE *stream, struct node **list);



#endif