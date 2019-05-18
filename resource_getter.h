
#include <vector>

#define RESOURCE(type, name) \
	std::vector<type> name ;\
	std::vector<type> & get_name() \
	{ \
		return name; \
	} 