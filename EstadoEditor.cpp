#include "EstadoEditor.h"
#include <sstream>
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
    if (!_fuenteBoton.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR:CargarFuente_EditorEstado_Botones" << std::endl;
    }
}

void EstadoEditor::iniciarBotones()
{


}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoEditor::EstadoEditor(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado) : EstadoBase(ventana, teclasSoportadas, estado)
{
    this->iniciarVariables();
    this->iniciarKeybinds();
    this->iniciarFondo();
    this->iniciarFuentes();
    this->iniciarBotones();

}

EstadoEditor::~EstadoEditor()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }
}


/// --------------------- ACTUALIZACIONES --------------------------
void EstadoEditor::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE"))))
        finEstado();

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
    actualizarInput(DT);
    actualizarBotones();

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

    /// VER POSICION MOUSE AL LADO DE LA FLECHA (QUITAR DESPUES)
//    sf::Text textoMouse;
//    textoMouse.setPosition(posMouseVista.x, posMouseVista.y - 50);
//    textoMouse.setFont(_fuenteBoton);
//    textoMouse.setCharacterSize(12);
//    std::stringstream ss;
//    ss << posMouseVista.x << " " << posMouseVista.y;
//    textoMouse.setString(ss.str());
//
//    target->draw(textoMouse);
}
