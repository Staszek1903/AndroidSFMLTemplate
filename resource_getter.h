#ifndef RESOURCE_GETTER_H_
#define RESOURCE_GETTER_H_

#include <vector>

#define RESOURCE(type, name) \
	std::vector<type> name ;\
	std::vector<type> & get_name() \
	{ \
		return name; \
	} 

#endif
