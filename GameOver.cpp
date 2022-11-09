#include "stdafx.h"
#include "GameOver.h"

void GameOver::iniciarVariables()
{
}

void GameOver::iniciarKeybinds()
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



void GameOver::iniciarFuentes()
{
    if (!_fuenteGameOver.loadFromFile("recursos/fuentes/kenpixel_square.ttf")) {
        std::cout << "ERROR::GAMEOVER::NO SE PUDO CARGAR FUENTE: 'recursos/fuentes/Dosis.ttf'" << std::endl;
    }
    if (!_fuenteBotonGameOver.loadFromFile("recursos/fuentes/Dosis.ttf")) {
        std::cout << "ERROR::GAMEOVER::NO SE PUDO CARGAR FUENTE: 'recursos/fuentes/Dosis.ttf'" << std::endl;
    }
}

void GameOver::iniciarGUI()
{
    const sf::VideoMode& modo_video = _datosEstado->opcionesGraficas->_resolucion;

    _fondoGameOver.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));

    _fondoGameOver.setFillColor(sf::Color::Black);

    //float posX = _ventana->getSize().x / 2.f - 100;
    sf::Color colorInactivoVolver = sf::Color(36, 231, 17, 120);
    sf::Color colorInactivo = sf::Color(208, 208, 208, 155);
    sf::Color colorActivo = sf::Color(189, 236, 182, 155);
    sf::Color colorHover = sf::Color(208, 208, 208, 200);
    sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 250);
    sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
    sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);
    
    _boton["CONTINUAR"] = new gui::Boton(gui::p2pX(50.f, modo_video) - gui::p2pX(5.2f, modo_video), gui::p2pY(90.f, modo_video), gui::p2pX(10.4f, modo_video), gui::p2pY(4.5f, modo_video), "CONTINUAR", gui::calcTamCaracter(modo_video), _fuenteBotonGameOver, sf::Color(0, 0, 0, 0), sf::Color(208, 208, 208, 200), sf::Color(208, 208, 208, 200), sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255));

    // Texto Cargar
    _textoGameOver.setFont(_fuenteGameOver);
    _textoGameOver.setPosition(sf::Vector2f(gui::p2pX(50.f, modo_video) - _textoGameOver.getGlobalBounds().width / 2.f, gui::p2pY(45.f, modo_video) - _textoGameOver.getGlobalBounds().height / 2.f));
    _textoGameOver.setCharacterSize(gui::calcTamCaracter(modo_video, 50));
    _textoGameOver.setFillColor(sf::Color(255, 255, 255, 200));
    _textoGameOver.setString("GAME OVER");
    _textoGameOver.setLetterSpacing(3);
}

void GameOver::resetGUI()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
    _boton.clear();

    this->iniciarGUI();
}

void GameOver::actualizarInput(const float& DT) {}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
GameOver::GameOver(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    iniciarVariables();
    iniciarFuentes();
    iniciarKeybinds();
    iniciarGUI();
    resetGUI();
}


GameOver::~GameOver()
{
    auto botones = _boton.begin(); // delete Botones
    for (botones = _boton.begin(); botones != _boton.end(); ++botones) {
        delete botones->second;
    }
}


void GameOver::actualizarGUI(const float& DT)
{
    // BOTONES --------------------------------------
    for (auto& botones : _boton) {
        botones.second->actualizar(_posMouseVentana);
    }


    if (_boton["CONTINUAR"]->getClick() && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }



}

void GameOver::actualizar(const float& DT)
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
void GameOver::renderizarGUI(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}


void GameOver::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    target->draw(_fondoGameOver);

    renderizarGUI(*target);

    target->draw(_textoGameOver);
}