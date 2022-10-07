#include "stdafx.h" // precompilado
#include "Gui.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                          BOTON
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// --------------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------------------------
gui::Boton::Boton(float posX, float posY, float ancho, float alto, std::string texto, int tamanioLetra, sf::Font& fuente,
    sf::Color colorBotonInactivo, sf::Color colorBotonHover, sf::Color colorBotonActivo,
    sf::Color colorTextoInactivo, sf::Color colorTextoHover, sf::Color colorTextoActivo,
    sf::Color colorExteriorInactivo, sf::Color colorExteriorHover, sf::Color colorExteriorActivo,
    int id)
{
    _estado = estado_boton::INACTIVO;
    _id = id;
    
    _colorBotonInactivo = colorBotonInactivo;
    _colorBotonHover = colorBotonHover;
    _colorBotonActivo = colorBotonActivo;
  
    _colorTextoInactivo = colorTextoInactivo;
    _colorTextoHover = colorTextoHover;
    _colorTextoActivo = colorTextoActivo;

    _colorExteriorInactivo = colorExteriorInactivo;
    _colorExteriorHover = colorExteriorHover;
    _colorExteriorActivo = colorExteriorActivo;
  
    _texto.setString(texto);
    _texto.setFillColor(colorTextoInactivo);
    _texto.setCharacterSize(tamanioLetra);
    _texto.setFont(fuente);
    
    _boton.setSize(sf::Vector2f(ancho, alto));
    _boton.setPosition(posX, posY);
    _boton.setFillColor(colorBotonInactivo);
    _boton.setOutlineThickness(1.f);
    _boton.setOutlineColor(colorExteriorInactivo);

    _texto.setPosition(
        _boton.getPosition().x + (_boton.getGlobalBounds().width / 2.f) - _texto.getGlobalBounds().width / 2.f, _boton.getPosition().y);
    
   /* _texto.setPosition(
        _boton.getPosition().x + (_boton.getGlobalBounds().width / 2.f) - _texto.getGlobalBounds().width / 2.f,
        _boton.getPosition().y + (_boton.getGlobalBounds().height / 2.f) - _texto.getGlobalBounds().height);*/
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

void gui::Boton::setID(int id)
{
    _id = id;
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

const std::string gui::Boton::getTexto() const
{
    return _texto.getString();
}

const int& gui::Boton::getID() const
{
    return _id;
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
        _texto.setFillColor(_colorTextoInactivo);
        _boton.setOutlineColor(_colorExteriorInactivo);
        break;

    case estado_boton::HOVER:
        _boton.setFillColor(_colorBotonHover);
        _texto.setFillColor(_colorTextoHover);
        _boton.setOutlineColor(_colorExteriorHover);
        break;

    case estado_boton::ACTIVO:
        _boton.setFillColor(_colorBotonActivo);
        _texto.setFillColor(_colorTextoActivo);
        _boton.setOutlineColor(_colorExteriorActivo);
        break;
    default:
        _boton.setFillColor(sf::Color::Red);
        _texto.setFillColor(sf::Color::Blue);
        _boton.setOutlineColor(sf::Color::Green);
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
//                                                                LISTAS DESPLEGABLES
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

/// --------------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------------------------
gui::ListaDesplegable::ListaDesplegable(float x, float y, float ancho, float alto, sf::Font& fuente, std::string lista[], int num_elementos, int index_defecto)
    : _fuenteLista(fuente), mostrarLista(false), _ppsTeclasMax(1.f), _ppsTeclas(0.f)
{
    sf::Color colorInactivo = sf::Color(20, 20, 20, 150);
    sf::Color colorActivo = sf::Color(20, 20, 20, 50);
    sf::Color colorHover = sf::Color(70, 70, 70, 200);
    
    sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 200);
    sf::Color colorTextoHover = sf::Color(255, 0, 0, 255);
    sf::Color colorTextoActivo = sf::Color(255, 0, 0, 200);

    sf::Color colorExteriorInactivo = sf::Color(255, 255, 255, 100);
    sf::Color colorExteriorHover = sf::Color(255, 255, 255, 200);
    sf::Color colorExteriorActivo = sf::Color(255, 255, 255, 250);
    //unsigned numElementos = sizeof(lista) / sizeof(std::string)

    _elementoActivo = new gui::Boton(x, y, ancho, alto, lista[index_defecto], 12, _fuenteLista, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo, colorExteriorInactivo, colorExteriorHover, colorExteriorActivo);

    for (int i = 0; i < num_elementos; i++) {
        
        _lista.push_back(new gui::Boton(x, y + ((i+1) * alto), ancho, alto, lista[i], 8, _fuenteLista, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo, colorExteriorInactivo, colorExteriorHover, colorExteriorActivo, i));

    }


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
const int& gui::ListaDesplegable::getIDelementoAtivo() const
{
    return _elementoActivo->getID();
}

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

            if (i->getClick() && getPpsTeclas())
            {
                mostrarLista = false;
                _elementoActivo->setTexto(i->getTexto());
                _elementoActivo->setID(i->getID());
            }
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


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                    SELECTOR DE TEXTURAS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------


/// --------------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------------------------
gui::SelectorTexturas::SelectorTexturas(float x, float y, float ancho, float alto, float tamanioCuadro, const sf::Texture* plantilla_textura, sf::Font& fuente, std::string texto)
    : _ppsTeclasMax(1.f), _ppsTeclas(0.f)
{
    _tamanioCuadro = tamanioCuadro;
    _activo = false;
    _esconder = false;
    float offset = 100.f;

    _limites.setSize(sf::Vector2f(ancho, alto));
    _limites.setPosition(x + offset, y);
    _limites.setFillColor(sf::Color(50, 50, 50, 100));
    _limites.setOutlineThickness(1.f);
    _limites.setOutlineColor(sf::Color(255, 255, 255, 200));

  _sheet.setTexture(*plantilla_textura);
  _sheet.setPosition(x + offset, y);

  if (_sheet.getGlobalBounds().width > _limites.getGlobalBounds().width)
  {
    _sheet.setTextureRect(sf::IntRect(0, 0, _limites.getGlobalBounds().width, _limites.getGlobalBounds().height));
  }

  if (_sheet.getGlobalBounds().height > _limites.getGlobalBounds().height)
  {
    _sheet.setTextureRect(sf::IntRect(0, 0, _limites.getGlobalBounds().width, _limites.getGlobalBounds().height));
  }

  _selector.setPosition(x + offset, y);
  _selector.setSize(sf::Vector2f(tamanioCuadro, tamanioCuadro));
  _selector.setFillColor(sf::Color::Transparent);
  _selector.setOutlineThickness(1.f);
  _selector.setOutlineColor(sf::Color::Red);

  _rectTextura.width = static_cast<int>(tamanioCuadro);
  _rectTextura.height = static_cast<int>(tamanioCuadro);

  _botonEsconder = new gui::Boton(x, y, 50.f, 50.f, texto, 20, fuente, sf::Color(255, 255, 255,200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}

gui::SelectorTexturas::~SelectorTexturas()
{
    delete _botonEsconder;
}

const bool& gui::SelectorTexturas::getActivo() const
{
    return _activo;
}

const sf::IntRect& gui::SelectorTexturas::getRectTextura() const
{
    return _rectTextura;
}

const bool gui::SelectorTexturas::getPpsTeclas()
{
    if (_ppsTeclas >= _ppsTeclasMax)
    {
        _ppsTeclas = 0.f;
        return true;
    }
    return false;
}

void gui::SelectorTexturas::actualizarPpsTeclas(const float& DT)
{
    if (_ppsTeclas < _ppsTeclasMax)
        _ppsTeclas += 10.f * DT;
}

void gui::SelectorTexturas::actualizar(const sf::Vector2i& posMouseVentana, const float& DT)
{
    actualizarPpsTeclas(DT);
    _botonEsconder->actualizar(static_cast<sf::Vector2f>(posMouseVentana));

    if (_botonEsconder->getClick() && getPpsTeclas())
    {
        if(_esconder)
            _esconder = false;
        else
            _esconder = true;
    }

    if (!_esconder) 
    {
        if(_limites.getGlobalBounds().contains(static_cast<sf::Vector2f>(posMouseVentana)))
            _activo = true;
        else
            _activo = false;


        if (_activo)
        {
            _posMouseCuadro.x = (posMouseVentana.x - static_cast<int>(_limites.getPosition().x)) / static_cast<unsigned>(_tamanioCuadro);
            _posMouseCuadro.y = (posMouseVentana.y - static_cast<int>(_limites.getPosition().y)) / static_cast<unsigned>(_tamanioCuadro);
            _selector.setPosition(_limites.getPosition().x + _posMouseCuadro.x * _tamanioCuadro, _limites.getPosition().y + _posMouseCuadro.y * _tamanioCuadro);

            _rectTextura.left = static_cast<int>(_selector.getPosition().x - _limites.getPosition().x);
            _rectTextura.top = static_cast<int>(_selector.getPosition().y - _limites.getPosition().y);
        }
    }


}

void gui::SelectorTexturas::renderizar(sf::RenderTarget& target)
{
    if (!_esconder)
    {
        target.draw(_limites);
        target.draw(_sheet);

        if(_activo)
            target.draw(_selector);
    }

    _botonEsconder->renderizar(target);
}
