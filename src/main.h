#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <tcl8.5/tcl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>

#include "readline/readline.h"
#include "tcl/tcl.h"

#define NRM  "\x1B[0m"		// Normal Color
#define RED  "\x1B[31m"		// Red Color
#define GRN  "\x1B[32m"		// Green Color
#define YEL  "\x1B[33m"		// Yellow Color
#define BLU  "\x1B[34m"		// Blue Color
#define MAG  "\x1B[35m"		// Magenta Color
#define CYN  "\x1B[36m"		// Cyan Color
#define WHT  "\x1B[37m"		// White Color

// PATH_MAX is a definition in linux/limits.h
#define BUFFER_SIZE (PATH_MAX + 1)

#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1

#endif // MAIN