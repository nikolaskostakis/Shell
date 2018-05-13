#ifndef PARSER
#define PARSER

#define DELIMITERS " \t\r\n"

/* Key Words used in the input file. */
#define ROW "Row:"
#define IO "IO:"
#define COMPONENT "Component:"

#define IS_SYNTAX_ERRROR  -1
#define IS_BORDERLINE      0
#define IS_HASH            1
#define IS_ROW             2
#define IS_IO              3
#define IS_COMPONENT       4

#define MAX_WORD 256

int check_first_token(char *string);
void parse_hash_line(char * line);
void parse_row_line(char * line);
void parse_io(char *line);
void parse_file(char *filename);

#endif