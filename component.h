#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Console.h"

#include <string>

class BaseComponent
{
public:
	BaseComponent();
};

template<class C>
class Component : virtual public BaseComponent
{
	static std::string name;
protected:
	virtual void addName(std::string name) = 0;
	
public:
	Component(){
		if(name.size() == 0)
		{
			name = typeid(this).name();
			addName(name);
		}
		Console::get()<<"component c-tor:  "<<name<<"\n";
		}
	
	//static std::string getName()
	//{
		//return typeid(C).name();
	//}
	
};


 #endif      