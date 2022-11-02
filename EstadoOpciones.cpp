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

    archivo.close();
}

void EstadoOpciones::iniciarFuentes()
{
    if (!_fuenteOpciones.loadFromFile("recursos/fuentes/Dosis.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
}

void EstadoOpciones::iniciarGUI()
{
    const sf::VideoMode& modo_video = _datosEstado->opcionesGraficas->_resolucion;

    if (!_texturaFondoOpciones.loadFromFile("recursos/img/fondos/dark_background.png"))
        std::cout << "ERROR::ESTADOOPCIONES::NO SE PUDO CARGAR EL FONDO: 'recursos/img/fondos/dark_background.png'" << std::endl;

    _fondoOpciones.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));
    _fondoOpciones.setTexture(&_texturaFondoOpciones);


    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivo = sf::Color(48, 132, 70, 155);
    sf::Color colorActivo = sf::Color(189, 236, 182, 155);
    sf::Color colorHover = sf::Color(208, 208, 208, 155);
    sf::Color colorTextoInactivo = sf::Color(255, 255, 255, 200);
    sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
    sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);
  

    _boton["VOLVER"] = new gui::Boton(gui::p2pX(5.2f, modo_video), gui::p2pY(83.3f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "VOLVER", gui::calcTamCaracter(modo_video), _fuenteOpciones, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);

    _boton["APLICAR"] = new gui::Boton(gui::p2pX(20.8f, modo_video), gui::p2pY(83.3f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "APLICAR", gui::calcTamCaracter(modo_video), _fuenteOpciones, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);


    std::vector<std::string> modos_str;
    for (auto &modos : _modoVideo)
    {
        modos_str.push_back(std::to_string(modos.width) + 'x' + std::to_string(modos.height));
    }

    _listasDesplegables["RESOLUCION"] = new gui::ListaDesplegable(gui::p2pX(41.6f, modo_video), gui::p2pY(37.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), _fuenteOpciones, gui::calcTamCaracter(modo_video), modos_str.data(), int(modos_str.size()));

    // Texto
    _textoOpciones.setFont(_fuenteOpciones);
    _textoOpciones.setPosition(sf::Vector2f(gui::p2pX(5.2f, modo_video), gui::p2pY(9.2f, modo_video)));
    _textoOpciones.setCharacterSize(gui::calcTamCaracter(modo_video, 50));
    _textoOpciones.setFillColor(sf::Color(255, 255, 255, 200));
    _textoOpciones.setString("AJUSTES DE PANTALLA");

}

void EstadoOpciones::resetGUI()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
    _boton.clear();

    auto listas = _listasDesplegables.begin(); // delete Lista
    for (listas = _listasDesplegables.begin(); listas != _listasDesplegables.end(); ++listas) {
        delete listas->second;
    }
    _listasDesplegables.clear();

    this->iniciarGUI();
}


/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoOpciones::EstadoOpciones(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    iniciarVariables();
    iniciarFuentes();
    iniciarKeybinds();
    iniciarGUI();
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
        botones.second->actualizar(_posMouseVentana);
    }
    
    if (_boton["APLICAR"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");

        _datosEstado->opcionesGraficas->_resolucion = _modoVideo[_listasDesplegables["RESOLUCION"]->getIDelementoAtivo()];

        _ventana->create(_datosEstado->opcionesGraficas->_resolucion, _datosEstado->opcionesGraficas->_titulo, sf::Style::Default);

        this->resetGUI();
    }

    if (_boton["VOLVER"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }


    // LISTAS DESPLEGABLES --------------------------
    for (auto& listas : _listasDesplegables)
    {
        listas.second->actualizar(_posMouseVentana, DT);
    }
}

void EstadoOpciones::actualizar(const float& DT)
{
    actualizarPpsTeclas(DT);
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