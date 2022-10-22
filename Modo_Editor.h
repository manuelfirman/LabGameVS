#ifndef MODO_EDITOR_H
#define MODO_EDITOR_H

#include "EstadoBase.h"
#include "TileMap.h"
#include "Gui.h"

class DatosEditor
{
public:
    DatosEditor() {};

    sf::Font* fuente;
    // Control de ingresos de teclado por segundo
    float* ppsTeclas;
    float* ppsTeclasMax;
    // vista cam
    sf::View* vista;
    // keybinds
    std::map<std::string, int>* keybinds;
    // Posiciones Mouse
    sf::Vector2i* posMousePantalla;
    sf::Vector2i* posMouseVentana;
    sf::Vector2f* posMouseVista;
    sf::Vector2i* posMouseCuadro;
};

class Modo_Editor
{
	private:

    protected:
        DatosEstado* _datosEstado;
        DatosEditor* _datosEditor;

        TileMap* _tileMap;
	public:
        Modo_Editor(DatosEstado* datos_estado, DatosEditor* datos_editor, TileMap* _tileMap);
        virtual ~Modo_Editor();

        const bool getPpsTeclas();

        virtual void actualizarInput(const float& DT) = 0;
        virtual void actualizarGUI(const float& DT) = 0;
        virtual void actualizar(const float& DT) = 0;

        virtual void renderizarGUI(sf::RenderTarget& target) = 0;
        virtual void renderizar(sf::RenderTarget& target) = 0;
};

#endif