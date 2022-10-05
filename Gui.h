#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>

enum estado_boton { INACTIVO = 0, HOVER, ACTIVO };

namespace gui
{
    class Boton
    {
        private:
            estado_boton _estado;

            sf::RectangleShape _boton;
            sf::Text _texto;

            sf::Color _colorBotonInactivo;
            sf::Color _colorBotonHover;
            sf::Color _colorBotonActivo;

            sf::Color _colorTexto;

        public:
            Boton(float posX, float posY, float ancho, float alto, std::string texto, int tamanioLetra, sf::Font& fuente, sf::Color colorBotonInactivo, sf::Color colorBotonHover, sf::Color colorBotonActivo, sf::Color colorTexto);
            ~Boton();

            void setFuente(sf::Font& fuente);
            void setColorBoton(sf::Color colorBoton);
            void setColorTexto(sf::Color colorTexto);
            void setPosicion(sf::Vector2f posicion);
            void actualizar(sf::Vector2f posMouse);
            bool getClick();
            void renderizar(sf::RenderTarget& target);
    };

    class ListaDesplegable
    {
        private:
            sf::RectangleShape _elementoActivo;
            std::vector<gui::Boton*> _lista;
            sf::Font& _fuenteLista;


        public:
            void actualizar(const sf::Vector2f& posMouse);
            void renderizar(sf::RenderTarget& target);
    };

}
#endif // BOTON_H