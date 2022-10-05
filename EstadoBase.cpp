#include "stdafx.h" // precompilado
#include "EstadoBase.h"
/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoBase::EstadoBase(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado)
{
    _ventana = ventana;
    _salir = false;
    _pausa = false;
    _estado = estado;
    _teclasSoportadas = teclasSoportadas;
    _ppsTeclas = 0.f;
    _ppsTeclasMax = 10.f;

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
        _ppsTeclas += 100.f * DT;
}
