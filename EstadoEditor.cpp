#include "stdafx.h" // precompilado
#include "EstadoEditor.h"

/// --------------------- INICIALIZACIONES --------------------------
void EstadoEditor::iniciarVariables()
{

}

void EstadoEditor::iniciarKeybinds()
{
    std::ifstream archivo("config/teclas_editorestado.ini");

    if (archivo.is_open()) {
        std::string accion = "";
        std::string tecla = "";

        while (archivo >> accion >> tecla) {
            _keybinds[accion] = _teclasSoportadas->at(tecla);
        }
    }
}

void EstadoEditor::iniciarFondo()
{


}

void EstadoEditor::iniciarFuentes()
{
    if (!_fuente.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_EditorEstado_Botones" << std::endl;
    }
}

void EstadoEditor::iniciarMenuPausa()
{
    _menuPausa = new MenuPausa(*_ventana, _fuente);

    _menuPausa->agregarBoton("SALIR", 800.f, "SALIR");
}

void EstadoEditor::iniciarBotones()
{

}

void EstadoEditor::iniciarGUI()
{
    rectSelector.setSize(sf::Vector2f(_datosEstado->tamanioCuadro, _datosEstado->tamanioCuadro));
    rectSelector.setFillColor(sf::Color::Transparent);
    rectSelector.setOutlineThickness(1.f);
    rectSelector.setOutlineColor(sf::Color::Green);
}

void EstadoEditor::iniciarTileMap()
{
    _tileMap = new TileMap(_datosEstado->tamanioCuadro, 10, 10);
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoEditor::EstadoEditor(DatosEstado* datos_estado) 
    : EstadoBase(datos_estado)
{
    this->iniciarVariables();
    this->iniciarKeybinds();
    this->iniciarFondo();
    this->iniciarFuentes();
    this->iniciarMenuPausa();
    this->iniciarBotones();
    this->iniciarGUI();
    this->iniciarTileMap();

}

EstadoEditor::~EstadoEditor()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }

    delete _menuPausa;
    delete _tileMap;
}


/// --------------------- ACTUALIZACIONES --------------------------
void EstadoEditor::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE"))) && getPpsTeclas())
    {
        if (!_pausa) pausarEstado();
        else reanudarEstado();
        //(_pausa) ? pausarEstado() : reanudarEstado();
    }
}

void EstadoEditor::actualizarInputEditor(const float& DT)
{
    // agregando un tile cuando clickeo
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getPpsTeclas())
    {
        _tileMap->agregarTile(posMouseCuadro.x, posMouseCuadro.y, 0);
    }
}

void EstadoEditor::actualizarBotones()
{
    for (auto& botones : _boton) {
        botones.second->actualizar(posMouseVista);
    }

}

void EstadoEditor::actualizarGUI()
{
    rectSelector.setPosition(posMouseCuadro.x * _datosEstado->tamanioCuadro, posMouseCuadro.y * _datosEstado->tamanioCuadro);
}

void EstadoEditor::actualizarBotonesMenuPausa()
{
    if (_menuPausa->getClick("SALIR"))
        finEstado();
}

// ACTUALIZAR ESTADO EDITOR
void EstadoEditor::actualizar(const float& DT)
{
    actualizarPosicionMouse();
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa) // No pausa
    {
        actualizarGUI();
        actualizarBotones();
        actualizarInputEditor(DT);
    }
    else // pausa
    {
        _menuPausa->actualizar(posMouseVista);
        actualizarBotonesMenuPausa();
    }

}


/// --------------------- RENDERIZAR --------------------------
void EstadoEditor::renderBotones(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}

void EstadoEditor::renderizarGUI(sf::RenderTarget& target)
{
    target.draw(rectSelector);
}

void EstadoEditor::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    renderBotones(*target);
    renderizarGUI(*target);

    _tileMap->renderizar(*target);

    if (_pausa)
    {
        _menuPausa->renderizar(*target);
    }

    /// VER POSICION MOUSE AL LADO DE LA FLECHA (QUITAR DESPUES)
    sf::Text textoMouse;
    textoMouse.setPosition(posMouseVista.x, posMouseVista.y - 50);
    textoMouse.setFont(_fuente);
    textoMouse.setCharacterSize(12);
    std::stringstream ss;
    ss << posMouseVista.x << " " << posMouseVista.y;
    textoMouse.setString(ss.str());

    target->draw(textoMouse);
}
