#ifndef EDITORESTADO_H
#define EDITORESTADO_H

#include "EstadoBase.h"
#include "Gui.h"
#include "MenuPausa.h"
#include "TileMap.h"

class EstadoBase;
class Gui;
class MenuPausa;
class TileMap;

class EstadoEditor : public EstadoBase
{
    private: // Atributos
        sf::View _vista;

        sf::Font _fuente;
        sf::Text _textoCursor;
        MenuPausa* _menuPausa;
        
        std::map<std::string, gui::Boton*> _boton;

        TileMap* _tileMap;

        sf::RectangleShape _barraLateral;

        sf::IntRect _rectTextura;
        sf::RectangleShape _rectSelector;

        gui::SelectorTexturas* _selectorTexturas;

        float _velocidadCamara;
        bool _colision;
        short _tipo;
        int _capa;

    private: // Metodos
        void iniciarVariables();
        void iniciarVista();
        void iniciarKeybinds();
        void iniciarFondo();
        void iniciarFuentes();
        void iniciarTexto();
        void iniciarMenuPausa();
        void iniciarBotones();
        void iniciarTileMap();
        void iniciarGUI();

    public:
        EstadoEditor(DatosEstado* datos_estado);
        ~EstadoEditor();

        void actualizarInput(const float& DT);
        void actualizarInputEditor(const float& DT);
        void actualizarBotones();
        void actualizarGUI(const float& DT);
        void actualizarBotonesMenuPausa();
        void actualizar(const float& DT);

        void renderBotones(sf::RenderTarget& target);
        void renderizarGUI(sf::RenderTarget& target);
        void renderizar(sf::RenderTarget* target = NULL);
};

#endif // EDITORESTADO_H
