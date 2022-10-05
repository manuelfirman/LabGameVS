#ifndef ANIMACION_H
#define ANIMACION_H

class Animacion // Componente Animacion
{
private:
    class setAnimacion // Animacion (No puede instanciarse por fuera de clase Animacion)
    {
    public: // Atributos
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

        // Constructor/Dtor
        setAnimacion(sf::Sprite& sprite, sf::Texture& textura, float tiempoAnimacion, int inicio_x, int inicio_y, int frames_x, int frames_y, int ancho, int alto)
            : _spriteA(sprite), _texturaA(textura), _ancho(ancho), _alto(alto), _tiempoAnimacion(tiempoAnimacion), _timer(0.f), _done(false)
        {
            _cuadroInicial = sf::IntRect(inicio_x * ancho, inicio_y * alto, ancho, alto);
            _cuadroActual = _cuadroInicial;
            _cuadroFinal = sf::IntRect(frames_x * ancho, frames_y * alto, ancho, alto);

            _spriteA.setTexture(_texturaA);
            _spriteA.setTextureRect(_cuadroInicial);


        }
        //                ~setAnimacion();

        // Metodos
        const bool& isDone() {
            return _done;
        }

        const bool& play(const float& DT) // Normal
        {
            _done = false;
            _timer += 100.f * DT;
            if (_timer >= _tiempoAnimacion) {

                _timer = 0.f; // reset timer

                if (_cuadroActual != _cuadroFinal)
                {
                    _cuadroActual.left += _ancho; // Animar
                }
                else
                {
                    _cuadroActual.left = _cuadroInicial.left; // Reset animacion
                    _done = true;
                }

                _spriteA.setTextureRect(_cuadroActual);
            }
            return _done;
        }

        const bool& play(const float& DT, float porcentajeModificador) // Con modificadores
        {
            _done = false;

            if (porcentajeModificador < 0.5f)
                porcentajeModificador = 0.5f;

            _timer += porcentajeModificador * 100.f * DT; // x porcentaje modificador
            if (_timer >= _tiempoAnimacion) {

                _timer = 0.f; // reset timer

                if (_cuadroActual != _cuadroFinal)
                {
                    _cuadroActual.left += _ancho; // Animar
                }
                else
                {
                    _cuadroActual.left = _cuadroInicial.left; // Reset animacion
                    _done = true;
                }

                _spriteA.setTextureRect(_cuadroActual);
            }
            return _done;
        }

        void reset()
        {
            _timer = _tiempoAnimacion;
            _cuadroActual = _cuadroInicial;
        }
    };

    sf::Sprite& _spriteCA;
    sf::Texture& _texturaCA;
    std::map<std::string, setAnimacion*> _animaciones;
    setAnimacion* _ultimaAnimacion;
    setAnimacion* _animacionPrioritaria;

public:
    // Constructor - Forzando a usar sprite y textura - No se puede tener animacion sin ellos
    Animacion(sf::Sprite& sprite, sf::Texture& textura);
    virtual ~Animacion();

    const bool& isDone(const std::string key);

    // Metodos
    void agregarAnimacion(const std::string key, float tiempoAnimacion, int inicio_x, int inicio_y, int frames_x, int frames_y, int ancho, int alto);

    const bool& play(const std::string key, const float& DT, const bool prioridad = false);
    const bool& play(const std::string key, const float& DT, const float& modificador, const float& modificador_max, const bool prioridad = false);

};

#endif // ANIMACION_H