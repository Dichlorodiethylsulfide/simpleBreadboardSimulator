//
// Created by riki on 7/25/22.
//

#ifndef CLIONUNTITLED_RESOURCEMANAGER_H
#define CLIONUNTITLED_RESOURCEMANAGER_H

#include "includes.h"


class ResourceManager {
public:
    explicit ResourceManager(const string& font_file);
    void AddNewTexture(const std::string& name, const std::string& filename);
    Texture& GetTexture(const std::string& texture_name);
    Font& GetFont();
    ~ResourceManager() = default;
    static ResourceManager* Resources;
private:
    map<string, Texture*> TextureMap;
    Font arialFont;
    ResourceManager();
};


#endif //CLIONUNTITLED_RESOURCEMANAGER_H
