#include "rum.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(!rum_init("Rum Example", 640, 480))
        exit(1);
    uint8_t image[] = { 255, 255, 255, 255 };

    while(!rum_check_event(RUM_EVENT_QUIT))
    {
        rum_copy_image(RUM_RGBA, image, 1, 1, 100, 100);
        rum_update_screen();
    }
    rum_terminate();
}