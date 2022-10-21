#pragma once
class Animacion2
{
    private:
        sf::Sprite& _spriteA;
        sf::Texture& _texturaA;
        //float _velocidad;
        float _tiempoAnimacion;
        float _timer;
        int _ancho;
        int _alto;
        bool _done;

        sf::IntRect _cuadroInicial;
        sf::IntRect _cuadroActual;
        sf::IntRect _cuadroFinal;

    public:
        Animacion2(sf::Sprite& sprite, sf::Texture& textura, float tiempoAnimacion, int inicio_x, int inicio_y, int frames_x, int frames_y, int ancho, int alto);
        const bool& isDone();
        const bool& play(const float& DT);
        void reset();
};

