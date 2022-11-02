#include "stdafx.h" // precompilado
#include "EstadoMenuPrincipal.h"

/// --------------------- INICIALIZACIONES --------------------------
void EstadoMenuPrincipal::iniciarVariables()
{
    _resetMenu = false;
}

void EstadoMenuPrincipal::iniciarKeybinds()
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


void EstadoMenuPrincipal::iniciarFuentes()
{
    if (!_fuenteMenu.loadFromFile("recursos/fuentes/kenpixel_square.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
    if (!_fuenteBoton.loadFromFile("recursos/fuentes/kenpixel_square.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal_Botones" << std::endl;
    }
}

void EstadoMenuPrincipal::iniciarGUI()
{
    const sf::VideoMode& modo_video = _datosEstado->opcionesGraficas->_resolucion;

    // FONDO
    if(!_texturas["FONDO_MENU"].loadFromFile("recursos/img/fondos/dark_background.png"))
        std::cout << "ERROR::MENUPRINCIPAL::NO SE PUDO CARGAR EL FONDO: 'recursos/img/fondos/dark_background.png'" << std::endl;
    _fondoMenu.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));
    _fondoMenu.setTexture(&_texturas["FONDO_MENU"]);
    
    // TEXTO
    _tituloMenu.setFont(_fuenteMenu);
    _tituloMenu.setCharacterSize(gui::calcTamCaracter(modo_video, 20));
    _tituloMenu.setString("LARASTER");
    _tituloMenu.setPosition(gui::p2pX(10.f, modo_video), gui::p2pX(5.f, modo_video));
    _tituloMenu.setLetterSpacing(2);

    _subtituloMenu.setFont(_fuenteMenu);
    _subtituloMenu.setCharacterSize(gui::calcTamCaracter(modo_video, 55));
    _subtituloMenu.setString("RPG");
    _subtituloMenu.setPosition(gui::p2pX(53.f, modo_video), gui::p2pY(26.f, modo_video));
    _subtituloMenu.setLetterSpacing(2);

    // BOTONES
    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivo = sf::Color(250, 250, 250, 0);
    sf::Color colorActivo = sf::Color(20, 20, 20, 0);
    sf::Color colorHover = sf::Color(70, 70, 70, 50);
    sf::Color colorTextoInactivo = sf::Color(150, 150, 150, 255);
    sf::Color colorTextoHover = sf::Color(134, 115, 161, 200);
    sf::Color colorTextoActivo = sf::Color(20, 20, 20, 220);

    _boton["ESTADO_JUGAR"] = new gui::Boton(gui::p2pX(25.f, modo_video), gui::p2pY(52.f, modo_video), gui::p2pX(15.f, modo_video), gui::p2pY(4.5f, modo_video), "JUGAR", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_OPCIONES"] = new gui::Boton(gui::p2pX(25.f, modo_video), gui::p2pY(59.f, modo_video), gui::p2pX(15.f, modo_video), gui::p2pY(4.5f, modo_video), "OPCIONES", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_SALIR"] = new gui::Boton(gui::p2pX(25.f, modo_video), gui::p2pY(66.f, modo_video), gui::p2pX(15.f, modo_video), gui::p2pY(4.5f, modo_video), "SALIR", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_EDITOR"] = new gui::Boton(gui::p2pX(25.f, modo_video), gui::p2pY(80.f, modo_video), gui::p2pX(15.f, modo_video), gui::p2pY(4.5f, modo_video), "EDITOR", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_TUTORIAL"] = new gui::Boton(gui::p2pX(80.f, modo_video), gui::p2pY(65.f, modo_video), gui::p2pX(15.f, modo_video), gui::p2pY(4.5f, modo_video), "VER TUTORIAL", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

}

void EstadoMenuPrincipal::resetGUI()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }
    _boton.clear();
    this->iniciarGUI();
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoMenuPrincipal::EstadoMenuPrincipal(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->iniciarVariables();
    this->iniciarKeybinds();
    this->iniciarFuentes();
    this->iniciarGUI();
    this->resetGUI();

    _datosEstado->audio->playMusica();
}

EstadoMenuPrincipal::~EstadoMenuPrincipal()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }
}


void EstadoMenuPrincipal::actualizarTitulo()
{
    if (_tituloMenu.getGlobalBounds().contains(static_cast<float>(_posMouseVentana.x), static_cast<float>(_posMouseVentana.y)))
    {
        _tituloMenu.setFillColor(sf::Color(134, 115, 161, 200));
        _subtituloMenu.setFillColor(sf::Color(96, 111, 140, 200));
    }
    else
    {
        _tituloMenu.setFillColor(sf::Color(255, 255, 255, 255));
        _subtituloMenu.setFillColor(sf::Color(255, 255, 255, 255));
    }
}

/// --------------------- ACTUALIZACIONES --------------------------
void EstadoMenuPrincipal::actualizarInput(const float& DT)
{


}

void EstadoMenuPrincipal::actualizarBotones()
{
    for (auto& botones : _boton) {
        botones.second->actualizar(_posMouseVentana);
    }


    if (_boton["ESTADO_JUGAR"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _estado->push(new EstadoCargarPartida(_datosEstado));
    }

    if (_boton["ESTADO_OPCIONES"]->getClick() && getPpsTeclas())
    {
        _resetMenu = true;
        _datosEstado->audio->playSonido("BOTON_CLICK"); 
        _estado->push(new EstadoOpciones(_datosEstado));
    }

    if (_boton["ESTADO_EDITOR"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _estado->push(new EstadoEditor(_datosEstado));
    }

    if (_boton["ESTADO_TUTORIAL"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _estado->push(new EstadoTutorial(_datosEstado));
    }

    if (_boton["ESTADO_SALIR"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }

}

void EstadoMenuPrincipal::actualizar(const float& DT)
{
    if (_resetMenu)
    {
        resetGUI();
        _resetMenu = false;
    }

    actualizarPosicionMouse();
    actualizarPpsTeclas(DT);
    actualizarInput(DT);
    actualizarBotones();
    actualizarTitulo();
}


/// --------------------- RENDERIZAR --------------------------
void EstadoMenuPrincipal::renderBotones(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}


void EstadoMenuPrincipal::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->draw(_fondoMenu);
    target->draw(_tituloMenu);
    target->draw(_subtituloMenu);

    renderBotones(*target);
}
