#include "stdafx.h" // precompilado
#include "EstadoJuego.h"
/// --------------------- INICIALIZACIONES --------------------------
void EstadoJuego::iniciarVistaCam()
{

    // TODO: hacer static cast

    _vistaCam.setSize(sf::Vector2f(_datosEstado->opcionesGraficas->_resolucion.width, _datosEstado->opcionesGraficas->_resolucion.height));

    _vistaCam.setCenter(sf::Vector2f(_datosEstado->opcionesGraficas->_resolucion.width / 2.f, _datosEstado->opcionesGraficas->_resolucion.height / 2.f));
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
}

void EstadoJuego::iniciarTexturas()
{
    sf::Texture aux;

    if (!_texturas["PLANTILLA_JUGADOR"].loadFromFile("recursos/img/personaje/1.png")) {
        std::cout << "ERROR: EstadoJuego_iniciarTexturas_CargaTexturaPersonaje" << std::endl;
    }
}

void EstadoJuego::iniciarMenuPausa()
{
    _menuPausa = new MenuPausa(*_ventana, _fuenteJuego);
    _menuPausa->agregarBoton("SALIR", 500.f, "SALIR");
}

void EstadoJuego::iniciarJugadores()
{
    player = new Jugador(0, 0, _texturas["PLANTILLA_JUGADOR"]);
}

void EstadoJuego::iniciarTileMap()
{
    _tileMap = new TileMap(_datosEstado->tamanioCuadro, 15, 20, "recursos/img/mapa/grass/floortileset.png");

    // cargando mapa desde archivo
    _tileMap->cargarDesdeArchivo("text.slmp");
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoJuego::EstadoJuego(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->iniciarVistaCam();
    this->iniciarKeybinds();
    this->iniciarFuentes();
    this->iniciarTexturas();
    this->iniciarMenuPausa();

    this->iniciarJugadores();
    this->iniciarTileMap();
}

EstadoJuego::~EstadoJuego()
{
    delete player;
    delete _menuPausa;
    delete _tileMap;
}

/// --------------------- ACTUALIZACIONES --------------------------

void EstadoJuego::actualizarVistaCam(const float& DT)
{
    // seteando camara con jugador en el centro
    _vistaCam.setCenter(player->getPosicionSprite());
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_IZQUIERDA"))))
        player->mover(-1.f, 0.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_DERECHA"))))
        player->mover(1.f, 0.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_ARRIBA"))))
        player->mover(0.f, -1.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_ABAJO"))))
        player->mover(0.f, 1.f, DT);

   

}

void EstadoJuego::actualizarBotonesPausa()
{
    if(_menuPausa->getClick("SALIR"))
        finEstado();
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

        player->actualizar(DT);
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

    // render tileMap con vistaCam seteada
    target->setView(_vistaCam);
    _tileMap->renderizar(*target);

    player->renderizar(*target);

    if (_pausa) { 
        // renderizar menu pausa con vistaCam por default
        target->setView(_ventana->getDefaultView());
        _menuPausa->renderizar(*target);
    }

}
