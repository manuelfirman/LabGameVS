#ifndef EDITORESTADO_H
#define EDITORESTADO_H

#include "EstadoBase.h"
#include "Gui.h"
#include "MenuPausa.h"
#include "TileMap.h"

class EstadoEditor : public EstadoBase
{
private: // Atributos
    MenuPausa* _menuPausa;
    sf::Font _fuente;
    std::map<std::string, gui::Boton*> _boton;

    TileMap _mapa;

private: // Metodos
    void iniciarVariables();
    void iniciarKeybinds();
    void iniciarFondo();
    void iniciarFuentes();
    void iniciarMenuPausa();
    void iniciarBotones();

public:
    EstadoEditor(DatosEstado* datos_estado);
    ~EstadoEditor();

    void actualizarBotones();
    void renderBotones(sf::RenderTarget& target);

    void actualizarBotonesMenuPausa();
    void actualizarInput(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // EDITORESTADO_H
