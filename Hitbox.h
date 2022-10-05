#ifndef HITBOX_H
#define HITBOX_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <ctime>
#include <cstdlib>
#include <iostream>

#include <fstream>

class Hitbox
{
private:
    sf::Sprite& _sprite;
    sf::RectangleShape _hitbox;
    float _offsetX;
    float _offsetY;

public:
    Hitbox(sf::Sprite& _sprite, float x, float y, float ancho, float alto);
    virtual ~Hitbox();

    bool checkInterseccion(const sf::FloatRect& frect);
    void actualizar();
    void renderizar(sf::RenderTarget& target);

};

#endif // HITBOX_H

