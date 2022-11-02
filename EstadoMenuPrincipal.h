#ifndef ESTADOMENUPRINCIPAL_H
#define ESTADOMENUPRINCIPAL_H
#include "EstadoBase.h"
#include "EstadoJuego.h"
#include "EstadoEditor.h"
#include "EstadoOpciones.h"
#include "EstadoCargarPartida.h"
#include "EstadoTutorial.h"
#include "Gui.h"

class EstadoMenuPrincipal : public EstadoBase
{
private: // Atributos
    sf::Texture _texturaFondoMenu;
    sf::RectangleShape _fondoMenu;
    sf::Text _tituloMenu;
    sf::Text _subtituloMenu;
    sf::Font _fuenteMenu;
    sf::Font _fuenteBoton;
    bool _resetMenu;
    std::map<std::string, gui::Boton*> _boton;


private: // Metodos
    void iniciarVariables();
    void iniciarKeybinds();
    void iniciarFuentes();
    void iniciarGUI();
    void resetGUI();

public:
    EstadoMenuPrincipal(DatosEstado* datos_estado);
    ~EstadoMenuPrincipal();

    void actualizarBotones();
    void renderBotones(sf::RenderTarget& target);

    void actualizarTitulo();
    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // ESTADOMENUPRINCIPAL_H
