#include "rum.h"

#include <stdio.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <stdlib.h>
#include <memory.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define CGMATH_IMPLEMENTATION
#include <cgmath.h>

void check_opengl_errors(const char* name)
{
    int check = 1;
    while (check)
    {
        const GLenum err = glGetError();
        switch (err)
        {
            case GL_NO_ERROR: check = 0; break;
            case 0x0500: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_ENUM"); break;
            case 0x0501: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_VALUE"); break;
            case 0x0502: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_OPERATION"); break;
            case 0x0503: printf("%s:%s", name, "OpenGL Error detected: GL_STACK_OVERFLOW"); break;
            case 0x0504: printf("%s:%s", name, "OpenGL Error detected: GL_STACK_UNDERFLOW"); break;
            case 0x0505: printf("%s:%s", name, "OpenGL Error detected: GL_OUT_OF_MEMORY"); break;
            case 0x0506: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_FRAMEBUFFER_OPERATION"); break;
            default: printf("%s:%i", "OpenGL Error detected: Unknown error code:", err); break;
        }
    }
}

typedef struct {
    GLFWwindow* glfw_window;
    bool initialized;
    uint32_t vertex_array, vertex_buffer, index_buffer, shader_program;
    
    struct {
        uint32_t texture;
        uint8_t* data;
        size_t data_size;
        size_t width, height;
        bool updated;
    } image;
} RumContext;

typedef struct {
    vec2_t position, tex_coords;
} RumVertex;

const char* vert_shader_source = 
    "#version 430 core\n"
    "layout(location = 0) in vec2 a_position;\n"
    "layout(location = 1) in vec2 a_texCoords;\n"
    "out vec2 v_texCoords;\n"
    "void main()\n"
    "{\n"
        "v_texCoords = a_texCoords;\n"
        "gl_Position =vec4(a_position, 0.0, 1.0);\n"
    "}";

const char* frag_shader_source = 
    "#version 430 core\n"
    "layout(location = 0) out vec4 o_color;\n"
    "in vec2 v_texCoords;\n"
    "uniform sampler2D u_Textures;\n"
    "void main()\n"
    "{\n"
        "outColor = texture();\n"
    "}\n";

static RumContext RUM = {0};

bool rum_init(const char* screen_title, int32_t screen_width, int32_t screen_height) {
    if(RUM.initialized)
        return false;
    if(!glfwInit())
        return false;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    RUM.glfw_window = glfwCreateWindow((int)screen_width, (int)screen_height, screen_title, NULL, NULL);

    RUM.image.width = screen_width;
    RUM.image.height = screen_height;
    RUM.image.data_size = sizeof(char) * RUM_RGBA * screen_width * screen_height;
    RUM.image.data = malloc(RUM.image.data_size);
    memset(RUM.image.data, 0, RUM.image.data_size);

    glfwMakeContextCurrent(RUM.glfw_window);

#if defined(__glad_h_)
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif

    glGenVertexArrays(1, &RUM.vertex_array);
    glBindVertexArray(RUM.vertex_array);

    uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
    glCompileShader(vert_shader);

    // Create and compile the fragment shader
    uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
    glCompileShader(frag_shader);
    // Link the vertex and fragment shader into a shader program
    RUM.shader_program = glCreateProgram();
    glAttachShader(RUM.shader_program, vert_shader);
    glAttachShader(RUM.shader_program, frag_shader);
    glLinkProgram(RUM.shader_program);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    glUseProgram(RUM.shader_program);

    glGenBuffers(1, &RUM.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, RUM.vertex_buffer);
    RumVertex vertices[] = {
        (RumVertex) { vec2(-1.0f, -1.0f), vec2(0.0f, 0.0f) },
        (RumVertex) { vec2( 1.0f, -1.0f), vec2(1.0f, 0.0f) },
        (RumVertex) { vec2( 1.0f,  1.0f), vec2(1.0f, 1.0f) },
        (RumVertex) { vec2(-1.0f,  1.0f), vec2(0.0f, 1.0f) },
    };
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(RumVertex), vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(RumVertex), (const void*) offsetof(RumVertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(RumVertex), (const void*) offsetof(RumVertex, tex_coords));

    glGenBuffers(1, &RUM.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RUM.index_buffer);
    uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glGenTextures(1, &RUM.image.texture);
    glBindTexture(GL_TEXTURE_2D, RUM.image.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei) RUM.image.width, (GLsizei) RUM.image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*) RUM.image.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)RUM_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)RUM_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

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
        free(RUM.image.data);
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

void rum_copy_image(RumImageFormat format, const uint8_t* image_data, uint64_t image_width, uint64_t image_height, int32_t px, int32_t py) {
    for(int32_t dy = 0; dy < (int32_t) image_height; ++dy) {
        int y = py + dy;
        if(0 <= y && y < (int32_t) RUM.image.height) {
            for(int32_t dx = 0; dx < (int32_t) image_width; ++dx) {
                int x = px + dx;
				if(0 <= x && x < (int) RUM.image.width) {
                    RUM.image.data[y * RUM.image.width + x + 0] = image_data[dy * image_width + dx + 0];
                    RUM.image.data[y * RUM.image.width + x + 1] = image_data[dy * image_width + dx + 1];
                    RUM.image.data[y * RUM.image.width + x + 2] = image_data[dy * image_width + dx + 2];
                    if(format == RUM_RGBA)
                        RUM.image.data[y * RUM.image.width + x + 3] = image_data[dy * image_width + dx + 3];
                    else
                        RUM.image.data[y * RUM.image.width + x + 3] = 0;
				}
            }
        }
    }
    RUM.image.updated = true;
}

void rum_update_screen()
{
    check_opengl_errors("TEST");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RUM.index_buffer);
    glBindVertexArray(RUM.vertex_array);
    glUseProgram(RUM.shader_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, RUM.image.texture);
    if(RUM.image.updated)
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (GLsizei)RUM.image.width, (GLsizei)RUM.image.height, GL_RGBA, GL_UNSIGNED_BYTE, RUM.image.data);
    RUM.image.updated = false;
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(RUM.glfw_window);
}