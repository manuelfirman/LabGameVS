#ifndef HITBOX_H
#define HITBOX_H

class Hitbox
{
private:
    sf::Sprite& _sprite;
    sf::RectangleShape _hitbox;
    sf::FloatRect _posicionSiguiente;
    float _offsetX;
    float _offsetY;

public:
    Hitbox(sf::Sprite& _sprite, float x, float y, float ancho, float alto);
    virtual ~Hitbox();

    // Setters
    void setPosicion(const sf::Vector2f& posicion);
    void setPosicion(const float x, const float y);

    // Getters
    const sf::Vector2f& getPosicion() const;
    const sf::FloatRect getLimites() const;
    const sf::FloatRect& getPosicionSiguiente(const sf::Vector2f& velocidad);

    bool interseccion(const sf::FloatRect& frect);
    void actualizar();
    void renderizar(sf::RenderTarget& target);

};

#endif // HITBOX_H

