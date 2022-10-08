#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

enum estado_movimiento { QUIETO = 0, MOVIENDO, MOV_IZQUIERDA, MOV_DERECHA, MOV_ABAJO, MOV_ARRIBA };

class Movimiento
{
private: // Atributos
    sf::Sprite& _sprite;
    float _velocidadMax;
    float _aceleracion;
    float _desaceleracion;
    sf::Vector2f _velocidad;

public:
    Movimiento(sf::Sprite& sprite, float velocidadMaxima, float aceleracion, float desaceleracion);
    virtual ~Movimiento();

    const sf::Vector2f& getVelocidad() const;
    const float& getVelocidadMax() const;

    const bool getEstadoMov(const int estado) const;

    void detenerXY();
    void detenerX();
    void detenerY();
    void mover(const float dir_x, const float dir_y, const float& DT);
    void actualizar(const float& DT);



};

#endif // MOVIMIENTO_H