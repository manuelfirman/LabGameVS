#ifndef EDITOR_SPAWNERENEMIGOS_H
#define EDITOR_SPAWNERENEMIGOS_H

#include "Modo_Editor.h"
#include "SpawnerEnemigos.h"

class Editor_SpawnerEnemigos : public Modo_Editor
{
	private:
		sf::Text _textoCursor;
		sf::RectangleShape _barraLateral;
		sf::RectangleShape _rectSelector;
		sf::IntRect _rectTextura;

		int _tipoEnemigo;
		int _cantidadEnemigos;
		int _tiempoSpawn;
		float _distanciaMax;

	private:
		void iniciarVariables();
		void iniciarGUI();
		
	public:
		Editor_SpawnerEnemigos(DatosEstado* datos_estado, DatosEditor* datos_editor, TileMap* tile_map);
		virtual ~Editor_SpawnerEnemigos();

		void actualizarInput(const float& DT);
		void actualizarGUI(const float& DT);
		void actualizar(const float& DT);

		void renderizarGUI(sf::RenderTarget& target);
		void renderizar(sf::RenderTarget& target);
};

#endif
