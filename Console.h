#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class Console
{
	sf::Font font;
	sf::Text text;
    sf::RenderTexture texture;
    sf::Sprite area;

    static constexpr int constent_size = 15;
    static constexpr int character_size = 20;
    std::string content [constent_size];
    int bottom = 2;
    int top = 0;

    bool is_shown = true;

public:
	sf::RenderWindow & window;
	
    Console(sf::RenderWindow &window);
	
    template<class T>
    void operator<<(T data)
    {
        std::stringstream ss;
        std::string text;
        ss<<data;
        text = ss.str();

        while (true) {
            size_t endline = text.find('\n');
            if( endline == std::string::npos ) {
                addContent(text);
                break;
            }

            addContent(text.substr(0,endline));
            text = text.substr(endline+1, text.size()-endline);
        }

    }

    void show(bool is);
	void draw();

private:
    void addContent(const std::string & text);
};
