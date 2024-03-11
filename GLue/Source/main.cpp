#include <Shader.h>
#include <GLFW/glfw3.h>
#include <iostream>


void SetFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);

int main() {

	const int HEIGHT = 600;
	const int WIDTH  = 800;
	/*Iniciacion del contexto de las librerias GLFW y GLAD y Creación de ventana*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLue funcionaa >_<", NULL, NULL);
	if (!window) {
		std::cout << "No se ha podido crear correctamente una ventana con GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,SetFramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "No se ha podido incializar GLAD" << std::endl;
		return -1;
	}
	/*Utilizacion de la clase codificada Shader*/
	Shader shader = Shader("Source/Shaders/Vertex.glsl",
		                   "Source/Shaders/Fragment.glsl");

	/*Preparando los vertices y estructuras*/
	float vertices[] = {
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //Inf.Dcha.
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //Inf.Izq.	 
		-0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f  //Sup.
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Se realiza el bind de VAO para que en las siguientes llamadas de la configuración del VBO
	//se quenden guardadas en esta
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Se realiza un unbind del VBO para indicar que se ha terminado su configuración
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Se realiza lo mismo para el VAO para que no haya ninguna interferencia si se configuran
	//otros VAO después.
	glBindVertexArray(0);
	
	/*Loop en el que se realizan la operaciones de visualización*/
	while (!glfwWindowShouldClose(window)) {

		proccessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use(); 		
		float stime = sin(glfwGetTime()) / 2.0f + 0.5f;
		shader.setFloat("offset", stime);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*Terminación del programa y liberar recursos*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader.ID);
	glfwTerminate();
	return 0;
}

void SetFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void proccessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


