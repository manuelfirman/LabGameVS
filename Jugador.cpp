#include "stdafx.h" // precompilado
#include "Jugador.h"
/// --------------------- INICIALIZACIONES --------------------------
void Jugador::iniciarVariables()
{
    _atacando = false;
    _espada = new Espada(1 ,20, "recursos/img/items/sword2.png");
}

void Jugador::iniciarComponentes()
{
    if (!_texturaSkill.loadFromFile("recursos/img/skills/fireball_blue.png"))
        std::cout << "ERROR::JUGADOR::NO SE PUDO CARGAR TEXTURA DE SKILL" << std::endl;
}


/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
Jugador::Jugador(float x, float y, sf::Texture& textura)
{
    this->iniciarVariables();
    this->iniciarComponentes();

    setPosicion(x, y);                                  // Posicion

    crearHitbox(_sprite, 18.f, 17.f, 28.f, 44.f);       // Hitbox
    crearComponenteMovimiento(150.f, 1700.f, 1000.f);   // Movimiento
    crearComponenteAnimacion(textura);                  // Animacion
    crearComponenteAtributos(0);                        // Atributos

    // key - Velocidad animacion - inicioX - inicioY - framesX - framesY
    _animacion->agregarAnimacion("QUIETO", 10.f, 1, 10, 1, 10, 64, 64);         // Quieto
    _animacion->agregarAnimacion("CAMINAR_ABAJO", 3.f, 1, 10, 8, 10, 64, 64);   // Caminar abajo
    _animacion->agregarAnimacion("CAMINAR_ARRIBA", 3.f, 1, 8, 8, 8, 64, 64);    // Caminar arriba
    _animacion->agregarAnimacion("CAMINAR_X", 3.f, 1, 9, 8, 9, 64, 64);         // Caminar derecha
    //_animacion->agregarAnimacion("CAMINAR_X", 3.f, 1, 11, 8, 11, 64, 64);       // Caminar izquierda

     // ANIMACIONES ATAQUE
    _animacion->agregarAnimacion("ATAQUE_MAGICO", 5.f, 0, 5, 6, 5, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_ABAJO", 10.f, 1, 14, 5, 14, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_X", 10.f, 1, 13, 5, 13, 64, 64);


}

Jugador::~Jugador()
{
    
}


Atributos* Jugador::getAtributos()
{
    return _atributos;
}

Armas* Jugador::getArma() const
{
    return _espada;
}


void Jugador::ganarHP(const int hp)
{
    _atributos->ganarVida(hp);
}

void Jugador::perderHP(const int hp)
{
    _atributos->perderVida(hp);
}

void Jugador::ganarExperiencia(const int experiencia)
{
    _atributos->ganarExperiencia(experiencia);
}

void Jugador::perdeExperiencia(const int experiencia)
{
    _atributos->perderExperiencia(experiencia);
}

//void Jugador::actualizarAtaque(const float& DT, sf::Vector2f posMouseVista)
//{
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
//        _skill.push_back(Proyectil(_texturaSkill, 10.f, 2.f, 500.f, posMouseVista, getCentro()));
//        _atacando = true;
//    }
//}


void Jugador::actualizarAnimacion(const float& DT, sf::Vector2f& posMouseVista)
{
   // PELADO
    if (_atacando)
    {
        if (_sprite.getScale().x > 0.f)
        {
            _sprite.setOrigin(0.f, 0.f);
        }
        else
        {
            _sprite.setOrigin(_sprite.getGlobalBounds().width, 0.f);
        }
        

        if (_animacion->play("ATAQUE_X", DT, true))
        {
            _atacando = false;
        }
    }


   if (_movimiento->getEstadoMov(QUIETO)) 
   {
        _animacion->play("QUIETO", DT);
   }
   else if (_movimiento->getEstadoMov(MOV_DERECHA))
   {

        _sprite.setOrigin(_sprite.getGlobalBounds().width, 0.f);
        _sprite.setScale(-1.f, 1.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
   }
   else if (_movimiento->getEstadoMov(MOV_IZQUIERDA))
   {
        _sprite.setOrigin(0.f, 0.f);
        _sprite.setScale(1.f, 1.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
   }
   else if (_movimiento->getEstadoMov(MOV_ABAJO))
   {
        _animacion->play("CAMINAR_ABAJO", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
   }
   else if (_movimiento->getEstadoMov(MOV_ARRIBA))
   {
        _animacion->play("CAMINAR_ARRIBA", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
   }
    
}

void Jugador::actualizar(const float& DT, sf::Vector2f& posMouseVista)
{

    //_atributos->actualizar();
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    //    _atributos->ganarExperiencia(20);

    //std::cout << _atributos->debug() << "\n";

    _movimiento->actualizar(DT);

    //actualizarAtaque(DT, posMouseVista);

    actualizarAnimacion(DT, posMouseVista);

    _hitbox->actualizar();

    _espada->actualizar(posMouseVista, getCentro());
    for (size_t i = 0; i < _skill.size(); i++)
    {
        if (_skill[i].getRealizando())
        {
            _skill[i].actualizar(DT);
        }
    }

}

void Jugador::renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox)
{
    if(sombra)
    {
        sombra->setUniform("tieneTextura", true);
        sombra->setUniform("luz", posLuz);
        target.draw(_sprite, sombra);

        sombra->setUniform("tieneTextura", true);
        sombra->setUniform("luz", posLuz);
        _espada->renderizar(target);
    }
    else // si no hay sombra
        target.draw(_sprite);
        _espada->renderizar(target);

    if(mostrar_hitbox)
        _hitbox->renderizar(target);

    for (size_t i = 0; i < _skill.size(); i++)
    {
        Proyectil skill = _skill[i];

        if (!skill.getRealizando() || skill.eliminar())
        {
            _skill.erase(_skill.begin() + i);
        }
    }

    for (size_t i = 0; i < _skill.size(); i++)
    {
        if (!_skill[i].eliminar())
        {
            if (_skill[i].getRealizando())
            {
                _skill[i].renderizar(target);
            }
        }
    }
}
