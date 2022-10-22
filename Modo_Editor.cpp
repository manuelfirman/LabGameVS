#include "stdafx.h"
#include "Modo_Editor.h"


Modo_Editor::Modo_Editor(DatosEstado* datos_estado, DatosEditor* datos_editor, TileMap* tile_map)
	: _datosEstado(datos_estado), _datosEditor(datos_editor), _tileMap(tile_map)
{
}

Modo_Editor::~Modo_Editor()
{
}

const bool Modo_Editor::getPpsTeclas()
{
    if (*_datosEditor->ppsTeclas >= *_datosEditor->ppsTeclasMax)
    {
        *_datosEditor->ppsTeclas = 0.f; // reset keytime
        return true;
    }
    return false;
}
