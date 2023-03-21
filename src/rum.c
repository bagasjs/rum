#include "rum.h"

#include <stdio.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <stdlib.h>
#include <memory.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cgmath.h>

typedef struct {
    GLFWwindow* glfw_window;
    bool initialized;
    uint32_t vertex_array, vertex_buffer, index_buffer;
} RumContext;

typedef struct {
    vec2_t position, tex_coords;
    float tex_id;
} RumVertex;

static RumContext RUM = {0};

bool rum_init(const char* title, uint32_t width, uint32_t height) {
    if(RUM.initialized)
        return false;
    if(!glfwInit())
        return false;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    RUM.glfw_window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
    glfwMakeContextCurrent(RUM.glfw_window);

#if defined(__glad_h_)
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif

    glGenVertexArrays(1, &RUM.vertex_array);

    glGenBuffers(1, &RUM.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, RUM.vertex_buffer);

    glGenBuffers(1, &RUM.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RUM.index_buffer);

    RUM.initialized = true;
    return true;
}

void rum_terminate()
{
    if(RUM.initialized) {
        glDeleteBuffers(1, &RUM.vertex_buffer);
        glDeleteBuffers(1, &RUM.index_buffer);
        glDeleteVertexArrays(1, &RUM.vertex_array);
        glfwDestroyWindow(RUM.glfw_window);
        glfwTerminate();
    }
}

bool rum_check_event(int event) {
    glfwPollEvents();
    if(event == (int) RUM_EVENT_QUIT)
        return glfwWindowShouldClose(RUM.glfw_window);
    if((int)RUM_EVENT_KEY_START <= event && event <= RUM_EVENT_KEY_LAST) {
        return glfwGetKey(RUM.glfw_window, event) == GLFW_PRESS || glfwGetKey(RUM.glfw_window, event) == GLFW_REPEAT;
    }
    return false;
}

void rum_update_screen()
{
    glfwSwapBuffers(RUM.glfw_window);
}