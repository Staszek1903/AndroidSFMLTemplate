#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

#include <sstream>

class ConsoleData;

class Console
{
    static Console * instance;
    static sf::RenderWindow * win_pointer;
    static constexpr int content_size = 26;
    static constexpr int line_size = 40;
    static constexpr int character_size = 12;

	sf::Font font;
	sf::Text text;
    sf::RenderTexture texture;
    sf::Sprite area;

    char content [content_size][line_size];
    int bottom = 2;
    int carriage =0;

    bool is_shown = true;
    bool need_redraw = true;
    float hide_level = 2.0f;

    Console(sf::RenderWindow &window);

public:
	sf::RenderWindow & window;

    template<typename T>
    friend Console & operator<<(Console & c, const T & data);

    void show(bool is);
	void draw();
    void display();

    static void set_window(sf::RenderWindow * window);
    static Console & get();
    static void release();

private:
    void addContent(const std::string & text);
    void addChar(char c);
    void nextLine();
    void clearLine(int line);
};

template <typename T>
Console & operator<<(Console & c, const T &data)
{
    std::stringstream ss;
    std::string text;
    ss<<data;
    text = ss.str();

    c.addContent(text);

    return c;
}

#endif /* CONSOLE_H_ */
