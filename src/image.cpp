#include "image.h"

#include <iostream>
#include <utility>
#include <fstream>
#include <cassert>

#include "../external/rapidjson/include/rapidjson/document.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include "gli.h"

std::map<std::string, Texture> texmap;


void loadAtlasInformation(const std::string file, Texture& tex)
{
  std::ifstream ifs(file);
  if (!ifs)
    return;

  // read the entire file in
  std::string buf;
  ifs.seekg(0, std::ios::end);
  buf.reserve(static_cast<std::string::size_type>(ifs.tellg())); // reserve all the memory up front
  ifs.seekg(0, std::ios::beg);
  buf.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

  rapidjson::Document doc;
  doc.Parse(buf.c_str());
  if (!doc.IsObject())
  {
    std::cerr << "Root node of atlas information isn't an object" << file << std::endl;
    return;
  }

  for (auto& it : doc.GetObject())
  {
    std::string name = it.name.GetString();
    assert(it.value.IsObject());
    const rapidjson::Value& v = it.value;
    assert(v.HasMember("x") || !v.HasMember("y") || !v.HasMember("w") || !v.HasMember("h"));

    AtlasSprite as;
    as.x = v["x"].GetInt();
    as.y = v["y"].GetInt();
    as.w = v["w"].GetInt();
    as.h = v["h"].GetInt();
    tex.sprites.insert(std::make_pair(name, as));
  }
}

void loadTexture(const std::string& t)
{
  if (texmap.find(t) != std::end(texmap))
    return;

  Texture tex;
  tex.data = stbi_load(t.c_str(), &tex.width, &tex.height, &tex.bpp, 4);
  if (!tex.data)
  {
    std::cerr << "Failed to load image: " << t << std::endl;
    exit(1); // die
  }
  glGenTextures(1, &tex.tex);
  glBindTexture(GL_TEXTURE_2D, tex.tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.data);
  //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
  //glGenerateMipmap(GL_TEXTURE_2D);

  // C++17 had std::filestream which we could use to test existance of the file
  // however, little early for that. So just try it anyway and quitely bail out
  // if the ifstream couldn't be opened
  loadAtlasInformation(t + ".json", tex);

  texmap.insert(std::make_pair(t, tex));
}

void dropTexture(const std::string& t)
{
  auto it = texmap.find(t);
  if (it != std::end(texmap))
  {
    glDeleteTextures(1, &it->second.tex);
    stbi_image_free(it->second.data);
    texmap.erase(it);
  }
}
void dropAllTextures()
{
  for (auto it : texmap)
    stbi_image_free(it.second.data);
  texmap.clear();
}

void bindTexture(const std::string& t)
{
  auto it = texmap.find(t);
  if (it == std::end(texmap))
  {
    loadTexture(t);
    it = texmap.find(t);
  }
  glBindTexture(GL_TEXTURE_2D, it->second.tex);
}

GLuint getTexture(const std::string& t)
{
  auto it = texmap.find(t);
  if (it == std::end(texmap))
  {
    loadTexture(t);
    it = texmap.find(t);
  }
  return it->second.tex;
}

STSprite getSTCoords(const std::string& t, const std::string& s)
{
  auto it = texmap.find(t);
  if (it == std::end(texmap))
  {
    loadTexture(t);
    it = texmap.find(t);
  }

  auto f = it->second.sprites.find(s);
  if (f == std::end(it->second.sprites))
    return {0.0, 1.0, 0.0, 1.0};

  AtlasSprite as = f->second;
  STSprite st;
  st.s0 = as.x / static_cast<double>(it->second.width);
  st.s1 = (as.x + as.w) / static_cast<double>(it->second.width);
  st.t0 = as.y / static_cast<double>(it->second.height);
  st.t1 = (as.y + as.h) / static_cast<double>(it->second.height);
  return st;
}
