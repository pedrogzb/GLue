#include <Shader.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Camera.h>
#include <glm/gtc/type_ptr.hpp>



void SetFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int HEIGHT = 600;
const unsigned int WIDTH  = 800;

float mix_val = 0.01f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float LastFrame0 = 0.0f;
int	  CountFrames =   0;
float FrameRate = 0.0f;

bool firstMouse = true;
float lastX = 400.0f, lastY = 300.0f;
Camera cam;

int main() {
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window,mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "No se ha podido incializar GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	/*Utilizacion de la clase codificada Shader*/
	Shader shader = Shader("Source/Shaders/Vertex.glsl",
		                   "Source/Shaders/Fragment.glsl");
	Shader sUI	  = Shader("Source/Shaders/vUI.glsl",
						   "Source/Shaders/fUI.glsl");

	/*Preparando los vertices y estructuras*/
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Se realiza el bind de VAO para que en las siguientes llamadas de la configuración del VBO
	//se quenden guardadas en esta
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*Preparar los vertices de la UI*/
	//float vUI[] = {
	//	-1.0f, -0.5f, 0.0f,  0.0f, 0.0f,
	//	 1.0f, -0.5f, 0.0f,  1.0f, 0.0f,
	//	 1.0f,  0.5f, 0.0f,  1.0f, 1.0f,
	//	 1.0f,  0.5f, 0.0f,  1.0f, 1.0f,
	//	-1.0f,  0.5f, 0.0f,  0.0f, 1.0f,
	//	-1.0f, -0.5f, 0.0f,  0.0f, 0.0f,
	//};
	float vUI[] = {
	 0.8f,  0.9f, 0.0f,  0.0f, 0.0f,
	 1.0f,  0.9f, 0.0f,  1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
	 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
	 0.8f,  1.0f, 0.0f,  0.0f, 1.0f,
	 0.8f,  0.9f, 0.0f,  0.0f, 0.0f,
	};
	unsigned int VBO_UI, VAO_UI;
	glGenVertexArrays(1, &VAO_UI);
	glGenBuffers(1, &VBO_UI);
	glBindVertexArray(VAO_UI);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_UI);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vUI), vUI, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/**********************************************************************************************/
	
	stbi_set_flip_vertically_on_load(true);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("Source/Textures/ShinjiGL.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "no se ha podido abrir el archivo" << std::endl;
	}
	stbi_image_free(data);
	
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("Source/Textures/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "no se ha podido abrir el archivo" << std::endl;
	}
	stbi_image_free(data);
		
	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	/*Loop en el que se realizan la operaciones de visualización*/
	while (!glfwWindowShouldClose(window)) {

		float currFrame = static_cast<float>(glfwGetTime());
		deltaTime = currFrame - lastFrame;
		lastFrame = currFrame;
		if (currFrame - LastFrame0 > 1.0f) {
			FrameRate = CountFrames + 1.0f / (currFrame - LastFrame0);
			CountFrames = 0;
			LastFrame0 = currFrame;
		}else ++CountFrames;

		proccessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		shader.use();

		/*Generación de la matriz de tranformacin*/
		glm::mat4 view = cam.GetViewMatrix();
		unsigned int viewTransLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewTransLoc, 1, GL_FALSE, glm::value_ptr(view));
		
		glm::mat4 proyection = glm::perspective(glm::radians(cam.Zoom), ((float)WIDTH) / ((float)HEIGHT), 0.01f, 100.f);
		unsigned int proyectionTransLoc = glGetUniformLocation(shader.ID, "proyection");
		glUniformMatrix4fv(proyectionTransLoc, 1, GL_FALSE, glm::value_ptr(proyection));

		shader.setFloat("mix_val", mix_val);

		glBindVertexArray(VAO);
		for (int i = 0; i < 10; ++i) {
			glm::mat4 model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			if (i % 3 == 0) angle += deltaTime*50.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			unsigned int modelTransLoc = glGetUniformLocation(shader.ID, "model");
			glUniformMatrix4fv(modelTransLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		sUI.use();
		sUI.setFloat("FrameRate", FrameRate);
		sUI.setInt("opcion", 6);
		glBindVertexArray(VAO_UI);
		glDrawArrays(GL_TRIANGLES, 0, 6);
				
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*Terminación del programa y liberar recursos*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader.ID);
	glDeleteVertexArrays(1, &VAO_UI);
	glDeleteBuffers(1, &VBO_UI);
	glDeleteProgram(sUI.ID);
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		mix_val = std::min(1.0f, mix_val + 1.0f * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		mix_val = std::max(0.0f, mix_val - 1.0f * deltaTime);
	}
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	cam.ProcessMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset), true);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

