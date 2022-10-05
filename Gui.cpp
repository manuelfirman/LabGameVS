#include "Gui.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                          BOTON
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// --------------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------------------------
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

/// --------------------------------- SETTERS ----------------------------------------

void gui::Boton::setFuente(sf::Font& fuente)
{
    _texto.setFont(fuente);
}

void gui::Boton::setTexto(const std::string texto)
{
    _texto.setString(texto);
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


/// --------------------------------- METODOS ----------------------------------------
bool gui::Boton::getClick()
{
    if (_estado == estado_boton::ACTIVO) {
        return true;
    }

    return false;
}

const std::string& gui::Boton::getTexto() const
{
    return _texto.getString();
}

/// --------------------------------- ACTUALIZAR ----------------------------------------
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

/// --------------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------------------------
gui::ListaDesplegable::ListaDesplegable(float x, float y, float ancho, float alto, sf::Font& fuente, std::string lista[], unsigned num_elementos, unsigned index_defecto)
    : _fuenteLista(fuente), mostrarLista(false), _ppsTeclasMax(1.f), _ppsTeclas(0.f)
{
    sf::Color colorInactivo = sf::Color(20, 20, 20, 150);
    sf::Color colorActivo = sf::Color(20, 20, 20, 50);
    sf::Color colorHover = sf::Color(70, 70, 70, 200);
    sf::Color colorTexto = sf::Color(255, 255, 255, 150);
    
    //unsigned numElementos = sizeof(lista) / sizeof(std::string)

    for (size_t i = 0; i < num_elementos; i++) {
        
        _lista.push_back(new gui::Boton(x, (y + i * alto), ancho, alto, lista[i], 8, _fuenteLista, colorInactivo, colorHover, colorActivo, colorTexto));

    }

    _elementoActivo = new Boton(*_lista[index_defecto]);

}

gui::ListaDesplegable::~ListaDesplegable()
{
    delete _elementoActivo;

    for (size_t i = 0; i < _lista.size(); i++)
    {
        delete _lista[i];
    }
}

/// --------------------------------- METODOS ----------------------------------------

const bool gui::ListaDesplegable::getPpsTeclas()
{
    if (_ppsTeclas >= _ppsTeclasMax)
    {
        _ppsTeclas = 0.f;
        return true;
    }
    return false;
}

void gui::ListaDesplegable::actualizarPpsTeclas(const float& DT)
{
    if(_ppsTeclas < _ppsTeclasMax)
        _ppsTeclas += 10.f * DT;
}



/// --------------------------------- ACTUALIZAR ----------------------------------------
void gui::ListaDesplegable::actualizar(const sf::Vector2f& posMouse, const float& DT)
{
    actualizarPpsTeclas(DT);

    _elementoActivo->actualizar(posMouse);

    // MOSTRAR Y OCULTAR LISTA
    if (_elementoActivo->getClick() && getPpsTeclas()) // si clickean boton principal
    {
        if (mostrarLista)
            mostrarLista = false; // muestra lista
        else
            mostrarLista = true; // deja de mostrar
    }


    if(mostrarLista)
    {
        for (auto& i : _lista)
        {
            i->actualizar(posMouse);
        }
    }

}

/// --------------------------------- RENDERIZAR ----------------------------------------
void gui::ListaDesplegable::renderizar(sf::RenderTarget& target)
{
    _elementoActivo->renderizar(target); // renderizar boton principal lista
    
    if (mostrarLista)
    {
        for (auto& i : _lista) // renderizar botones
        {
            i->renderizar(target);
        }
    }
}
