#ifndef ESTADOTUTORIAL_H
#define ESTADOTUTORIAL_H

#include "EstadoBase.h"
#include "Gui.h"

class EstadoTutorial : public EstadoBase
{
private: // Atributos
    sf::Texture _texturaFondoTutorial;
    sf::RectangleShape _fondoTutorial;
    sf::Font _fuenteTutorial;

    sf::Text _textoTutorial1;
    sf::Text _textoTutorial2;
    sf::Text _tituloTutorial;
    std::vector<sf::VideoMode> _modoVideo;

    std::map<std::string, gui::Boton*> _boton;

    std::string tutorial1;
    std::string tutorial2;
    int con;

    bool _resetMusica;

    bool _slot[3];

private: // Metodos
    void iniciarVariables();
    void iniciarKeybinds();
    void iniciarFuentes();
    void iniciarGUI();
    void resetGUI();

public:
    EstadoTutorial(DatosEstado* datos_estado);
    virtual ~EstadoTutorial();
    void actualizarGUI(const float& DT);
    void renderizarGUI(sf::RenderTarget& target);
    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif //
