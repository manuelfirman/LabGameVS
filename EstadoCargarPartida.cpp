#include "stdafx.h"
#include "EstadoCargarPartida.h"
/// --------------------- INICIALIZACIONES --------------------------
void EstadoCargarPartida::iniciarVariables()
{
    _modoVideo = sf::VideoMode::getFullscreenModes();

    std::ifstream test_archivos;
    test_archivos.open("config/cargar_slot1.ini");
    if (test_archivos.is_open())
    {
        bool activo;
        test_archivos >> activo;

        if (activo)
            _slot[0] = true;
        else
            _slot[0] = false;
        
    }
    else
    {
        _slot[0] = false;
        std::cout << "ERROR::CARGARPARTIDA::NO SE PUDO ABRIR ARCHIVO DE SLOT 1" << std::endl;
    }
    test_archivos.close();

    test_archivos.open("config/cargar_slot2.ini");
    if (test_archivos.is_open())
    {
        bool activo;
        test_archivos >> activo;

        if (activo)
            _slot[1] = true;
        else
            _slot[1] = false;
        
    }
    else
    {
        _slot[1] = false;
        std::cout << "ERROR::CARGARPARTIDA::NO SE PUDO ABRIR ARCHIVO DE SLOT 2" << std::endl;
    }
    test_archivos.close();

    test_archivos.open("config/cargar_slot3.ini");
    if (test_archivos.is_open())
    {
        bool activo;
        test_archivos >> activo;

        if (activo)
            _slot[2] = true;
        else
            _slot[2] = false;
    }
    else
    {
        _slot[2] = false;
        std::cout << "ERROR::CARGARPARTIDA::NO SE PUDO ABRIR ARCHIVO DE SLOT 3" << std::endl;
    }
    test_archivos.close();


    //_slot[1] = false;
    //_slot[2] = false;
}

void EstadoCargarPartida::iniciarKeybinds()
{
    std::ifstream archivo("config/teclas_menuprincipal.ini");

    if (archivo.is_open()) {
        std::string accion = "";
        std::string tecla = "";

        while (archivo >> accion >> tecla) {
            _keybinds[accion] = _teclasSoportadas->at(tecla);
        }
    }

    archivo.close();
}



void EstadoCargarPartida::iniciarFuentes()
{
    if (!_fuenteCargar.loadFromFile("recursos/fuentes/Dosis.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
}

void EstadoCargarPartida::iniciarGUI()
{
    const sf::VideoMode& modo_video = _datosEstado->opcionesGraficas->_resolucion;

    if (!_texturaFondoCargar.loadFromFile("recursos/img/fondos/dark_background.png"))
        std::cout << "ERROR::ESTADOOPCIONES::NO SE PUDO CARGAR EL FONDO: 'recursos/img/fondos/dark_background.png'" << std::endl;

    _fondoCargar.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));
    _fondoCargar.setTexture(&_texturaFondoCargar);


    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivoVolver = sf::Color(36, 231, 17, 120);
    sf::Color colorInactivo = sf::Color(208, 208, 208, 155);
    sf::Color colorActivo = sf::Color(189, 236, 182, 155);
    sf::Color colorHover = sf::Color(208, 208, 208, 200);
    sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 250);
    sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
    sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);

    _boton["JUEGO_NUEVO"] = new gui::Boton(gui::p2pX(50.f, modo_video) - gui::p2pX(7.5f, modo_video), gui::p2pY(18.f, modo_video), gui::p2pX(15.f, modo_video), gui::p2pY(7.f, modo_video), "INICIAR JUEGO", gui::calcTamCaracter(modo_video), _fuenteCargar, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["SLOT_1"] = new gui::Boton(gui::p2pX(50.f, modo_video) - gui::p2pX(8.5f, modo_video), gui::p2pY(57.f, modo_video), gui::p2pX(17.f, modo_video), gui::p2pY(4.5f, modo_video), "SLOT 1", gui::calcTamCaracter(modo_video), _fuenteCargar, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
    _boton["SLOT_2"] = new gui::Boton(gui::p2pX(50.f, modo_video) - gui::p2pX(8.5f, modo_video), gui::p2pY(69.f, modo_video), gui::p2pX(17.f, modo_video), gui::p2pY(4.5f, modo_video), "SLOT 2", gui::calcTamCaracter(modo_video), _fuenteCargar, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
    _boton["SLOT_3"] = new gui::Boton(gui::p2pX(50.f, modo_video) - gui::p2pX(8.5f, modo_video), gui::p2pY(81.f, modo_video), gui::p2pX(17.f, modo_video), gui::p2pY(4.5f, modo_video), "SLOT 3", gui::calcTamCaracter(modo_video), _fuenteCargar, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["VOLVER"] = new gui::Boton(gui::p2pX(5.5f, modo_video), gui::p2pY(85.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "VOLVER", gui::calcTamCaracter(modo_video), _fuenteCargar, colorInactivoVolver, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);


    // Texto Nuevo Juego
    _textoNuevoJuego.setFont(_fuenteCargar);
    _textoNuevoJuego.setPosition(sf::Vector2f(gui::p2pX(50.f, modo_video) - _textoNuevoJuego.getGlobalBounds().width / 2.f, gui::p2pY(5.f, modo_video)));
    _textoNuevoJuego.setCharacterSize(gui::calcTamCaracter(modo_video, 50));
    _textoNuevoJuego.setFillColor(sf::Color(255, 255, 255, 200));
    _textoNuevoJuego.setString("CREAR JUEGO NUEVO");
    _textoNuevoJuego.setLetterSpacing(2);

    // Texto Cargar
    _textoCargar.setFont(_fuenteCargar);
    _textoCargar.setPosition(sf::Vector2f(gui::p2pX(50.f, modo_video) - _textoCargar.getGlobalBounds().width / 2.f, gui::p2pY(45.f, modo_video)));
    _textoCargar.setCharacterSize(gui::calcTamCaracter(modo_video, 50));
    _textoCargar.setFillColor(sf::Color(255, 255, 255, 200));
    _textoCargar.setString("CARGAR PARTIDA");
    _textoCargar.setLetterSpacing(3);
}

void EstadoCargarPartida::resetGUI()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
    _boton.clear();

    this->iniciarGUI();
}

void EstadoCargarPartida::actualizarInput(const float& DT){}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoCargarPartida::EstadoCargarPartida(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    iniciarVariables();
    iniciarFuentes();
    iniciarKeybinds();
    iniciarGUI();
    resetGUI();
}


EstadoCargarPartida::~EstadoCargarPartida()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
}


void EstadoCargarPartida::actualizarGUI(const float& DT)
{
    // BOTONES --------------------------------------
    for (auto& botones : _boton) {
        botones.second->actualizar(_posMouseVentana);
    }

    if (_boton["JUEGO_NUEVO"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _estado->push(new EstadoJuego(_datosEstado));
    }


    if (_boton["SLOT_1"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        if (_slot[0])
        {
            _datosEstado->audio->stopMusica();
            _estado->push(new EstadoJuego(_datosEstado, "config/cargar_slot1.ini"));
            _resetMusica = true;
        }
        else
        {
            std::cout << "No hay partida guardada en este slot" << std::endl;
        }
    }
    if (_boton["SLOT_2"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        if (_slot[1])
        {
            _datosEstado->audio->stopMusica();
            _estado->push(new EstadoJuego(_datosEstado, "config/cargar_slot2.ini"));
            _resetMusica = true;
        }
        else
        {
            std::cout << "No hay partida guardada en este slot" << std::endl;
        }
   
    }
    if (_boton["SLOT_3"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        if (_slot[2])
        {
            _datosEstado->audio->stopMusica();
            _estado->push(new EstadoJuego(_datosEstado, "config/cargar_slot3.ini"));
            _resetMusica = true;
        }
        else
        {
            std::cout << "No hay partida guardada en este slot" << std::endl;
        }
     
    }

    if (_boton["VOLVER"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }



}

void EstadoCargarPartida::actualizar(const float& DT)
{
    if (_resetMusica)
    {
        _datosEstado->audio->playMusica();
        _resetMusica = false;
    }

    actualizarPpsTeclas(DT);
    actualizarPosicionMouse();
    actualizarInput(DT);
    actualizarGUI(DT);
}

/// --------------------- RENDERIZAR --------------------------
void EstadoCargarPartida::renderizarGUI(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}


void EstadoCargarPartida::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->draw(_fondoCargar);

    renderizarGUI(*target);

    target->draw(_textoCargar);
    target->draw(_textoNuevoJuego);
}