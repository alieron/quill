#pragma once

#include <string>
#include <unordered_map>

#include <glad/gl.h>
#include <glm/glm.hpp>

struct Texture {
  GLuint id;
  int width, height;
};

/* std::unordered_map<std::string, std::shared_ptr<Texture2D>> textureCache; */
/* if (textureCache.contains("stone.png")) return textureCache["stone.png"]; */

class TextureLoader {
private:
  std::unordered_map<std::string, Texture *> sceneTextures;

  Texture *loadTextureFromPath(const std::string &path);

public:
  void loadTexture(const std::string &name);

  Texture *getTexture(const std::string &name);

  void clearTextures();
};
