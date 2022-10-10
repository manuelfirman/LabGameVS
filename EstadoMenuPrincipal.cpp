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
}

void EstadoMenuPrincipal::iniciarFondo()
{
    if (!_texturaFondoMenu.loadFromFile("recursos/img/fondos/fondo_menu.jpg"))
        std::cout << "ERROR:iniciarFondo_EstadoMenuPrincipal_CargarTexturaMenu" << std::endl;

    _fondoMenu.setSize(sf::Vector2f(static_cast<float>(_ventana->getSize().x), static_cast<float>(_ventana->getSize().y)));
    _fondoMenu.setTexture(&_texturaFondoMenu);
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

void EstadoMenuPrincipal::iniciarBotones()
{
    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivo = sf::Color(70, 70, 70, 50);
    sf::Color colorActivo = sf::Color(250, 250, 250, 0);
    sf::Color colorHover = sf::Color(20, 20, 20, 0);
    sf::Color colorTextoInactivo = sf::Color(30, 30, 30, 220);
    sf::Color colorTextoHover = sf::Color(150, 150, 150, 255);
    sf::Color colorTextoActivo = sf::Color(20, 20, 20, 220);

    _boton["ESTADO_JUEGO"] = new gui::Boton(p2pX(15.6f), p2pY(37.f), p2pX(10.4f), p2pY(4.5f), "NUEVO JUEGO", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_CARGAR"] = new gui::Boton(p2pX(15.6f), p2pY(44.4f), p2pX(10.4f), p2pY(4.5f), "CARGAR PARTIDA", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_OPCIONES"] = new gui::Boton(p2pX(15.6f), p2pY(51.8f), p2pX(10.4f), p2pY(4.5f), "OPCIONES", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_SALIR"] = new gui::Boton(p2pX(15.6f), p2pY(59.25), p2pX(10.4f), p2pY(4.5f), "SALIR", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["ESTADO_EDITOR"] = new gui::Boton(p2pX(15.6f), p2pY(74.f), p2pX(10.4f), p2pY(4.5f), "EDITOR", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoMenuPrincipal::EstadoMenuPrincipal(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->iniciarVariables();
    this->iniciarKeybinds();
    this->iniciarFondo();
    this->iniciarFuentes();
    this->iniciarBotones();

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
        botones.second->actualizar(posMouseVentana);
    }

    if (_boton["ESTADO_JUEGO"]->getClick() && getPpsTeclas())
        _estado->push(new EstadoJuego(_datosEstado)); // pasa 3 punteros

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
