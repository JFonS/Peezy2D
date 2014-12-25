#ifndef RESOURCEMANAGER_HPP
#define	RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace sf;
using namespace std;

struct Resource {
        void* res;
        int refs;
        
        Resource() {
            res = NULL;
            refs = 0;
        }
        
        Resource(void* p) {
            res = p;
            refs = 1;
        }
    };

typedef map<string,Resource> ResourceMap;

class ResourceManager {
      
public:
    static Texture& getTexture(string textureName);
    static void deleteTexture(string textureName);
    
private:
    static ResourceMap textures;
};

#endif	/* RESOURCEMANAGER_HPP */

