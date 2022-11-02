#ifndef ESTADOCARGARPARTIDA_H
#define ESTADOCARGARPARTIDA_H

#include "EstadoBase.h"
#include "EstadoJuego.h"
#include "Gui.h"
#include "Audio.h"


class EstadoCargarPartida : public EstadoBase
{
private: // Atributos
    sf::Texture _texturaFondoCargar;
    sf::RectangleShape _fondoCargar;
    sf::Font _fuenteCargar;

    sf::Text _textoCargar;
    sf::Text _textoNuevoJuego;
    std::vector<sf::VideoMode> _modoVideo;

    std::map<std::string, gui::Boton*> _boton;

    bool _resetMusica;

    bool _slot[3];

private: // Metodos
    void iniciarVariables();
    void iniciarKeybinds();
    void iniciarFuentes();
    void iniciarGUI();
    void resetGUI();

public:
    EstadoCargarPartida(DatosEstado* datos_estado);
    virtual ~EstadoCargarPartida();
    void actualizarGUI(const float& DT);
    void renderizarGUI(sf::RenderTarget& target);
    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif