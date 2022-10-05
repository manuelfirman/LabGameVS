#include "stdafx.h" // precompilado
#include "EstadoBase.h"
/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoBase::EstadoBase(DatosEstado* datos_estado)
{
    _datosEstado = datos_estado;
    _ventana = datos_estado->ventana;
    _salir = false;
    _pausa = false;
    _estado = datos_estado->estado;
    _teclasSoportadas = datos_estado->teclasSoportadas;
    _ppsTeclas = 0.f;
    _ppsTeclasMax = 10.f;
    _tamanioCuadro = datos_estado->tamanioCuadro;
}

EstadoBase::~EstadoBase()
{
    //dtor
}


/// --------------------- FUNCIONES ---------------------
void EstadoBase::finEstado()
{
    _salir = true;
}

void EstadoBase::pausarEstado()
{
    _pausa = true;
}

void EstadoBase::reanudarEstado()
{
    _pausa = false;
}

const bool& EstadoBase::getSalir() const
{
    return _salir;
}

const bool EstadoBase::getPpsTeclas()
{
    if(_ppsTeclas >= _ppsTeclasMax) 
    {
        _ppsTeclas = 0.f; // reset keytime
        return true;
    }
    return false;
}

void EstadoBase::actualizarPosicionMouse()
{
    posMousePantalla = sf::Mouse::getPosition();
    posMouseVentana = sf::Mouse::getPosition(*_ventana);
    posMouseVista = _ventana->mapPixelToCoords(sf::Mouse::getPosition(*_ventana));
}

void EstadoBase::actualizarPpsTeclas(const float& DT)
{
    if(_ppsTeclas < _ppsTeclasMax)
        _ppsTeclas += 50.f * DT;
}
