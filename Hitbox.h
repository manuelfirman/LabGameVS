#ifndef HITBOX_H
#define HITBOX_H

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

