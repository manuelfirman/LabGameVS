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

        TileMap* _tileMap;

        sf::RectangleShape rectSelector;

    private: // Metodos
        void iniciarVariables();
        void iniciarKeybinds();
        void iniciarFondo();
        void iniciarFuentes();
        void iniciarMenuPausa();
        void iniciarBotones();
        void iniciarGUI();
        void iniciarTileMap();

    public:
        EstadoEditor(DatosEstado* datos_estado);
        ~EstadoEditor();

        void actualizarInput(const float& DT);
        void actualizarInputEditor(const float& DT);
        void actualizarBotones();
        void actualizarGUI();
        void actualizarBotonesMenuPausa();
        void actualizar(const float& DT);

        void renderBotones(sf::RenderTarget& target);
        void renderizarGUI(sf::RenderTarget& target);
        void renderizar(sf::RenderTarget* target = NULL);
};

#endif // EDITORESTADO_H
