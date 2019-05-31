#ifndef PROGRAM_STAGE_H_
#define PROGRAM_STAGE_H_

#include <memory>
#include <SFML/Graphics.hpp>

class ProgramStage
{
	static std::unique_ptr<ProgramStage> next;
	static std::unique_ptr<ProgramStage> current;
	
public:
	ProgramStage();
	virtual ~ProgramStage();
	template<class T>
	static void next_stage();
	
	static void switch_stage();
	static void input_stage(sf::Event &ev);
	static void update_stage(double dt);
	static void render_stage(sf::RenderWindow & win);
	 
	
	virtual void init() = 0;
	virtual void input(sf::Event & ev) = 0;
	virtual void update(double dt)=0;
	virtual void render(sf::RenderWindow & win) =0;
	virtual void release() =0;
};

template<class T>
void ProgramStage::next_stage()
{
	next = std::make_unique<T>();
}

#endif