#include "Gui.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                          BOTON
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// CONSTRUCTOR
gui::Boton::Boton(float posX, float posY, float ancho, float alto, std::string texto, int tamanioLetra, sf::Font& fuente, sf::Color colorBotonInactivo, sf::Color colorBotonHover, sf::Color colorBotonActivo, sf::Color colorTexto)
{
    _estado = estado_boton::INACTIVO;
    _texto.setString(texto);
    _texto.setFillColor(colorTexto);
    _texto.setCharacterSize(tamanioLetra);
    _texto.setFont(fuente);
    _boton.setSize(sf::Vector2f(ancho, alto));
    _colorBotonInactivo = colorBotonInactivo;
    _colorBotonHover = colorBotonHover;
    _colorBotonActivo = colorBotonActivo;
    
    _boton.setPosition(posX, posY);
    _texto.setPosition(
        _boton.getPosition().x + (_boton.getGlobalBounds().width / 2.f) - _texto.getGlobalBounds().width / 2.f,
        _boton.getPosition().y + (_boton.getGlobalBounds().height / 2.f) - _texto.getGlobalBounds().height);
}

gui::Boton::~Boton()
{

}

void gui::Boton::setFuente(sf::Font& fuente)
{
    _texto.setFont(fuente);
}

void gui::Boton::setColorBoton(sf::Color colorBoton)
{
    _boton.setFillColor(colorBoton);
}

void gui::Boton::setColorTexto(sf::Color colorTexto)
{
    _texto.setFillColor(colorTexto);
}

void gui::Boton::setPosicion(sf::Vector2f posicion)
{
    _boton.setPosition(posicion);

    _texto.setPosition(
        _boton.getPosition().x + (_boton.getGlobalBounds().width / 2.f) - _texto.getGlobalBounds().width / 2.f,
        _boton.getPosition().y + (_boton.getGlobalBounds().height / 2.f) - _texto.getGlobalBounds().height);
}

bool gui::Boton::getClick()
{
    if (_estado == estado_boton::ACTIVO) {
        return true;
    }

    return false;
}

/// ACTUALIZAR BOTON
void gui::Boton::actualizar(sf::Vector2f posMouse)
{
    _estado = estado_boton::INACTIVO;
    if (_boton.getGlobalBounds().contains(posMouse)) {
        _estado = estado_boton::HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _estado = estado_boton::ACTIVO;
        }
    }

    switch (_estado) {
    case estado_boton::INACTIVO:
        _boton.setFillColor(_colorBotonInactivo);
        break;

    case estado_boton::HOVER:
        _boton.setFillColor(_colorBotonHover);
        break;

    case estado_boton::ACTIVO:
        _boton.setFillColor(_colorBotonActivo);
        break;
    }
}

/// RENDERIZAR BOTON
void gui::Boton::renderizar(sf::RenderTarget& target)
{
    target.draw(_boton);
    target.draw(_texto);
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                          DESPLEGABLE
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

void gui::ListaDesplegable::actualizar(const sf::Vector2f& posMouse)
{
}

void gui::ListaDesplegable::renderizar(sf::RenderTarget& target)
{
}
