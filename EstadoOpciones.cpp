#include "stdafx.h" // precompilado
#include "EstadoOpciones.h"

/// --------------------- INICIALIZACIONES --------------------------
void EstadoOpciones::iniciarVariables()
{
    _modoVideo = sf::VideoMode::getFullscreenModes();
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

void EstadoOpciones::iniciarGUI()
{
    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivo = sf::Color(48, 132, 70, 155);
    sf::Color colorActivo = sf::Color(189, 236, 182, 155);
    sf::Color colorHover = sf::Color(208, 208, 208, 155);
    sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 200);
    sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
    sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);
  

    _boton["VOLVER"] = new gui::Boton(100.f, 900.f, 200.f, 50.f, "VOLVER", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["APLICAR"] = new gui::Boton(400.f, 900.f, 200.f, 50.f, "APLICAR", 20, _fuenteBoton, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);


    std::vector<std::string> modos_str;
    for (auto &modos : _modoVideo)
    {
        modos_str.push_back(std::to_string(modos.width) + 'x' + std::to_string(modos.height));
    }

    _listasDesplegables["RESOLUCION"] = new gui::ListaDesplegable(800.f, 400.f, 200.f, 50.f, _fuenteBoton, modos_str.data(), int(modos_str.size()));


}

void EstadoOpciones::iniciarTexto()
{
    _textoOpciones.setFont(_fuenteOpciones);
    _textoOpciones.setPosition(sf::Vector2f(100.f, 100.f));
    _textoOpciones.setCharacterSize(30);
    _textoOpciones.setFillColor(sf::Color(255,255,255,200));
    _textoOpciones.setString("Resolucion \nFullscreen \nVsync \nAntialiasing");
}


/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoOpciones::EstadoOpciones(sf::RenderWindow* ventana, OpcionesGraficas& opcionesGraficas, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado)
	: EstadoBase(ventana, teclasSoportadas, estado), _opcionesGraficas(opcionesGraficas)
{
    iniciarVariables();
    iniciarFondo();
    iniciarFuentes();
    iniciarKeybinds();
    iniciarGUI();
    iniciarTexto();
}

EstadoOpciones::~EstadoOpciones()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }

    auto listas = _listasDesplegables.begin(); // delete Lista
    for (listas = _listasDesplegables.begin(); listas != _listasDesplegables.end(); ++listas) {
        delete listas->second;
    }


}



/// --------------------- ACTUALIZACIONES --------------------------
void EstadoOpciones::actualizarInput(const float& DT)
{


}

void EstadoOpciones::actualizarGUI(const float& DT)
{
    // BOTONES --------------------------------------
    for (auto& botones : _boton) { 
        botones.second->actualizar(posMouseVista);
    }

    if (_boton["VOLVER"]->getClick())
        finEstado();
    
    if (_boton["APLICAR"]->getClick())
    {
    
        _opcionesGraficas._resolucion = _modoVideo[_listasDesplegables["RESOLUCION"]->getIDelementoAtivo()];

        _ventana->create(_opcionesGraficas._resolucion, _opcionesGraficas._titulo, sf::Style::Default);
    }
        


    // LISTAS DESPLEGABLES --------------------------
    for (auto& listas : _listasDesplegables)
    {
        listas.second->actualizar(posMouseVista, DT);
    }
}

void EstadoOpciones::actualizar(const float& DT)
{
    actualizarPosicionMouse();
    actualizarInput(DT);
    actualizarGUI(DT);
}

/// --------------------- RENDERIZAR --------------------------
void EstadoOpciones::renderizarGUI(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }

    for (auto& listas : _listasDesplegables) {
        listas.second->renderizar(target);
    }

}


void EstadoOpciones::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->draw(_fondoOpciones);

    renderizarGUI(*target);

    target->draw(_textoOpciones);
}