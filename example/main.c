#include <rum.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#include <stdio.h>

int main(void) {
	if(!rum_init("Example", 640, 480))
		return 1;
	int w, h, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("hxbunny.jpg", &w, &h, &channels, 4);
	while(!rum_check_event(RUM_EVENT_QUIT)) {
		rum_copy_image(channels == 4 ? RUM_RGBA : RUM_RGB, data, w, h, 0, 0);
		rum_update_screen();
	}
	rum_terminate();
	return 0;
}


