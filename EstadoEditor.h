#ifndef EDITORESTADO_H
#define EDITORESTADO_H

#include "EstadoBase.h"
#include "Gui.h"
#include "MenuPausa.h"
#include "TileMap.h"
#include "Editor_Mapa.h"
#include "Editor_SpawnerEnemigos.h"


enum mod_editor{ MAPA = 0, ENEMIGOS };


class EstadoEditor : public EstadoBase
{
    private: // Atributos
        DatosEditor _datosEditor;
        
        sf::View _vista;
        float _velocidadCamara;

        sf::Font _fuente;
        MenuPausa* _menuPausa;

        std::map<std::string, gui::Boton*> _boton;

        TileMap* _tileMap;

        std::vector<Modo_Editor*> _vModo;
        unsigned _modoEditor;

    private: // Metodos
        void iniciarModos();


        void iniciarVariables();
        void iniciarDatosEditor();
        void iniciarVista();
        void iniciarKeybinds();
        void iniciarFondo();
        void iniciarFuentes();
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
        void actualizarModos(const float& DT);
        void actualizar(const float& DT);

        void renderBotones(sf::RenderTarget& target);
        void renderizarGUI(sf::RenderTarget& target);
        void renderizarModos(sf::RenderTarget& target);
        void renderizar(sf::RenderTarget* target = NULL);
};

#endif // EDITORESTADO_H
