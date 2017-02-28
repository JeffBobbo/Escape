#include "visage.h"

/*
#include <map>
#include <string>

#include <iostream>
#include <fstream>

#include "allvisage.h"
#include "../../external/rapidjson/include/rapidjson/document.h"
*/

/*
#ifdef _WIN32
#else
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#endif
 */

/*
std::map<std::string, Visage*> vmap;

void loadFile(const std::string& filename)
{
  std::ifstream file("visages/" + filename + ".json");
  if (!file)
  {
    std::cerr << "Failed to open visage file " << filename << std::endl;
    return;
  }

  std::string buf;
  file.seekg(0, std::ios::end);
  buf.reserve(static_cast<std::string::size_type>(file.tellg()));
  file.seekg(0, std::ios::beg);
  buf.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  rapidjson::Document doc;
  doc.Parse(buf.c_str());
  if (!doc.IsObject())
  {
    std::cerr << "Root element of visage data must be an object" << std::endl;
    return;
  }

  Visage* v = nullptr;
  std::string type = doc["type"].GetString();
  if (type == "polygon")
    v = new VisagePolygon();
  else if (type == "texture")
    v = new VisageTexture();
  else if (type == "complex")
    v = new VisageComplex();
  else if (type == "particle")
    v = new ParticleSystem(doc["max"].GetInt(), 0);
  else
    std::cerr << "Unknown visage type: " << type << std::endl;

  //if (v)
    //v->fromJSON(doc);
}

void Visage::loadVisages()
{
  std::cout << "Loading visage data from files..." << std::endl;

  std::ifstream index("visages/index.json");
  if (!index)
  {
    std::cerr << "Failed to open index" << std::endl;
    return;
  }

  std::string buf;
  index.seekg(0, std::ios::end);
  buf.reserve(static_cast<std::string::size_type>(index.tellg()));
  index.seekg(0, std::ios::beg);
  buf.assign((std::istreambuf_iterator<char>(index)), std::istreambuf_iterator<char>());

  rapidjson::Document doc;
  doc.Parse(buf.c_str());
  if (!doc.IsArray())
  {
    std::cerr << "Visage index should be a list of files" << std::endl;
    return;
  }

  //for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
  for (auto& it : doc.GetArray())
  {
    loadFile(it.GetString());
  }
*/
/*
#ifdef _WIN32
#error LOADING VISAGES NOT IMPLEMENTED
#else
  DIR* dp;
  dirent* dirp;
  if ((dp = opendir("visages/")) == nullptr)
  {
    std::cerr << "Failed to open visages directory: " << errno << std::endl;
    exit(1);
  }

  while ((dirp = readdir(dp)) != nullptr)
  {
    // skip the . files
    if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
      continue;

    std::string name = std::string(dirp->d_name);
    if (name.substr(name.length() - 4) != ".json")
    {
      std::cout << "Skipping non-JSON file " << name << std::endl;
      continue;
    }
    std::cout << name << std::endl;
  }
#endif
 */
/*
}
*/
