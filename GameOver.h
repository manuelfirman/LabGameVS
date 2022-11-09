#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "EstadoBase.h"
#include "Gui.h"


class GameOver : public EstadoBase
{
    private:
    sf::RectangleShape _fondoGameOver;
    sf::Font _fuenteGameOver;
    sf::Font _fuenteBotonGameOver;

    sf::Text _textoGameOver;
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
    GameOver(DatosEstado* datos_estado);
    virtual ~GameOver();
    void actualizarGUI(const float& DT);
    void renderizarGUI(sf::RenderTarget& target);
    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif 