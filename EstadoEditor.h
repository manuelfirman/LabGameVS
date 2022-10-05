#ifndef EDITORESTADO_H
#define EDITORESTADO_H

#include "EstadoBase.h"
#include "Gui.h"

class EstadoEditor : public EstadoBase
{
private: // Atributos
    sf::Font _fuenteBoton;
    std::map<std::string, gui::Boton*> _boton;

private: // Metodos
    void iniciarVariables();
    void iniciarKeybinds();
    void iniciarFondo();
    void iniciarFuentes();
    void iniciarBotones();

public:
    EstadoEditor(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado);
    ~EstadoEditor();

    void actualizarBotones();
    void renderBotones(sf::RenderTarget& target);


    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // EDITORESTADO_H
