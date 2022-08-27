#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void 
if_error (bool value, 
         const char* errmsg)
{
    if (value)
    {
        printf ("error:%s\n", errmsg);
        perror (errmsg);
        exit (EXIT_FAILURE);
    }
    

}