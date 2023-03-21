#ifndef RUM_H_
#define RUM_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    RUM_RGB = 3,
    RUM_RGBA = 4,
} RumImageFormat;

typedef enum {
    RUM_LINEAR = 0x2600,
    RUM_NEAREST = 0x2601,
    RUM_NEAREST_MIPMAP_NEAREST = 0x2700,
    RUM_LINEAR_MIPMAP_NEAREST = 0x2701,
    RUM_NEAREST_MIPMAP_LINEAR = 0x2702,
    RUM_LINEAR_MIPMAP_LINEAR = 0x2703,
} RumFilter;


bool rum_init(const char* screen_title, int32_t screen_width, int32_t screen_height);
void rum_terminate();
bool rum_check_event(int event);
void rum_update_screen();

void rum_copy_image(RumImageFormat format, const uint8_t* image_data, uint64_t image_width, uint64_t image_height, int32_t x, int32_t y);

typedef enum {
    /** Unknown Event */
    RUM_EVENT_UNKNOWN                = -1,
    
    /** Window Event*/
    RUM_EVENT_QUIT                   = 1,

    /** Keyboard Event */
    RUM_EVENT_KEY_SPACE              = 32,
    RUM_EVENT_KEY_APOSTROPHE         = 39,
    RUM_EVENT_KEY_COMMA              = 44,
    RUM_EVENT_KEY_MINUS              = 45,
    RUM_EVENT_KEY_PERIOD             = 46,
    RUM_EVENT_KEY_SLASH              = 47,
    RUM_EVENT_KEY_0                  = 48,
    RUM_EVENT_KEY_1                  = 49,
    RUM_EVENT_KEY_2                  = 50,
    RUM_EVENT_KEY_3                  = 51,
    RUM_EVENT_KEY_4                  = 52,
    RUM_EVENT_KEY_5                  = 53,
    RUM_EVENT_KEY_6                  = 54,
    RUM_EVENT_KEY_7                  = 55,
    RUM_EVENT_KEY_8                  = 56,
    RUM_EVENT_KEY_9                  = 57,
    RUM_EVENT_KEY_SEMICOLON          = 59,
    RUM_EVENT_KEY_EQUAL              = 61,
    RUM_EVENT_KEY_A                  = 65,
    RUM_EVENT_KEY_B                  = 66,
    RUM_EVENT_KEY_C                  = 67,
    RUM_EVENT_KEY_D                  = 68,
    RUM_EVENT_KEY_E                  = 69,
    RUM_EVENT_KEY_F                  = 70,
    RUM_EVENT_KEY_G                  = 71,
    RUM_EVENT_KEY_H                  = 72,
    RUM_EVENT_KEY_I                  = 73,
    RUM_EVENT_KEY_J                  = 74,
    RUM_EVENT_KEY_K                  = 75,
    RUM_EVENT_KEY_L                  = 76,
    RUM_EVENT_KEY_M                  = 77,
    RUM_EVENT_KEY_N                  = 78,
    RUM_EVENT_KEY_O                  = 79,
    RUM_EVENT_KEY_P                  = 80,
    RUM_EVENT_KEY_Q                  = 81,
    RUM_EVENT_KEY_R                  = 82,
    RUM_EVENT_KEY_S                  = 83,
    RUM_EVENT_KEY_T                  = 84,
    RUM_EVENT_KEY_U                  = 85,
    RUM_EVENT_KEY_V                  = 86,
    RUM_EVENT_KEY_W                  = 87,
    RUM_EVENT_KEY_X                  = 88,
    RUM_EVENT_KEY_Y                  = 89,
    RUM_EVENT_KEY_Z                  = 90,
    RUM_EVENT_KEY_LEFT_BRACKET       = 91, 
    RUM_EVENT_KEY_BACKSLASH          = 92, 
    RUM_EVENT_KEY_RIGHT_BRACKET      = 93, 
    RUM_EVENT_KEY_GRAVE_ACCENT       = 96, 
    RUM_EVENT_KEY_WORLD_1            = 161,
    RUM_EVENT_KEY_WORLD_2            = 162,

    /* Function keys */
    RUM_EVENT_KEY_ESCAPE             = 256,
    RUM_EVENT_KEY_ENTER              = 257,
    RUM_EVENT_KEY_TAB                = 258,
    RUM_EVENT_KEY_BACKSPACE          = 259,
    RUM_EVENT_KEY_INSERT             = 260,
    RUM_EVENT_KEY_DELETE             = 261,
    RUM_EVENT_KEY_RIGHT              = 262,
    RUM_EVENT_KEY_LEFT               = 263,
    RUM_EVENT_KEY_DOWN               = 264,
    RUM_EVENT_KEY_UP                 = 265,
    RUM_EVENT_KEY_PAGE_UP            = 266,
    RUM_EVENT_KEY_PAGE_DOWN          = 267,
    RUM_EVENT_KEY_HOME               = 268,
    RUM_EVENT_KEY_END                = 269,
    RUM_EVENT_KEY_CAPS_LOCK          = 280,
    RUM_EVENT_KEY_SCROLL_LOCK        = 281,
    RUM_EVENT_KEY_NUM_LOCK           = 282,
    RUM_EVENT_KEY_PRINT_SCREEN       = 283,
    RUM_EVENT_KEY_PAUSE              = 284,
    RUM_EVENT_KEY_F1                 = 290,
    RUM_EVENT_KEY_F2                 = 291,
    RUM_EVENT_KEY_F3                 = 292,
    RUM_EVENT_KEY_F4                 = 293,
    RUM_EVENT_KEY_F5                 = 294,
    RUM_EVENT_KEY_F6                 = 295,
    RUM_EVENT_KEY_F7                 = 296,
    RUM_EVENT_KEY_F8                 = 297,
    RUM_EVENT_KEY_F9                 = 298,
    RUM_EVENT_KEY_F10                = 299,
    RUM_EVENT_KEY_F11                = 300,
    RUM_EVENT_KEY_F12                = 301,
    RUM_EVENT_KEY_F13                = 302,
    RUM_EVENT_KEY_F14                = 303,
    RUM_EVENT_KEY_F15                = 304,
    RUM_EVENT_KEY_F16                = 305,
    RUM_EVENT_KEY_F17                = 306,
    RUM_EVENT_KEY_F18                = 307,
    RUM_EVENT_KEY_F19                = 308,
    RUM_EVENT_KEY_F20                = 309,
    RUM_EVENT_KEY_F21                = 310,
    RUM_EVENT_KEY_F22                = 311,
    RUM_EVENT_KEY_F23                = 312,
    RUM_EVENT_KEY_F24                = 313,
    RUM_EVENT_KEY_F25                = 314,
    RUM_EVENT_KEY_KP_0               = 320,
    RUM_EVENT_KEY_KP_1               = 321,
    RUM_EVENT_KEY_KP_2               = 322,
    RUM_EVENT_KEY_KP_3               = 323,
    RUM_EVENT_KEY_KP_4               = 324,
    RUM_EVENT_KEY_KP_5               = 325,
    RUM_EVENT_KEY_KP_6               = 326,
    RUM_EVENT_KEY_KP_7               = 327,
    RUM_EVENT_KEY_KP_8               = 328,
    RUM_EVENT_KEY_KP_9               = 329,
    RUM_EVENT_KEY_KP_DECIMAL         = 330,
    RUM_EVENT_KEY_KP_DIVIDE          = 331,
    RUM_EVENT_KEY_KP_MULTIPLY        = 332,
    RUM_EVENT_KEY_KP_SUBTRACT        = 333,
    RUM_EVENT_KEY_KP_ADD             = 334,
    RUM_EVENT_KEY_KP_ENTER           = 335,
    RUM_EVENT_KEY_KP_EQUAL           = 336,
    RUM_EVENT_KEY_LEFT_SHIFT         = 340,
    RUM_EVENT_KEY_LEFT_CONTROL       = 341,
    RUM_EVENT_KEY_LEFT_ALT           = 342,
    RUM_EVENT_KEY_LEFT_SUPER         = 343,
    RUM_EVENT_KEY_RIGHT_SHIFT        = 344,
    RUM_EVENT_KEY_RIGHT_CONTROL      = 345,
    RUM_EVENT_KEY_RIGHT_ALT          = 346,
    RUM_EVENT_KEY_RIGHT_SUPER        = 347,
    RUM_EVENT_KEY_MENU               = 348,
} RumEvent;

#define RUM_EVENT_KEY_START RUM_EVENT_KEY_SPACE
#define RUM_EVENT_KEY_LAST RUM_EVENT_KEY_MENU

#endif // RUM_H_