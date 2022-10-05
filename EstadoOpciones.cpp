#include "EstadoOpciones.h"

/// --------------------- INICIALIZACIONES --------------------------
void EstadoOpciones::iniciarVariables()
{

}

void EstadoOpciones::iniciarKeybinds()
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

void EstadoOpciones::iniciarFondo()
{
    if (!_texturaFondoOpciones.loadFromFile("recursos/img/fondos/fondo_menu.jpg"))
        std::cout << "ERROR:iniciarFondo_EstadoMenuPrincipal_CargarTexturaMenu" << std::endl;

    _fondoOpciones.setSize(sf::Vector2f(static_cast<float>(_ventana->getSize().x), static_cast<float>(_ventana->getSize().y)));
    _fondoOpciones.setTexture(&_texturaFondoOpciones);
}

void EstadoOpciones::iniciarFuentes()
{
    if (!_fuenteOpciones.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
    if (!_fuenteBoton.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal_Botones" << std::endl;
    }
}

void EstadoOpciones::iniciarBotones()
{
    float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivo = sf::Color(48, 132, 70, 155);
    sf::Color colorActivo = sf::Color(189, 236, 182, 155);
    sf::Color colorHover = sf::Color(208, 208, 208, 155);
    sf::Color colorTexto = sf::Color(sf::Color::Black);

  

    _boton["ESTADO_SALIR"] = new gui::Boton(posX, 640, 200.f, 50.f, "SALIR", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTexto);

    std::string li[] = {"123", "456", "321", "654", "555"};
    _lista = new gui::ListaDesplegable(100.f, 100.f, 200.f, 50.f, _fuenteBoton, li, 5);


}


/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoOpciones::EstadoOpciones(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado)
	: EstadoBase(ventana, teclasSoportadas, estado)
{
    iniciarVariables();
    iniciarFondo();
    iniciarFuentes();
    iniciarKeybinds();
    iniciarBotones();
}

EstadoOpciones::~EstadoOpciones()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }

    delete _lista;
}



/// --------------------- ACTUALIZACIONES --------------------------
void EstadoOpciones::actualizarInput(const float& DT)
{


}

void EstadoOpciones::actualizarBotones()
{
    for (auto& botones : _boton) {
        botones.second->actualizar(posMouseVista);
    }


    if (_boton["ESTADO_SALIR"]->getClick())
        finEstado();

}

void EstadoOpciones::actualizar(const float& DT)
{
    actualizarPosicionMouse();
    actualizarInput(DT);
    actualizarBotones();

    _lista->actualizar(posMouseVista, DT);
}

/// --------------------- RENDERIZAR --------------------------
void EstadoOpciones::renderBotones(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }

}


void EstadoOpciones::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->draw(_fondoOpciones);

    renderBotones(*target);

    _lista->renderizar(*target);
}