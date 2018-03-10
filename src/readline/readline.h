#ifndef READLINE
#define READLINE

#include <tcl/tcl.h>

#include "../main.h"

extern char *commands[];

void init_readline();

char **custom_completion(const char *text, int start, int end);

char *custom_completer(const char * text, int state);

#endif // READLINE