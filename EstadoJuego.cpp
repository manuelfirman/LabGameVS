#include "stdafx.h" // precompilado
#include "EstadoJuego.h"
/// --------------------- INICIALIZACIONES --------------------------
void EstadoJuego::iniciarFuentes()
{
    if (!_fuenteJuego.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
 /*   if (!_fuenteBoton.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
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

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoJuego::EstadoJuego(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->iniciarKeybinds();
    this->iniciarFuentes();
    this->iniciarTexturas();
    this->iniciarMenuPausa();

    this->iniciarJugadores();
}

EstadoJuego::~EstadoJuego()
{
    delete player;
    delete _menuPausa;
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

/// --------------------- ACTUALIZACIONES --------------------------
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
    actualizarPosicionMouse();
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa) // actualizar sin pausa
    {
        actualizarInputJugador(DT);

        player->actualizar(DT);
    }
    else // actualizar con pausa
    {
        _menuPausa->actualizar(posMouseVista);
        actualizarBotonesPausa();
    }

}


/// --------------------- RENDERIZAR --------------------------
void EstadoJuego::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    //mapa.renderizar(*target);


    player->renderizar(*target);

    if (_pausa) { // renderizar menu pausa
        _menuPausa->renderizar(*target);
    }

}
