#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include "resource_getter.h"
#include "singleton.hpp"
#include <SFML/Graphics.hpp>

class ResourceManager:public Singleton < ResourceManager >
{
    ResourceManager();
    ~ResourceManager();
    friend Singleton < ResourceManager > ;
	
    RESOURCE(sf::Texture, textures)

};

#endif
