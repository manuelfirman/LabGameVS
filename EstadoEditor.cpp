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

}

EstadoEditor::~EstadoEditor()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }

    delete _menuPausa;
}


/// --------------------- ACTUALIZACIONES --------------------------
void EstadoEditor::actualizarBotonesMenuPausa()
{
    if (_menuPausa->getClick("SALIR"))
        finEstado();
}

void EstadoEditor::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE"))) && getPpsTeclas())
    {
        if (!_pausa) pausarEstado();
        else reanudarEstado();
        //(_pausa) ? pausarEstado() : reanudarEstado();
    }
}

void EstadoEditor::actualizarBotones()
{
    for (auto& botones : _boton) {
        botones.second->actualizar(posMouseVista);
    }

}

void EstadoEditor::actualizar(const float& DT)
{
    actualizarPosicionMouse();
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa)
    {
        actualizarBotones();

    }
    else
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


void EstadoEditor::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    renderBotones(*target);

    _mapa.renderizar(*target);

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
