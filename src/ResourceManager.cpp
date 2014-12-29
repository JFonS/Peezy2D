/* 
 * File:   ResourceManager.cpp
 * Author: jfons
 * 
 * Created on December 25, 2014, 1:49 PM
 */

#include "include/ResourceManager.hpp"
#include "include/Debug.hpp"
#include <map>

ResourceMap ResourceManager::textures = ResourceMap();

void ResourceManager::deleteTexture(string textureName) {
    ResourceMap::iterator it;
    if ((it = textures.find(textureName)) != textures.end()) {
        if (--(it->second.refs) < 1) {
            delete (Texture*)it->second.res;
            textures.erase(it);
            DbgLog("Deleted texture " << textureName);
        } 
    }
}


Texture& ResourceManager::getTexture(string textureName) {
    Texture* ret;
    ResourceMap::iterator it;
    if ((it = textures.find(textureName)) != textures.end()) {
        ret = (Texture*)it->second.res;
        ++(it->second.refs);
    } else {
        DbgLog("Loading texture " << textureName);
        ret = new Texture();
        ret->loadFromFile(textureName);
        textures.insert(pair<string,Resource>(textureName,Resource(ret)));
    }
    return *ret;
}
