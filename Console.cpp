#include "Console.h"
#include <exception>
Console * Console::instance = nullptr;
sf::RenderWindow * Console::win_pointer = nullptr;

Console::Console(sf::RenderWindow & window)
: window(window)
{
      if( ! font.loadFromFile( "Arial.ttf" ) )
	    throw std::runtime_error( " no font.ttf ");	    
      text.setString("SAMPLE TEXT");
      text.setFont(font);
      text.setFillColor(sf::Color::White);
      text.setCharacterSize(character_size);
      texture.create(400,315);
      area.setTexture(texture.getTexture());

      area.setOrigin(area.getLocalBounds().width/2, area.getLocalBounds().height/2);
      area.setScale(2.0f, -2.0f);
      area.setPosition(area.getLocalBounds().width, area.getLocalBounds().height);

      for(int i = 0; i < content_size; ++i)
      for(int j = 0; j < line_size; ++j)
      content[i][j] = '\0';
      
      addContent("Android Console V0.2\n");
      addContent("Hello!\n");
      (*this)<<"character height:"<<text.getLocalBounds().height<<" dsads\n";
}

void Console::show(bool is)
{
    is_shown = is;
}

void Console::draw()
{
    texture.clear(sf::Color(0,0,0,128));
    int row = 0; // rzad graficzny
    for (int i = (bottom +1)%content_size;
     ;
     (++i) %= content_size, ++row) 
    {
        std::string l(/*"dupa");*/content[i]);
    	text.setString(l);
        text.setPosition(5,row*character_size);
        texture.draw(text);
        if(i == bottom) break;
    }
}

void Console::display()
{
	if(need_redraw)
	{
		need_redraw = false;
	    draw();
	}
    if(is_shown)
        window.draw(area);
}

void Console::set_window(sf::RenderWindow *window)
{
    win_pointer = window;
}

Console &Console::get()
{
    if(! instance ) instance = new Console(*win_pointer);
    return *instance;
}

void Console::release()
{
    if(instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Console::addContent(const std::string &text)
{
    for(auto a: text)
    {
    	addChar(a);
    	if(a == '\n') nextLine();
    }
    need_redraw = true;
}

void Console::addChar(char c)
{
	content[bottom][carriage] = c;
    ++carriage;
	if(carriage > line_size - 2)  nextLine();
}

void Console::nextLine()
{
	content[bottom][carriage] = '\0';
    bottom = (bottom+1)%content_size;
    carriage = 0;
    clearLine(bottom);
}

void Console::clearLine(int line)
{
	for(int i=0; i<line_size; i++) content[line][i] = '\0';
}
	
