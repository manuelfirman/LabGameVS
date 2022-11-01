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
    _clickBoton = false;
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

void EstadoBase::actualizarPosicionMouse(sf::View* vista)
{
    _posMousePantalla = sf::Mouse::getPosition();
    _posMouseVentana = sf::Mouse::getPosition(*_ventana);

    if(vista)
        _ventana->setView(*vista);
    
    _posMouseVista = _ventana->mapPixelToCoords(sf::Mouse::getPosition(*_ventana));
    
    // Posiciona en cuadricula (por eso casteo estatico de unsigned)
    _posMouseCuadro = sf::Vector2i(static_cast<int>(_posMouseVista.x) / static_cast<int>(_tamanioCuadro), static_cast<int>(_posMouseVista.y) / static_cast<int>(_tamanioCuadro));

    _ventana->setView(_ventana->getDefaultView());
}

void EstadoBase::actualizarPpsTeclas(const float& DT)
{
    if(_ppsTeclas < _ppsTeclasMax)
        _ppsTeclas += 50.f * DT;
}
