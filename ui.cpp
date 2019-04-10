#include "ui.h"

Desctription default_ui[5] =
{
	 // { pos:{x,y}, vert:{ {x1,y1}, {x2,y2}, ...}  }  
	{  {,},  { {,},{,},{,} }  },
	{  {,},  { {,},{,},{,} }  },
	{  {,},  { {,},{,},{,} }  },
	{  {,},  { {,},{,},{,} }  },
	
	{  {,},  { {,},{,},{,} }  }
};



UI::UI(){}

UI::~UI()
{
	for(auto t: nodes)
		if(t) delete t;
}

void UI::addNode( Touchable * t )
{
	nodes.push_back(t);
	Renderer::get().addDrawable(*t);
}

void UI::createDefault()
{
	auto t = new Touchable(300,300, {{-50,-50},{50,-50},{0,50}});
	t->setFillColor(sf::Color::Green);
	addNode(t);
}