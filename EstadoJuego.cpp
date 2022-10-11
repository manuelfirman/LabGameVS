#include "stdafx.h" // precompilado
#include "EstadoJuego.h"
void EstadoJuego::renderizadoDiferido()
{
    // Creando lienzo
    _renderTextura.create(_datosEstado->opcionesGraficas->_resolucion.width, _datosEstado->opcionesGraficas->_resolucion.height);

    _renderSprite.setTexture(_renderTextura.getTexture());
    _renderSprite.setTextureRect(sf::IntRect(0, 0, _datosEstado->opcionesGraficas->_resolucion.width, _datosEstado->opcionesGraficas->_resolucion.height));
    
}
/// --------------------- INICIALIZACIONES --------------------------
void EstadoJuego::iniciarVistaCam()
{
    _vistaCam.setSize(static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.width), static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height));

    _vistaCam.setCenter(_datosEstado->opcionesGraficas->_resolucion.width / 2.f, _datosEstado->opcionesGraficas->_resolucion.height / 2.f);
}

void EstadoJuego::iniciarFuentes()
{
    if (!_fuenteJuego.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
    /*if (!_fuenteBoton.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal_Botones" << std::endl;
    }*/
}

void EstadoJuego::iniciarKeybinds()
{
    std::ifstream archivo("config/teclas_juego.ini");

    if (archivo.is_open()) {
        std::string accion = "";
        std::string tecla = "";

        while (archivo >> accion >> tecla) {
            _keybinds[accion] = _teclasSoportadas->at(tecla);
        }
    }

    archivo.close();
}

void EstadoJuego::iniciarTexturas()
{
    //sf::Texture aux;

    if (!_texturas["PLANTILLA_JUGADOR"].loadFromFile("recursos/img/personaje/1.png")) {
        std::cout << "ERROR: EstadoJuego_iniciarTexturas_CargaTexturaPersonaje" << std::endl;
    }
}

void EstadoJuego::iniciarMenuPausa()
{
    _menuPausa = new MenuPausa(_datosEstado->opcionesGraficas->_resolucion, _fuenteJuego);
    _menuPausa->agregarBoton("SALIR", gui::p2pY(46.3f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "SALIR");
}

void EstadoJuego::iniciarSombras()
{
    if (!_sombra.loadFromFile("vert_sombras.vert", "frag_sombras.frag"))
    {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUEDEN CARGAR LAS SOMBRAS." << std::endl;
    }
}

void EstadoJuego::iniciarJugadores()
{
    _jugador = new Jugador(0, 0, _texturas["PLANTILLA_JUGADOR"]);
}

void EstadoJuego::iniciarGUIJugador()
{
    _GUIJugador = new GUIJugador(_jugador, _datosEstado->opcionesGraficas->_resolucion);
}

void EstadoJuego::iniciarTileMap()
{
    _tileMap = new TileMap(_datosEstado->tamanioCuadro, 32, 32, "recursos/img/mapa/terrenos/terreno_01.png");

    // cargando mapa desde archivo
    _tileMap->cargarDesdeArchivo("text.slmp");
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoJuego::EstadoJuego(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->renderizadoDiferido();
    this->iniciarVistaCam();
    this->iniciarKeybinds();
    this->iniciarFuentes();
    this->iniciarTexturas();
    this->iniciarMenuPausa();
    this->iniciarSombras();

    this->iniciarTileMap();
    this->iniciarJugadores();
    this->iniciarGUIJugador();
}

EstadoJuego::~EstadoJuego()
{
    delete _jugador;
    delete _GUIJugador;
    delete _menuPausa;
    delete _tileMap;
}

/// --------------------- ACTUALIZACIONES --------------------------

void EstadoJuego::actualizarVistaCam(const float& DT)
{
    // Jugador centrado
    //_vistaCam.setCenter(std::floor(_jugador->getPosicionSprite().x), std::floor(_jugador->getPosicionSprite().y)); // floor para estabilizar el float en pixels 

    // Jugador centrado + movimiento de mouse
    _vistaCam.setCenter(
        std::floor(_jugador->getPosicionSprite().x + (static_cast<float>(posMouseVentana.x)) - (static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.width / 2) / 5.f)),
        std::floor(_jugador->getPosicionSprite().y + (static_cast<float>(posMouseVentana.y)) - (static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height / 2) / 5.f))); // floor para estabilizar el float en pixels 
}

void EstadoJuego::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE")))  && getPpsTeclas())
    {
        if (!_pausa) pausarEstado();
        else reanudarEstado();
        //(_pausa) ? pausarEstado() : reanudarEstado();
    }

}

void EstadoJuego::actualizarInputJugador(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_IZQUIERDA")))) {
        _jugador->mover(-1.f, 0.f, DT);
        _jugador->perderHP(1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_DERECHA")))) {

        _jugador->mover(1.f, 0.f, DT);
        _jugador->ganarHP(1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_ARRIBA"))))
        _jugador->mover(0.f, -1.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_ABAJO"))))
        _jugador->mover(0.f, 1.f, DT);

   

}

void EstadoJuego::actualizarBotonesPausa()
{
    if(_menuPausa->getClick("SALIR"))
        finEstado();
}

void EstadoJuego::actualizarTileMap(const float& DT)
{
    _tileMap->actualizar();
    _tileMap->checkColision(_jugador, DT);
}

void EstadoJuego::actualizar(const float& DT)
{
    actualizarPosicionMouse(&_vistaCam);
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa) // actualizar sin pausa
    {
        actualizarVistaCam(DT);

        actualizarInputJugador(DT);

        actualizarTileMap(DT);

        _jugador->actualizar(DT);

        _GUIJugador->actualizar(DT);

    }
    else // actualizar con pausa
    {
        _menuPausa->actualizar(posMouseVentana);
        actualizarBotonesPausa();
    }

}


/// --------------------- RENDERIZAR --------------------------
void EstadoJuego::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    _renderTextura.clear(); // limpia el frame anterior

    // TODO SE RENDERIZA A TRAVES DEL LIENZO
    _renderTextura.setView(_vistaCam); // con la vista seteada
    _tileMap->renderizar(_renderTextura, _jugador->getCuadroActual(static_cast<int>(_datosEstado->tamanioCuadro)), _jugador->getCentro(), &_sombra);
    _jugador->renderizar(_renderTextura, &_sombra);
    _tileMap->renderizacionDiferida(_renderTextura);

    _renderTextura.setView(_renderTextura.getDefaultView()); // vista por default
    _GUIJugador->renderizar(_renderTextura);

    if (_pausa) { 
        //_renderTextura.setView(_renderTextura.getDefaultView()); // vista por default
        _menuPausa->renderizar(_renderTextura);
    }

    _renderTextura.display(); // actualiza el contenido
    
    //_renderSprite.setTexture(_renderTextura.getTexture());
    // RENDERIZADO FINAL (la ventana dibuja el sprite del lienzo, que contiene el renderizado de lo demas)
    target->draw(_renderSprite);

}
