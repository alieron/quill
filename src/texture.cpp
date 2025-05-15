#include <iostream>
#include <string>
#include <unordered_map>

#include <glad/gl.h>
#include <stb/stb_image.h>

#include "textures.h"

Texture *TextureLoader::loadTextureFromPath(const std::string &path) {
  Texture *tex;

  int nChannels;
  unsigned char *data =
      stbi_load(path.c_str(), &tex->width, &tex->height, &nChannels, 0);
  if (data) {
    GLenum format = nChannels - 3 ? GL_RGBA : GL_RGB;

    glGenTextures(1, &tex->id);
    glBindTexture(GL_TEXTURE_2D, tex->id);

    glTexImage2D(GL_TEXTURE_2D, 0, format, tex->width, tex->height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
    return tex;
  } else {
    std::cout << "Failed to load texture at: " << path << std::endl;
    stbi_image_free(data);
    return nullptr;
  }
}

// does not overrides any texture that exists with the same
void TextureLoader::loadTexture(const std::string &name) {
  if (sceneTextures.find(name) != sceneTextures.end()) {
    return;
  } else {
    // eventually handle the search for the file paths
    Texture *tex = loadTextureFromPath(name);
    if (tex->id != 0) {
      sceneTextures[name] = tex;
    }
    return;
  }
}

Texture *TextureLoader::getTexture(const std::string &name) {
  if (sceneTextures.find(name) != sceneTextures.end())
    return sceneTextures[name];
  return nullptr;
}
