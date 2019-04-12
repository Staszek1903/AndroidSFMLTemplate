#include "entitymenager.h";

EntityMenager()
{
}


~EntityMenager()
{
	for(auto p: systems)
		delete p;
	for(auto c: components)
		delete c;
}
	