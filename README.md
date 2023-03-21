# RUM
A simple library to display an image into window. It just take an array of color and display it to the window there's no other complex API.

### API
```c
/// Core API

// Create context and window
bool rum_init(const char* screen_title, int32_t screen_width, int32_t screen_height); 

// Destroy context and window
void rum_terminate(void);

// Copy the image buffer into the context's image buffer
void rum_copy_image(RumImageFormat format, const uint8_t* image_data, uint64_t image_width, uint64_t image_height, int32_t x, int32_t y);

// Update the texture's data and draw into screen
void rum_update_screen(void);


/// Supporting
// Check if an event is happened (Check the header file for the list of events in the enum)
bool rum_check_event(int event);
```

### Example
To run this example you will need to grab the ["stb_image.h"](https://github.com/nothings/stb/blob/master/stb_image.h) header file.

```c
#include <rum.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void) {
	if(!rum_init("Example", 640, 480))
		return 1;
	int w, h, channels;
	// stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("circles.ppm", &w, &h, &channels, 4);
	while(!rum_check_event(RUM_EVENT_QUIT)) {
		rum_copy_image(channels == 4 ? RUM_RGBA : RUM_RGB, data, w, h, 100, 0);
		rum_update_screen();
	}
	rum_terminate();
	return 0;
}
```
