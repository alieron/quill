#include "element.h"

#include <stb/stb_image.h>
#include <iostream>

unsigned int loadTexture(const char* path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nchannels;
  unsigned char *data = stbi_load(path, &width, &height, &nchannels, 0);
  if (data) {
    GLenum format = nchannels - 3 ? GL_RGBA : GL_RGB;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
  }
  else {
    std::cout << "Failed to load texture at: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

// Element::buildGeometry(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned int z1, unsigned int z2) {

// }

// Face::Face(int from[3], int to[3], int uv[4], std::string &texture){
    
// };

void Element::draw() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, _down);
    // glDrawRangeElements(GL_TRIANGLES, 0, 5, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &mVertices[0]);

	glBindTexture(GL_TEXTURE_2D, _up);
    // // glDrawRangeElements(GL_TRIANGLES, 6, 11, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &mVertices[0] + 6);

	glBindTexture(GL_TEXTURE_2D, _north);
    // glDrawRangeElements(GL_TRIANGLES, 12, 17, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &mVertices[0] + 12);

	glBindTexture(GL_TEXTURE_2D, _south);
    // glDrawRangeElements(GL_TRIANGLES, 18, 23, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &mVertices[0] + 18);

	glBindTexture(GL_TEXTURE_2D, _west);
    // glDrawRangeElements(GL_TRIANGLES, 24, 29, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &mVertices[0] + 24);

	glBindTexture(GL_TEXTURE_2D, _east);
    // glDrawRangeElements(GL_TRIANGLES, 30, 35, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &mVertices[0] + 30);
};