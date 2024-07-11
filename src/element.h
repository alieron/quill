#pragma once

#include <string>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

unsigned int loadTexture(const char* path);

class Element {
public:
	unsigned int VBO, EBO, VAO;
	glm::vec3 mFr;
	glm::vec3 mTo;
	std::vector<float> mVertices;
	std::vector<unsigned int> mIndices;

	// Constructor
	// Element(int from[3], int to[3], int uv[4], std::string &texture) {

	// }

	Element(glm::vec3 from = glm::vec3(0,0,0), glm::vec3 to = glm::vec3(16,16,16)) {
		mFr = (from * 0.0625f) - 0.5f;
		mTo = (to * 0.0625f) - 0.5f;

		// yet to handle UV scaling
		std::vector<float> vertices{
			// Down -Y
			mTo.x, mFr.y, mTo.z, 1.0f, 0.0f,    // 0
			mFr.x, mFr.y, mTo.z, 0.0f, 0.0f,    // 1
			mFr.x, mFr.y, mFr.z, 0.0f, 1.0f,    // 2
			mTo.x, mFr.y, mFr.z, 1.0f, 1.0f,    // 3
			// Up +Y
			mTo.x, mTo.y, mFr.z, 1.0f, 0.0f,    // 4
			mFr.x, mTo.y, mFr.z, 0.0f, 0.0f,    // 5
			mFr.x, mTo.y, mTo.z, 0.0f, 1.0f,    // 6
			mTo.x, mTo.y, mTo.z, 1.0f, 1.0f,    // 7
			// North -Z
			mFr.x, mTo.y, mFr.z, 1.0f, 0.0f,    // 5
			mTo.x, mTo.y, mFr.z, 0.0f, 0.0f,    // 4
			mTo.x, mFr.y, mFr.z, 0.0f, 1.0f,    // 3
			mFr.x, mFr.y, mFr.z, 1.0f, 1.0f,    // 2
			// South +Z
			mTo.x, mTo.y, mTo.z, 1.0f, 0.0f,    // 7
			mFr.x, mTo.y, mTo.z, 0.0f, 0.0f,    // 6
			mFr.x, mFr.y, mTo.z, 0.0f, 1.0f,    // 1
			mTo.x, mFr.y, mTo.z, 1.0f, 1.0f,    // 0
			// West -X
			mFr.x, mTo.y, mTo.z, 1.0f, 0.0f,    // 6
			mFr.x, mTo.y, mFr.z, 0.0f, 0.0f,    // 5
			mFr.x, mFr.y, mFr.z, 0.0f, 1.0f,    // 2
			mFr.x, mFr.y, mTo.z, 1.0f, 1.0f,    // 1
			// East +X
			mTo.x, mTo.y, mFr.z, 1.0f, 0.0f,    // 4
			mTo.x, mTo.y, mTo.z, 0.0f, 0.0f,    // 7
			mTo.x, mFr.y, mTo.z, 0.0f, 1.0f,    // 0
			mTo.x, mFr.y, mFr.z, 1.0f, 1.0f,    // 3
		};
		
		std::vector<unsigned int> indices{
			0, 1, 2,    	0, 2, 3,	// Down -Y
			4, 5, 6, 		4, 6, 7,	// Up +Y
			8, 9, 10, 		8, 10, 11,	// North -Z
			12, 13, 14, 	12, 14, 15,	// South +Z
			16, 17, 18, 	16, 18, 19,	// West -X
			20, 21, 22, 	20, 22, 23	// East +X
		};

		// mVertices = vertices;
		mIndices = indices;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		
		// pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		
		// uv
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	};
	
	~Element() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void draw();

	void _testTextures() {
		_down = loadTexture("../resourcepacks/test/minecraft/textures/block/down_test.png");
		_up = loadTexture("../resourcepacks/test/minecraft/textures/block/up_test.png");
		_north = loadTexture("../resourcepacks/test/minecraft/textures/block/north_test.png");
		_south = loadTexture("../resourcepacks/test/minecraft/textures/block/south_test.png");
		_west = loadTexture("../resourcepacks/test/minecraft/textures/block/west_test.png");
		_east = loadTexture("../resourcepacks/test/minecraft/textures/block/east_test.png");
	};

private:
	unsigned int _down, _up, _north, _south, _west, _east;
};