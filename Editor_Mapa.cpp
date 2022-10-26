#include "stdafx.h"
#include "Editor_Mapa.h"

void Editor_Mapa::iniciarVariables()
{
    _rectTextura = sf::IntRect(0, 0, static_cast<int>(_datosEstado->tamanioCuadro), static_cast<int>(_datosEstado->tamanioCuadro));

    _colision = false;
    _tipo = tipo_tile::SUELO;
    _capa = 0;
    _bloqueoTile = false;

    
}

void Editor_Mapa::iniciarGUI()
{
    /// VER POSICION MOUSE AL LADO DE LA FLECHA (QUITAR DESPUES)
    _textoCursor.setFont(*_datosEditor->fuente);
    _textoCursor.setFillColor(sf::Color::White);
    _textoCursor.setCharacterSize(12);
    _textoCursor.setPosition(_datosEditor->posMouseVista->x, _datosEditor->posMouseVista->y - 50);

    // Barra Lateral
    _barraLateral.setSize(sf::Vector2f(80.f, static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height)));
    _barraLateral.setFillColor(sf::Color(50, 50, 50, 100));
    _barraLateral.setOutlineColor(sf::Color(200, 200, 200, 150));
    _barraLateral.setOutlineThickness(1.f);
    // Selector (Cuadro)
    _rectSelector.setSize(sf::Vector2f(_datosEstado->tamanioCuadro, _datosEstado->tamanioCuadro));
    _rectSelector.setFillColor(sf::Color(255, 255, 255, 150));
    _rectSelector.setOutlineThickness(1.f);
    _rectSelector.setOutlineColor(sf::Color::Green);
    _rectSelector.setTexture(_tileMap->getTexturaTile());
    _rectSelector.setTextureRect(_rectTextura);
    // Inicializa selector de texturas
    _selectorTexturas = new gui::SelectorTexturas(20.f, 20.f, 512.f, 1024.f, _datosEstado->tamanioCuadro, _tileMap->getTexturaTile(), *_datosEditor->fuente, "TS");
}

Editor_Mapa::Editor_Mapa(DatosEstado* datos_estado, DatosEditor* datos_editor, TileMap* tile_map)
	: Modo_Editor(datos_estado, datos_editor, tile_map)
{
    this->iniciarVariables();
    this->iniciarGUI();
}

Editor_Mapa::~Editor_Mapa()
{
    delete _selectorTexturas;
}

void Editor_Mapa::actualizarInput(const float& DT)
{
    // agregando un tile cuando clickeo
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getPpsTeclas())
    {
        if (!_barraLateral.getGlobalBounds().contains(sf::Vector2f(*_datosEditor->posMouseVentana)))
        {
            if (!_selectorTexturas->getActivo()) // Selector inactivo
            {
                if (_bloqueoTile) // bloqueo tile
                {
                    if(_tileMap->tileVacio(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y, 0)) // tile vacio
                    {
                        _tileMap->agregarTile(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y, 0, _rectTextura, _colision, _tipo);
                    }
                }
                else
                {

                    _tileMap->agregarTile(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y, 0, _rectTextura, _colision, _tipo);
                }
            }
            else
            {
                _rectTextura = _selectorTexturas->getRectTextura();
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getPpsTeclas())
    {
        if (!_barraLateral.getGlobalBounds().contains(sf::Vector2f(*_datosEditor->posMouseVentana)))
        {
            if (!_selectorTexturas->getActivo()) // Si esta activo, remueve tile
            {
                _tileMap->removerTile(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y, 0);
            }
        }
    }

    // Colision
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("COLISION"))) && getPpsTeclas())
    {
        _colision = !_colision;
    }// Tipo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("INCREMENTAR_TIPO"))) && getPpsTeclas())
    {
        if(_tipo < 4)
            ++_tipo;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("DISMINUIR_TIPO"))) && getPpsTeclas())
    {
        if (_tipo > 0)
            --_tipo;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_datosEditor->keybinds->at("BLOQUEAR_TILE"))) && getPpsTeclas())
    {
        _bloqueoTile = !_bloqueoTile;
    }
}


void Editor_Mapa::actualizarGUI(const float& DT)
{
    _selectorTexturas->actualizar(*_datosEditor->posMouseVentana, DT);
    if (!_selectorTexturas->getActivo())
    {
        _rectSelector.setTextureRect(_rectTextura);
        _rectSelector.setPosition(_datosEditor->posMouseCuadro->x * _datosEstado->tamanioCuadro, _datosEditor->posMouseCuadro->y * _datosEstado->tamanioCuadro);
    }


    _textoCursor.setPosition(_datosEditor->posMouseVista->x, _datosEditor->posMouseVista->y - 50);
    std::stringstream ss;
    ss << "Pos Vista: " << _datosEditor->posMouseVista->x << " " << _datosEditor->posMouseVista->y << "\n"
        << "Pos Cuadro: " << _datosEditor->posMouseCuadro->x << " " << _datosEditor->posMouseCuadro->y << "\n"
        << "Rect px: " << _rectTextura.left << " " << _rectTextura.top << "\n"
        << "Colision: " << _colision << "\n"
        << "Tipo Tile: " << _tipo << "\n"
        << "Cant Tiles: " << _tileMap->getTilesPorCuadro(_datosEditor->posMouseCuadro->x, _datosEditor->posMouseCuadro->y, _capa) << "\n"
        << "Bloqueo: " << _bloqueoTile;

    _textoCursor.setString(ss.str());
}

void Editor_Mapa::actualizar(const float& DT)
{
    this->actualizarGUI(DT);
    this->actualizarInput(DT);
}


void Editor_Mapa::renderizarGUI(sf::RenderTarget& target)
{
    if (!_selectorTexturas->getActivo())
    {
        // dibujar tilea partir de textura con vista seteada
        target.setView(*_datosEditor->vista);
        target.draw(_rectSelector);
    }

    // render selector de texturas y barra lateral con vista por default
    target.setView(_datosEstado->ventana->getDefaultView());
    _selectorTexturas->renderizar(target);
    target.draw(_barraLateral);

    // dibujar texto mouse con vista seteada
    target.setView(*_datosEditor->vista);
    target.draw(_textoCursor);
}

void Editor_Mapa::renderizar(sf::RenderTarget& target)
{
    renderizarGUI(target);
    target.draw(_textoCursor);
}
