#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>



//#include <cstdlib>


enum estado_boton { INACTIVO = 0, HOVER, ACTIVO };

namespace gui
{

    // BOTON
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
            // Setters
            void setColorBoton(sf::Color colorBoton);
            void setColorTexto(sf::Color colorTexto);
            void setPosicion(sf::Vector2f posicion);
            void setFuente(sf::Font& fuente);
            void setTexto(const std::string texto);

            // Accesorios
            bool getClick();
            const std::string& getTexto() const;

            // Metodos
            void actualizar(sf::Vector2f posMouse);
            void renderizar(sf::RenderTarget& target);
    };


    // LISTA DESPLEGABLE
    class ListaDesplegable
    {
        private:
            gui::Boton* _elementoActivo;
            std::vector<gui::Boton*> _lista;
            sf::Font& _fuenteLista;
            bool mostrarLista;
            float _ppsTeclas;
            float _ppsTeclasMax;


        public:
            ListaDesplegable(float x, float y, float ancho, float alto, sf::Font& fuente, std::string lista[], unsigned num_elementos, unsigned index_defecto = 0);
            ~ListaDesplegable();

            const bool getPpsTeclas();
            void actualizarPpsTeclas(const float& DT);

            void actualizar(const sf::Vector2f& posMouse, const float& DT);
            void renderizar(sf::RenderTarget& target);
    };

}
#endif // BOTON_H