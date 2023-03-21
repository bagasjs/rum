/**************************************************************************************
 *
 *  MIT License
 *
 *  Copyright (c) 2023 Bagas J. Sitanggang
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 ************************************************************************************/
#include "rum.h"

#include <stdint.h>
#include <stdbool.h>

#include <stdlib.h>
#include <memory.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define CGMATH_IMPLEMENTATION
#include <cgmath.h>

typedef struct {
    GLFWwindow* glfw_window;
    bool initialized;
    uint32_t vertex_array, vertex_buffer, index_buffer, shader_program;
    
    struct {
        uint32_t texture;
        uint8_t* data;
        uint64_t data_size;
        uint64_t width, height;
        RumImageFormat format;
        bool updated;
    } image;
} RumContext;

const char* vert_shader_source = 
    "#version 330 core\n"
    "layout(location = 0) in vec2 a_position;\n"
    "layout(location = 1) in vec2 a_texCoords;\n"
    "out vec2 v_texCoords;\n"
    "void main()\n"
    "{\n"
        "v_texCoords = a_texCoords;\n"
        "gl_Position =vec4(a_position.x, a_position.y, 0.0, 1.0);\n"
    "}";

const char* frag_shader_source = 
    "#version 330 core\n"
    "layout(location = 0) out vec4 o_color;\n"
    "in vec2 v_texCoords;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
        "o_color = texture(u_texture, v_texCoords);\n"
    "}\n";

static RumContext RUM = {0};

bool rum_init(const char* screen_title, int32_t screen_width, int32_t screen_height) {
    if(RUM.initialized)
        return false;
    if(!glfwInit())
        return false;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    RUM.glfw_window = glfwCreateWindow((int)screen_width, (int)screen_height, screen_title, NULL, NULL);

    RUM.image.width = screen_width;
    RUM.image.height = screen_height;
    RUM.image.format = RUM_RGBA;
    RUM.image.data_size = sizeof(char) * RUM.image.format * screen_width * screen_height;
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
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)8);

    glGenBuffers(1, &RUM.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RUM.index_buffer);
    uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glGenTextures(1, &RUM.image.texture);
    glActiveTexture(GL_TEXTURE0);
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

void rum_copy_image(RumImageFormat src_format, const uint8_t* image_data, uint64_t image_width, uint64_t image_height, int32_t px, int32_t py) {
    for(int dy = 0; dy < image_height; ++dy) {
        int target_y = py + dy;
        if(0 <= target_y && target_y < (int) RUM.image.height) {
            for(int dx = 0; dx < image_width; ++dx) {
                int target_x = px + dx;
                if(0 <= target_x && target_x < RUM.image.width) {
                    int source_index = (dy * image_width + dx) * RUM.image.format;
                    int target_index = (target_y * RUM.image.width + target_x) * RUM.image.format;
                    for(int i = 0; i < src_format; ++i) {
                        RUM.image.data[target_index + i] = image_data[source_index + i];
                    }
                    if(src_format < 4) {
                        RUM.image.data[target_index + 3] = 255;
                    }
                }
            }
        }
    }

    RUM.image.updated = true;
}

void rum_update_screen()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RUM.index_buffer);
    glBindVertexArray(RUM.vertex_array);
    glUseProgram(RUM.shader_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, RUM.image.texture);
    if(RUM.image.updated) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (GLsizei)RUM.image.width, (GLsizei)RUM.image.height, GL_RGBA, GL_UNSIGNED_BYTE, RUM.image.data);
        RUM.image.updated = false;
    }
    glUniform1i(glGetUniformLocation(RUM.shader_program, "u_texture"), 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(RUM.glfw_window);
}