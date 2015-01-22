#include "../include/ResourceManager.hpp"
#include "../include/Debug.hpp"
#include <map>

ResourceMap ResourceManager::textures = ResourceMap();
ResourceMap ResourceManager::sounds = ResourceMap();

void ResourceManager::deleteTexture(string texturePath) {
    ResourceMap::iterator it;
    if ((it = textures.find(texturePath)) != textures.end()) {
        if (--(it->second.refs) < 1) {
            delete (Texture*)it->second.res;
            textures.erase(it);
            DbgLog("Deleted texture " << texturePath);
        } 
    }
}


Texture& ResourceManager::getTexture(string texturePath) {
    Texture* ret;
    ResourceMap::iterator it;
    if ((it = textures.find(texturePath)) != textures.end()) {
        ret = (Texture*)it->second.res;
        ++(it->second.refs);
    } else {
        DbgLog("Loading texture " << texturePath);
        ret = new Texture();
        ret->loadFromFile(texturePath);
        textures.insert(pair<string,Resource>(texturePath,Resource(ret)));
    }
    return *ret;
}

SoundBuffer& ResourceManager::getSoundBuffer(string soundPath) {
    SoundBuffer* ret;
    ResourceMap::iterator it;
    if ((it = sounds.find(soundPath)) != sounds.end()) {
        ret = (SoundBuffer*)it->second.res;
        ++(it->second.refs);
    } else {
        DbgLog("Loading texture " << soundPath);
        ret = new SoundBuffer();
        ret->loadFromFile(soundPath);
        sounds.insert(pair<string,Resource>(soundPath,Resource(ret)));
    }
    return *ret;
}

void ResourceManager::deleteSoundBuffer(string soundPath) {
    ResourceMap::iterator it;
    if ((it = sounds.find(soundPath)) != sounds.end()) {
        if (--(it->second.refs) < 1) {
            delete (SoundBuffer*)it->second.res;
            sounds.erase(it);
            DbgLog("Deleted texture " << soundPath);
        } 
    }
}

