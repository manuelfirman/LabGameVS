#include "stdafx.h"
#include "Editor_SpawnerEnemigos.h"

void Editor_SpawnerEnemigos::iniciarVariables()
{
    _tipoEnemigo = 0;
    _cantidadEnemigos = 1;
    _tiempoSpawn = 60;
    _distanciaMax = 500.f;
}

void Editor_SpawnerEnemigos::iniciarGUI()
{
    // Barra Lateral
    _barraLateral.setSize(sf::Vector2f(80.f, static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height)));
    _barraLateral.setFillColor(sf::Color(50, 50, 200, 100));
    _barraLateral.setOutlineColor(sf::Color(50, 50, 200, 150));
    _barraLateral.setOutlineThickness(1.f);
    //Texto
    _textoCursor.setFont(*_datosEditor->fuente);
    _textoCursor.setFillColor(sf::Color::White);
    _textoCursor.setCharacterSize(12);
    _textoCursor.setPosition(_datosEditor->posMouseVista->x, _datosEditor->posMouseVista->y - 50);
    // Selector (Cuadro)
    _rectSelector.setSize(sf::Vector2f(_datosEstado->tamanioCuadro, _datosEstado->tamanioCuadro));
    _rectSelector.setFillColor(sf::Color(255, 255, 255, 150));
    _rectSelector.setOutlineThickness(1.f);
    _rectSelector.setOutlineColor(sf::Color::Green);
}

Editor_SpawnerEnemigos::Editor_SpawnerEnemigos(DatosEstado* datos_estado, DatosEditor* datos_editor, TileMap* tile_map)
	: Modo_Editor(datos_estado, datos_editor, tile_map)
{
    this->iniciarVariables();
    this->iniciarGUI();
}

Editor_SpawnerEnemigos::~Editor_SpawnerEnemigos()
{
}

void Editor_SpawnerEnemigos::actualizarInput(const float& DT)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getPpsTeclas()) // agregar
    {
        if (!_barraLateral.getGlobalBounds().contains(sf::Vector2f(*_datosEditor->posMouseVentana)))
        {
            _tileMap->agregarTile(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y,0, _rectTextura, _tipoEnemigo, _cantidadEnemigos, _tiempoSpawn, static_cast<int>(_distanciaMax));
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getPpsTeclas()) // quitar
    {
        if (!_barraLateral.getGlobalBounds().contains(sf::Vector2f(*_datosEditor->posMouseVentana)))
        {
            _tileMap->removerTile(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y, 0, tipo_tile::SPAWNERENEMIGO);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("TIPO_SUMAR"))) && getPpsTeclas())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (_tipoEnemigo > 0)
                _tipoEnemigo--;
        }
        else if (_tipoEnemigo < 10)
            _tipoEnemigo++;
        else
            _tipoEnemigo = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("CANTIDAD_SUMAR"))) && getPpsTeclas())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (_cantidadEnemigos > 0)
                _cantidadEnemigos--;
        }
        else if (_cantidadEnemigos < 10)
            _cantidadEnemigos++;
        else
            _cantidadEnemigos = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("TSPAWN_SUMAR"))) && getPpsTeclas())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (_tiempoSpawn > 0)
                _tiempoSpawn--;
        }
        else if (_tiempoSpawn < 60)
            _tiempoSpawn++;
        else
            _tiempoSpawn = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("DISTANCIA_SUMAR"))) && getPpsTeclas())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (_distanciaMax > 0)
                _distanciaMax--;
        }
        else if (_distanciaMax < 1000)
            _distanciaMax++;
        else
            _distanciaMax = 0;
    }
}

void Editor_SpawnerEnemigos::actualizarGUI(const float& DT)
{
    _rectSelector.setPosition(_datosEditor->posMouseCuadro->x * _datosEstado->tamanioCuadro, _datosEditor->posMouseCuadro->y * _datosEstado->tamanioCuadro);
    _textoCursor.setPosition(_datosEditor->posMouseVista->x, _datosEditor->posMouseVista->y - 50);

    std::stringstream ss;
    ss  << "\n"
        << "Tipo Enemigo: " << _tipoEnemigo << "\n"
        << "Cantidad: " << _cantidadEnemigos << "\n"
        << "Distancia Max: " << _distanciaMax << "\n"
        << "Tiempo Spawn: " << _tiempoSpawn;

    _textoCursor.setString(ss.str());
}

void Editor_SpawnerEnemigos::actualizar(const float& DT)
{
    this->actualizarInput(DT);
    this->actualizarGUI(DT);
}

void Editor_SpawnerEnemigos::renderizarGUI(sf::RenderTarget& target)
{
    target.setView(*_datosEditor->vista); // vista seteada
    target.draw(_rectSelector);
    target.draw(_textoCursor);

    target.setView(target.getDefaultView()); // vista por default
    target.draw(_barraLateral);
}

void Editor_SpawnerEnemigos::renderizar(sf::RenderTarget& target)
{
    this->renderizarGUI(target);
}
