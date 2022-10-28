#include "stdafx.h" // precompilado
#include "EstadoMenuPrincipal.h"

/// --------------------- INICIALIZACIONES --------------------------
void EstadoMenuPrincipal::iniciarVariables()
{

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
    if (!_fuenteMenu.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
    if (!_fuenteBoton.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal_Botones" << std::endl;
    }
}

void EstadoMenuPrincipal::iniciarGUI()
{
    const sf::VideoMode& modo_video = _datosEstado->opcionesGraficas->_resolucion;

    if (!_texturaFondoMenu.loadFromFile("recursos/img/fondos/dark_background.png"))
        std::cout << "ERROR:iniciarFondo_EstadoMenuPrincipal_CargarTexturaMenu" << std::endl;

    _fondoMenu.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));
    _fondoMenu.setTexture(&_texturaFondoMenu);

    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivo = sf::Color(250, 250, 250, 0);
    sf::Color colorActivo = sf::Color(20, 20, 20, 0);
    sf::Color colorHover = sf::Color(70, 70, 70, 50);
    sf::Color colorTextoInactivo = sf::Color(150, 150, 150, 255);
    sf::Color colorTextoHover = sf::Color(180, 180, 180, 255);
    sf::Color colorTextoActivo = sf::Color(20, 20, 20, 220);

    _boton["ESTADO_JUEGO"] = new gui::Boton(gui::p2pX(15.6f, modo_video), gui::p2pY(37.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "NUEVO JUEGO", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_CARGAR"] = new gui::Boton(gui::p2pX(15.6f, modo_video), gui::p2pY(44.4f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "CARGAR PARTIDA", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_OPCIONES"] = new gui::Boton(gui::p2pX(15.6f, modo_video), gui::p2pY(51.8f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "OPCIONES", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_SALIR"] = new gui::Boton(gui::p2pX(15.6f, modo_video), gui::p2pY(59.2f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "SALIR", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_EDITOR"] = new gui::Boton(gui::p2pX(15.6f, modo_video), gui::p2pY(74.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "EDITOR", gui::calcTamCaracter(modo_video), _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
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

}

EstadoMenuPrincipal::~EstadoMenuPrincipal()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
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

    if (_boton["ESTADO_JUEGO"]->getClick() && getPpsTeclas())
        _estado->push(new EstadoJuego(_datosEstado));

    if (_boton["ESTADO_OPCIONES"]->getClick() && getPpsTeclas())
        _estado->push(new EstadoOpciones(_datosEstado));

    if (_boton["ESTADO_EDITOR"]->getClick() && getPpsTeclas())
        _estado->push(new EstadoEditor(_datosEstado));

    if (_boton["ESTADO_SALIR"]->getClick() && getPpsTeclas())
        finEstado();

}

void EstadoMenuPrincipal::actualizar(const float& DT)
{
    actualizarPosicionMouse();
    actualizarPpsTeclas(DT);
    actualizarInput(DT);
    actualizarBotones();

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

    renderBotones(*target);
}
