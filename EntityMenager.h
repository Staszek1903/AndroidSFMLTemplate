#ifndef ENTITYMENAGER_H_
#define ENTITYMENAGER_H_

#include <string>
#include <map>

class BaseSystem;


class EntityMenager
{
	// first: component class name
	// second: conponent class id;
	std::map < std::string, unsigned int> id_map;
	std::vector <BaseSystem*> systems;
	std::vector <BaseComponents*> componenst;
	
public:
	EntityMenager();
	
	template<class Sys>
	void addSytem();
	
	template<class C>
	void addEntity();
	
};

#endif