#include "stdafx.h"
#include "EstadoTutorial.h"
void EstadoTutorial::iniciarVariables()
{
    _modoVideo = sf::VideoMode::getFullscreenModes();
    con = 0;
    tutorial1 = "";
    tutorial2 = "";
}

void EstadoTutorial::iniciarKeybinds()
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



void EstadoTutorial::iniciarFuentes()
{
    if (!_fuenteTutorial.loadFromFile("recursos/fuentes/Dosis.ttf")) {
        std::cout << "ERROR:CargarFuente_MenuPrincipal" << std::endl;
    }
}

void EstadoTutorial::iniciarGUI()
{
    const sf::VideoMode& modo_video = _datosEstado->opcionesGraficas->_resolucion;

    if (!_texturaFondoTutorial.loadFromFile("recursos/img/fondos/dark_background.png"))
        std::cout << "ERROR::ESTADOOPCIONES::NO SE PUDO CARGAR EL FONDO: 'recursos/img/fondos/dark_background.png'" << std::endl;

    _fondoTutorial.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));
    _fondoTutorial.setTexture(&_texturaFondoTutorial);


    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivoVolver = sf::Color(36, 231, 17, 120);
    sf::Color colorInactivo = sf::Color(208, 208, 208, 155);
    sf::Color colorActivo = sf::Color(189, 236, 182, 155);
    sf::Color colorHover = sf::Color(208, 208, 208, 200);
    sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 250);
    sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
    sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);

    

    _boton["SIGUIENTE"] = new gui::Boton(gui::p2pX(94.5f, modo_video) - gui::p2pX(10.4f, modo_video), gui::p2pY(85.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "SIGUIENTE", gui::calcTamCaracter(modo_video), _fuenteTutorial, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
    _boton["ATRAS"] = new gui::Boton(gui::p2pX(74.5f, modo_video) - gui::p2pX(10.4f, modo_video), gui::p2pY(85.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "ATRAS", gui::calcTamCaracter(modo_video), _fuenteTutorial, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
    _boton["VOLVER"] = new gui::Boton(gui::p2pX(5.5f, modo_video), gui::p2pY(85.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "VOLVER", gui::calcTamCaracter(modo_video), _fuenteTutorial, colorInactivoVolver, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);


    // Titulo
    _tituloTutorial.setFont(_fuenteTutorial);
    _tituloTutorial.setPosition(sf::Vector2f(gui::p2pX(50.f, modo_video) - _tituloTutorial.getGlobalBounds().width / 2.f, gui::p2pY(3.f, modo_video)));
    _tituloTutorial.setCharacterSize(gui::calcTamCaracter(modo_video, 30));
    _tituloTutorial.setFillColor(sf::Color(255, 255, 255, 200));
    _tituloTutorial.setString("TUTORIAL");
    _tituloTutorial.setLetterSpacing(4);

    // Texto tutorial 1
    tutorial1 = "BIENVENIDO AL TUTORIAL DE LARASTER";
    _textoTutorial1.setFont(_fuenteTutorial);
    _textoTutorial1.setPosition(sf::Vector2f(gui::p2pX(50.f, modo_video) - _textoTutorial1.getGlobalBounds().width / 2.f, gui::p2pY(15.f, modo_video)));
    _textoTutorial1.setCharacterSize(gui::calcTamCaracter(modo_video, 100));
    _textoTutorial1.setFillColor(sf::Color(255, 255, 255, 200));
    _textoTutorial1.setString(tutorial1);
    _textoTutorial1.setLetterSpacing(3);
    
    // Texto tutorial 2
    tutorial2 = "MOVIMIENTOS:\nW -> ARRIBA\nS -> ABAJO\nA -> IZQUIERDA\nD -> DERECHA";
    _textoTutorial2.setFont(_fuenteTutorial);
    _textoTutorial2.setPosition(sf::Vector2f(gui::p2pX(40.f, modo_video) - _textoTutorial1.getGlobalBounds().width / 2.f, gui::p2pY(45.f, modo_video)));
    _textoTutorial2.setCharacterSize(gui::calcTamCaracter(modo_video, 80));
    _textoTutorial2.setFillColor(sf::Color(255, 255, 255, 200));
    _textoTutorial2.setString(tutorial2);
    _textoTutorial2.setLetterSpacing(1);


}

void EstadoTutorial::resetGUI()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
    _boton.clear();

    this->iniciarGUI();
}

void EstadoTutorial::actualizarInput(const float& DT) {}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoTutorial::EstadoTutorial(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    iniciarVariables();
    iniciarFuentes();
    iniciarKeybinds();
    iniciarGUI();
    resetGUI();
}


EstadoTutorial::~EstadoTutorial()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
}


void EstadoTutorial::actualizarGUI(const float& DT)
{
    // BOTONES --------------------------------------
    for (auto& botones : _boton) {
        botones.second->actualizar(_posMouseVentana);
    }


    if (_boton["SIGUIENTE"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        if(con < 2) con++;
    }


    if (_boton["ATRAS"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        if (con > 0) con--;
    }


    if (_boton["VOLVER"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }


    if (con == 0)
    {
        _textoTutorial2.setFillColor(sf::Color(255, 255, 255, 200));
        tutorial2 = "MOVIMIENTOS:\n\n\nW->ARRIBA\t\tS->ABAJO\n\nA->IZQUIERDA\t\tD->DERECHA";
        _textoTutorial2.setString(tutorial2);
    }
    else if (con == 1)
    {
        _textoTutorial2.setFillColor(sf::Color(255, 255, 255, 200));
        tutorial2 = "ATAQUES:\n\n\nCLICK IZQUIERDO -> ATAQUE BASICO\n\nQ -> SKILL";
        _textoTutorial2.setString(tutorial2);
    }
    else if (con == 2)
    {
        _textoTutorial2.setFillColor(sf::Color(36, 231, 17, 200));
        tutorial2 = "Utiliza las teclas de movimiento para moverte por el mapa.\nNo dejes que los enemigos te alcancen, mantenete en movimiento.\nAtaca a los enemigos pulsando el click izquierdo mientras les apuntas.\nObtene experiencia matando enemigos y subi de nivel para mejorar tus estadisticas\n\nMANTENETE CON VIDA";
        _textoTutorial2.setString(tutorial2);
    }

}

void EstadoTutorial::actualizar(const float& DT)
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
void EstadoTutorial::renderizarGUI(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}


void EstadoTutorial::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->draw(_fondoTutorial);

    renderizarGUI(*target);

    target->draw(_tituloTutorial);
    target->draw(_textoTutorial1);
    target->draw(_textoTutorial2);
}