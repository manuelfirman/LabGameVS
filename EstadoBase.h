#ifndef ESTADOBASE_H
#define ESTADOBASE_H
#include "OpcionesGraficas.h"
#include "Audio.h"

class EstadoBase;


class DatosEstado
{
    public:
        float tamanioCuadro;
        sf::RenderWindow* ventana;
        OpcionesGraficas* opcionesGraficas;
        std::map<std::string, int>* teclasSoportadas;
        std::stack<EstadoBase*>* estado;
        Audio* audio;
        std::map<std::string, sf::SoundBuffer>* bufferSonidos;

        DatosEstado()
        {
            tamanioCuadro = 0;
            ventana = NULL;
            opcionesGraficas = NULL;
            teclasSoportadas = NULL;
            estado = NULL;
            audio = NULL;
            bufferSonidos = NULL;
        };
};


class EstadoBase
{
private:


protected: // Atributos
    std::stack<EstadoBase*>* _estado; // Pila de punteros que apuntan a pila de punteros EstadoBase (Para no hacer una copia)
    sf::RenderWindow* _ventana;
    DatosEstado* _datosEstado;

    std::map<std::string, int>* _teclasSoportadas;
    std::map<std::string, int> _keybinds;
    std::map<std::string, sf::Texture> _texturas;
    std::map<std::string, sf::SoundBuffer>* _bufferSonidos;
        
        
    float _tamanioCuadro;

    bool _salir;
    bool _pausa;

    // Control de ingresos de teclado por segundo
    float _ppsTeclas;
    float _ppsTeclasMax;
    
    // Posiciones Mouse
    sf::Vector2i _posMousePantalla;
    sf::Vector2i _posMouseVentana;
    sf::Vector2f _posMouseVista;
    sf::Vector2i _posMouseCuadro;

protected: // Metodos
    virtual void iniciarKeybinds() = 0;

public:
    EstadoBase(DatosEstado* datos_estado);
    virtual ~EstadoBase();

    // Accesorios
    const bool& getSalir() const;
    const bool getPpsTeclas();

    // salida de estado
    void finEstado();
    void pausarEstado();
    void reanudarEstado();

    // Funciones
    virtual void actualizarPosicionMouse(sf::View* vista = NULL);
    virtual void actualizarPpsTeclas(const float& DT);

    // virtuales puras
    virtual void actualizarInput(const float& DT) = 0;
    virtual void actualizar(const float& DT) = 0;
    virtual void renderizar(sf::RenderTarget* target = NULL) = 0;
};

#endif // ESTADOBASE_H