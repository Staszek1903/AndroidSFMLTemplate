#include "p.h"
#include <SFML/Graphics.hpp>

#include "console.h"
#include "error_generate.hpp"

int main()
{
    Program p;

    ProgramStage::next_stage<P>(p.get_window());

    p.run();
	
	return 0;
}
