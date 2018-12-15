#ifndef PARSER
#define PARSER

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"
#include "../structures/structures.h"

#define DELIMITERS " \t\r\n"

#define ROW "Row:"
#define IO "IO:"
#define COMPONENT "Component:"

#define ARROW "->"

#define IS_SYNTAX_ERRROR  -1
#define IS_BORDERLINE      0
#define IS_HASH            1
#define IS_ROW             2
#define IS_IO              3
#define IS_COMPONENT       4

#define MAX_WORD 256

// Design Parsing //
int check_first_token(char *string);
void parse_hash_line(char * line);
void parse_row_line(char * line);
void parse_io(char *line);
void parse_design_file(FILE *fp);

// Graph Parsing //
void parse_graph_file(FILE *fp);
void write_graph_file(FILE *fp);

#endif