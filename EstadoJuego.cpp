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
    _tileMap = new TileMap(_datosEstado->tamanioCuadro, 10, 10, "recursos/img/mapa/grass/floortileset.png");

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
    _vistaCam.setCenter(std::floor(player->getPosicionSprite().x), std::floor(player->getPosicionSprite().y)); // floor para estabilizar el float en pixels 
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

void EstadoJuego::actualizarTileMap(const float& DT)
{
    _tileMap->actualizar();
    _tileMap->checkColision(player, DT);
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

    _renderTextura.clear(); // limpia el frame anterior

    // TODO SE RENDERIZA A TRAVES DEL LIENZO
    _renderTextura.setView(_vistaCam); // con la vista seteada
    _tileMap->renderizar(_renderTextura, player);

    player->renderizar(_renderTextura);

    if (_pausa) { 
        // renderizar MENU PAUSA con vistaCam por default
        _renderTextura.setView(_renderTextura.getDefaultView());
        _menuPausa->renderizar(_renderTextura);
    }

    _renderTextura.display(); // actualiza el contenido
    
    // RENDERIZADO FINAL (la ventana dibuja el sprite del lienzo, que contiene el renderizado de lo demas)
    _renderSprite.setTexture(_renderTextura.getTexture());
    target->draw(_renderSprite);

}
