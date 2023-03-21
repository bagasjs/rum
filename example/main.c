#include "rum.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(!rum_init("Rum Example", 640, 480))
        exit(1);
    
    while(!rum_check_event(RUM_EVENT_QUIT))
    {
        rum_update_screen();
    }
    rum_terminate();
}