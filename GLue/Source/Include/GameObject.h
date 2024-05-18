#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <iostream>
#include <fstream>
#include <vector>

class GameObject{
public:
	glm::vec3 Transform;
	glm::vec3 Rotation;
	std::vector<float> data;
	unsigned int VBO, VAO;
	GameObject(glm::vec3 transform, glm::vec3 rotation): Transform(transform), Rotation(rotation) {
		//std::cout << "Hola se ha construido este objeto" << std::endl;
		
		data = std::vector<float>(sizeof(DEFAULT_PIRAMID) / sizeof(float), 0);
		for (int i = 0; i < static_cast<int>(data.size()); ++i) {
			data[i] = DEFAULT_PIRAMID[i];
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		//Se realiza el bind de VAO para que en las siguientes llamadas de la configuración del VBO
		//se quenden guardadas en esta
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	~GameObject() {
		data.~vector();
		//std::cout << "Hola se ha destruido este objeto" << std::endl;
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	void DrawObject() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
private:
	const float DEFAULT_CUBE[180] = {
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
	const float DEFAULT_PIRAMID[4*3*5] = {
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //frente izq;
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //frente dcha;
	 0.0f,  0.5f,  0.0f,  0.5f, 1.0f, //frente arriba

	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //frente dcha;
	 0.0f, -0.5f, -0.5f,  1.0f, 0.0f, //no se sabe, calcular
	 0.0f,  0.5f,  0.0f,  0.5f, 1.0f, //frente arriba

	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //frente izq;
	 0.0f, -0.5f, -0.5f,  0.0f, 0.0f, //no se sabe, calcular
	 0.0f,  0.5f,  0.0f,  0.5f, 1.0f, //frente arriba

	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //frente izq;
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //frente dcha;
	 0.0f, -0.5f, -0.5f,  0.5f, 1.0f, //no se sabe, calcular
	};
	bool LeerVerticesDeArchivo(const char* path) {
		std::ifstream archivo;
		archivo.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			char fuera[512];
			archivo.open("Source/Textures/prueba.obj", std::ifstream::in);
			while (!archivo.eof()){
				archivo.getline(fuera, 512);
			}
			archivo.close();
			std::cout << fuera << std::endl;
		}catch (std::ifstream::failure e) {
			std::cerr << "No se ha podido abrir el archivo porque: " << e.what() << std::endl;
			archivo.close();
			return false;
		}
		return true;
	}
};
#endif 

