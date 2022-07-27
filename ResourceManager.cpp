//
// Created by riki on 7/25/22.
//

#include "ResourceManager.h"

ResourceManager* ResourceManager::Resources = nullptr;

ResourceManager::ResourceManager(const string& font_file)
{
    this->TextureMap = map<string, Texture*>();
    this->arialFont = Font();
    this->arialFont.loadFromFile(font_file);
}

ResourceManager::ResourceManager()
{
    throw runtime_error("Cannot create resource manager.");
}

void ResourceManager::AddNewTexture(const std::string &name, const std::string &filename)
{
    if(this->TextureMap.count(name))
    {
        throw std::runtime_error("Map already contains key");
    }
    auto texture = new Texture();
    texture->loadFromFile(filename);
    this->TextureMap.insert(std::pair<std::string, Texture*>(name, texture));
}

Texture &ResourceManager::GetTexture(const string &texture_name)
{
    return *this->TextureMap[texture_name];
}

Font &ResourceManager::GetFont()
{
    return this->arialFont;
}

