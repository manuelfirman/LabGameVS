#ifndef EDITOR_MAPA_H
#define EDITOR_MAPA_H
#include "Modo_Editor.h"



class Editor_Mapa : public Modo_Editor
{
	private:
        sf::Text _textoCursor;
        sf::RectangleShape _barraLateral;
        sf::IntRect _rectTextura;
        sf::RectangleShape _rectSelector;
        gui::SelectorTexturas* _selectorTexturas;

        
        bool _colision;
        short _tipo;
        int _capa;
        bool _bloqueoTile;

    private:
        void iniciarVariables();
        void iniciarGUI();

	public:
		Editor_Mapa(DatosEstado* datos_estado, DatosEditor* datos_editor, TileMap* tile_map);
		virtual ~Editor_Mapa();

        void actualizarInput(const float& DT);
        void actualizarGUI(const float& DT);
        void actualizar(const float& DT);

        void renderizarGUI(sf::RenderTarget& target);
        void renderizar(sf::RenderTarget& target);
};

#endif