#include "stdafx.h" // precompilado
#include "EstadoEditor.h"

/// --------------------- INICIALIZACIONES --------------------------
void EstadoEditor::iniciarVariables()
{
    _rectTextura = sf::IntRect(0, 0, static_cast<int>(_datosEstado->tamanioCuadro), static_cast<int>(_datosEstado->tamanioCuadro));

    _colision = false;
    _tipo = TipoTile::DEFAULT;

    _velocidadCamara = 100.f;
}

void EstadoEditor::iniciarVista()
{
    _vista.setSize(sf::Vector2f(_datosEstado->opcionesGraficas->_resolucion.width, _datosEstado->opcionesGraficas->_resolucion.height));
    _vista.setCenter(_datosEstado->opcionesGraficas->_resolucion.width / 2.f, _datosEstado->opcionesGraficas->_resolucion.height / 2.f);
}

void EstadoEditor::iniciarKeybinds()
{
    std::ifstream archivo("config/teclas_editorestado.ini");

    if (archivo.is_open()) {
        std::string accion = "";
        std::string tecla = "";

        while (archivo >> accion >> tecla) {
            _keybinds[accion] = _teclasSoportadas->at(tecla);
        }
    }
}

void EstadoEditor::iniciarFondo()
{


}

void EstadoEditor::iniciarFuentes()
{
    if (!_fuente.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_EditorEstado_Botones" << std::endl;
    }
}

void EstadoEditor::iniciarTexto()
{
    /// VER POSICION MOUSE AL LADO DE LA FLECHA (QUITAR DESPUES)
    _textoCursor.setFont(_fuente);
    _textoCursor.setFillColor(sf::Color::White);
    _textoCursor.setCharacterSize(12);
    _textoCursor.setPosition(posMouseVista.x, posMouseVista.y - 50);

}

void EstadoEditor::iniciarMenuPausa()
{
    _menuPausa = new MenuPausa(*_ventana, _fuente);

    _menuPausa->agregarBoton("SALIR", 800.f, "SALIR");

    _menuPausa->agregarBoton("GUARDAR", 600.f, "GUARDAR");

    _menuPausa->agregarBoton("CARGAR", 400.f, "CARGAR");
}

void EstadoEditor::iniciarBotones()
{

}

void EstadoEditor::iniciarGUI()
{
    _barraLateral.setSize(sf::Vector2f(80.f ,static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height)));
    _barraLateral.setFillColor(sf::Color(50, 50, 50, 100));
    _barraLateral.setOutlineColor(sf::Color(200, 200, 200, 150));
    _barraLateral.setOutlineThickness(1.f);

    _rectSelector.setSize(sf::Vector2f(_datosEstado->tamanioCuadro, _datosEstado->tamanioCuadro));
    _rectSelector.setFillColor(sf::Color(255, 255, 255, 150));
    _rectSelector.setOutlineThickness(1.f);
    _rectSelector.setOutlineColor(sf::Color::Green);
    _rectSelector.setTexture(_tileMap->getTexturaTile());
    _rectSelector.setTextureRect(_rectTextura);

    _selectorTexturas = new gui::SelectorTexturas(20.f, 20.f, 500.f, 500.f, _datosEstado->tamanioCuadro, _tileMap->getTexturaTile(), _fuente, "TS");
}

void EstadoEditor::iniciarTileMap()
{
    _tileMap = new TileMap(_datosEstado->tamanioCuadro, 15, 20, "recursos/img/mapa/grass/floortileset.png");
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoEditor::EstadoEditor(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->iniciarVariables();
    this->iniciarVista();
    this->iniciarKeybinds();
    this->iniciarFondo();
    this->iniciarFuentes();
    this->iniciarTexto();
    this->iniciarMenuPausa();
    this->iniciarBotones();
    this->iniciarTileMap();
    this->iniciarGUI();

}

EstadoEditor::~EstadoEditor()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }

    delete _menuPausa;
    delete _tileMap;
    delete _selectorTexturas;
}


/// --------------------- ACTUALIZACIONES --------------------------
void EstadoEditor::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE"))) && getPpsTeclas())
    {
        if (!_pausa) pausarEstado();
        else reanudarEstado();
        //(_pausa) ? pausarEstado() : reanudarEstado();
    }
}

void EstadoEditor::actualizarInputEditor(const float& DT)
{
    // Mover vista
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_ARRIBA"))) && getPpsTeclas())
    {
        _vista.move(0.f, -_velocidadCamara * DT);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_ABAJO"))) && getPpsTeclas())
    {
        _vista.move(0.f, _velocidadCamara * DT);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_DERECHA"))) && getPpsTeclas())
    {
        _vista.move(_velocidadCamara * DT, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_IZQUIERDA"))) && getPpsTeclas())
    {
        _vista.move(-_velocidadCamara * DT, 0.f);
    }


    // agregando un tile cuando clickeo
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getPpsTeclas())
    {
        if (!_barraLateral.getGlobalBounds().contains(sf::Vector2f(posMouseVentana)))
        {
            if (!_selectorTexturas->getActivo()) // Si no esta activo, agrega tile
            {
                _tileMap->agregarTile(posMouseCuadro.x, posMouseCuadro.y, 0, _rectTextura, _colision, _tipo);
            }
            else
            {
                _rectTextura = _selectorTexturas->getRectTextura();
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getPpsTeclas())
    {
        if (!_barraLateral.getGlobalBounds().contains(sf::Vector2f(posMouseVentana)))
        {
            if (!_selectorTexturas->getActivo()) // Si esta activo, remueve tile
            {
                _tileMap->removerTile(posMouseCuadro.x, posMouseCuadro.y, 0);
            }
        }
    }

    // Colision
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("COLISION"))) && getPpsTeclas())
    {
        _colision = !_colision;
    }// Tipo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("INCREMENTAR_TIPO"))) && getPpsTeclas())
    {
        ++_tipo; // TODO: validar que no se pase
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("DISMINUIR_TIPO"))) && getPpsTeclas())
    {
        if (_tipo > 0)
            --_tipo;
    }
}

void EstadoEditor::actualizarBotones()
{
    for (auto& botones : _boton) {
        botones.second->actualizar(posMouseVentana);
    }

}

void EstadoEditor::actualizarGUI(const float& DT)
{
    _selectorTexturas->actualizar(posMouseVentana, DT);
    if (!_selectorTexturas->getActivo())
    {
        _rectSelector.setTextureRect(_rectTextura);
        _rectSelector.setPosition(posMouseCuadro.x * _datosEstado->tamanioCuadro, posMouseCuadro.y * _datosEstado->tamanioCuadro);
    }


    _textoCursor.setPosition(posMouseVista.x, posMouseVista.y - 50);
    std::stringstream ss;
    ss << posMouseVista.x << " " << posMouseVista.y << "\n"
        << posMouseCuadro.x << " " << posMouseCuadro.y << "\n"
        << _rectTextura.left << " " << _rectTextura.top << "\n"
        << "Colision: " << _colision << "\n" << "Tipo: " << _tipo;

    _textoCursor.setString(ss.str());
}

void EstadoEditor::actualizarBotonesMenuPausa()
{
    if (_menuPausa->getClick("CARGAR"))
        _tileMap->cargarDesdeArchivo("text.slmp");

    if (_menuPausa->getClick("GUARDAR"))
        _tileMap->guardarEnArchivo("text.slmp");

    if (_menuPausa->getClick("SALIR"))
        finEstado();
}

// ACTUALIZAR ESTADO EDITOR
void EstadoEditor::actualizar(const float& DT)
{
    actualizarPosicionMouse(&_vista);
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa) // No pausa
    {
        actualizarGUI(DT);
        actualizarBotones();
        actualizarInputEditor(DT);
    }
    else // pausa
    {
        _menuPausa->actualizar(posMouseVentana);
        actualizarBotonesMenuPausa();
    }

}


/// --------------------- RENDERIZAR --------------------------
void EstadoEditor::renderBotones(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}

void EstadoEditor::renderizarGUI(sf::RenderTarget& target)
{
    if(!_selectorTexturas->getActivo())
        target.draw(_rectSelector);

    _selectorTexturas->renderizar(target);
    target.draw(_textoCursor);

    target.draw(_barraLateral);
}

void EstadoEditor::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->setView(_vista);
    _tileMap->renderizar(*target);
  
    target->setView(_ventana->getDefaultView());
    renderBotones(*target);
    renderizarGUI(*target);


    if (_pausa)
    {
        _menuPausa->renderizar(*target);
    }

    target->draw(_textoCursor);
}
