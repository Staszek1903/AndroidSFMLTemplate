#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

class BaseComponent
{
public:
	BaseComponent();
};

template<class C>
class Component : public BaseComponent
{
public:
	Component(){}
	
	static std::string getName()
	{
		return typeid(C).name();
	}
	
};


 #endif      