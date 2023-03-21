// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <cgmath.h>
// #include <stdint.h>
// #include <stdio.h>

// const char* vert_source =
// 	"#version 330 core\n"
// 	"layout(location = 0) in vec2 a_position;\n"
// 	"void main()\n"
// 	"{\n"
// 	"\tgl_Position = vec4(a_position, 0.0, 1.0);\n"
// 	"}\n";

// const char* frag_source = 
// 	"#version 330 core\n"
// 	"layout(location=0) out vec4 o_color;\n"
// 	"void main()\n"
// 	"{\n"
// 	"\to_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
// 	"}\n";

// void check_opengl_errors(const char* name)
// {
//     int check = 1;
//     while (check)
//     {
//         const GLenum err = glGetError();
//         switch (err)
//         {
//             case GL_NO_ERROR: check = 0; break;
//             case 0x0500: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_ENUM"); break;
//             case 0x0501: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_VALUE"); break;
//             case 0x0502: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_OPERATION"); break;
//             case 0x0503: printf("%s:%s", name, "OpenGL Error detected: GL_STACK_OVERFLOW"); break;
//             case 0x0504: printf("%s:%s", name, "OpenGL Error detected: GL_STACK_UNDERFLOW"); break;
//             case 0x0505: printf("%s:%s", name, "OpenGL Error detected: GL_OUT_OF_MEMORY"); break;
//             case 0x0506: printf("%s:%s", name, "OpenGL Error detected: GL_INVALID_FRAMEBUFFER_OPERATION"); break;
//             default: printf("%s:%i", "OpenGL Error detected: Unknown error code:", err); break;
//         }
//     }
// }

// int main(int argc, char** argv) {
// 	if(!glfwInit())
// 		return 1;
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
// 	GLFWwindow* window = glfwCreateWindow(640, 480, "Example", NULL, NULL);

// 	glfwMakeContextCurrent(window);

// 	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

// 	float vertices[] = {
// 		-0.5f, -0.5f,
// 		 0.5f, -0.5f,
// 		 0.5f,  0.5f,
// 		-0.5f,  0.5f,
// 	};

// 	uint32_t vao = 0;
// 	glGenVertexArrays(1, &vao);
// 	glBindVertexArray(vao);

// 	uint32_t vbo = 0;
// 	glGenBuffers(1, &vbo);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 	uint32_t ibo = 0;
// 	glGenBuffers(1, &ibo);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
// 	uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// 	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 	glShaderSource(vertexShader, 1, &vert_source, NULL);
// 	glCompileShader(vertexShader);

// 	// Create and compile the fragment shader
// 	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// 	glShaderSource(fragmentShader, 1, &frag_source, NULL);
// 	glCompileShader(fragmentShader);

// 	// Link the vertex and fragment shader into a shader program
// 	GLuint shaderProgram = glCreateProgram();
// 	glAttachShader(shaderProgram, vertexShader);
// 	glAttachShader(shaderProgram, fragmentShader);
// 	glLinkProgram(shaderProgram);
// 	glUseProgram(shaderProgram);

// 	// Specify the layout of the vertex data
// 	// GLint posAttrib = glGetAttribLocation(shaderProgram, "a_position");
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);err
// 	while(!glfwWindowShouldClose(window)) {
// 		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}
// }