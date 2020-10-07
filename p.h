 #ifndef P_H
#define P_H

#include <SFML/Graphics.hpp>
#include "IOStuff/program.h"
#include "IOStuff/console.h"
#include "IOStuff/touchable.h"
#include "IOStuff/ui.h"
#include "IOStuff/programstage.h"

#include "IOStuff/resource_manager.h"
#include "ScriptStuff/script.h"
#include "PlatformerStuff/tilemap.h"
#include "PlatformerStuff/dynamic.h"
#include "PlatformerStuff/steeringmanager.h"
#include "IOStuff/line.h"

#include "EntityStuff/pool.hpp"

class P : public ProgramStage 
{
    sf::RenderWindow & win;
    sf::CircleShape s;
    UI ui;
    TileMap tile_map;
    Colidable hero;
    SteeringManager steering;
    sf::Texture texture;

public:
    P(sf::RenderWindow & win);
    ~P() override;
    virtual void init() override;
    virtual void render(sf::RenderWindow & win) override;
    virtual void update(double dt) override;
    virtual void input(sf::Event &ev) override;
	virtual void release() override;
};


#endif // P_H
