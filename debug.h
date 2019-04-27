#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#define DP(...)     fprintf(stderr, __VA_ARGS__)
#define ENTRY_LOG   fprintf(stderr, "%s\t:\t%s\n", __FILE__, __func__)

#endif // DEBUG_H

