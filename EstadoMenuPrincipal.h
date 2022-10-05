#ifndef ESTADOMENUPRINCIPAL_H
#define ESTADOMENUPRINCIPAL_H
#include "EstadoBase.h"
#include "EstadoJuego.h"
#include "EstadoEditor.h"
#include "EstadoOpciones.h"
#include "Gui.h"

class EstadoMenuPrincipal : public EstadoBase
{
private: // Atributos
    sf::Texture _texturaFondoMenu;
    sf::RectangleShape _fondoMenu;
    sf::Font _fuenteMenu;
    sf::Font _fuenteBoton;

    std::map<std::string, gui::Boton*> _boton;

private: // Metodos
    void iniciarVariables();
    void iniciarKeybinds();
    void iniciarFondo();
    void iniciarFuentes();
    void iniciarBotones();

public:
    EstadoMenuPrincipal(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado);
    ~EstadoMenuPrincipal();

    void actualizarBotones();
    void renderBotones(sf::RenderTarget& target);


    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // ESTADOMENUPRINCIPAL_H