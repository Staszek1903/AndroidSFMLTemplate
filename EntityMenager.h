#ifndef ENTITYMENAGER_H_
#define ENTITYMENAGER_H_

#include <string>
#include <map>
#include <vector>

#include "component.h"
#include "system.h"
#include "Console.h"

class EntityMenager
{
	// first: component class name
	// second: conponent class id;
	std::map < std::string, unsigned int> id_map;
	unsigned int next_id = 1;
	
	std::vector <BaseSystem*> systems;
	std::vector <BaseComponent*> components;
	
public:
	EntityMenager();
	~EntityMenager();
	
	template<class Sys>
	void addSytem()
	{}
	
	template<class C>
	void addEntity();
	
};

template<class C>
void EntityMenager::addEntity()
{
	 components.push_back(new C());
	 //std::string name = C::getName();
	 
	 //if(id_map.find(name) == id_map.end())
	 //{
	 	//Console::get()<<"new name: "<<name<<"\n";
	 	//id_map[name] = next_id;
	 	//next_id <<= 1;
	 //}
	 
	 Console::get()<<"juss\n";
}

#endif