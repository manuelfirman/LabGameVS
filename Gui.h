#ifndef GUI_H
#define GUI_H

enum estado_boton { INACTIVO = 0, HOVER, ACTIVO };

namespace gui
{
    const float p2pX(const float porcentaje, const sf::VideoMode& modo_video);
    const float p2pY(const float porcentaje, const sf::VideoMode& modo_video);
    const unsigned calcTamCaracter(const sf::VideoMode& modo_video, const unsigned modificador = 150);


    // BOTON
    class Boton
    {
        private:
            estado_boton _estado;
            int _id;

            sf::RectangleShape _boton;
            sf::Text _texto;

            sf::Color _colorBotonInactivo;
            sf::Color _colorBotonHover;
            sf::Color _colorBotonActivo;

            sf::Color _colorTextoInactivo;
            sf::Color _colorTextoHover;
            sf::Color _colorTextoActivo;

            sf::Color _colorExteriorInactivo;
            sf::Color _colorExteriorHover;
            sf::Color _colorExteriorActivo;


        public:
            Boton(float posX, float posY, float ancho, float alto, std::string texto, int tamanioLetra, sf::Font& fuente, 
                sf::Color colorBotonInactivo, sf::Color colorBotonHover, sf::Color colorBotonActivo, 
                sf::Color colorTextoInactivo, sf::Color colorTextoHover, sf::Color colorTextoActivo,
                sf::Color colorExteriorInactivo = sf::Color::Transparent, sf::Color colorExteriorHover = sf::Color::Transparent, sf::Color colorExteriorActivo = sf::Color::Transparent,
                int id = 0);
            ~Boton();

            // Setters
            void setColorBoton(sf::Color colorBoton);
            void setColorTexto(sf::Color colorTexto);
            void setPosicion(sf::Vector2f posicion);
            void setFuente(sf::Font& fuente);
            void setTexto(const std::string texto);
            void setID(int id);
            // Accesorios
            bool getClick();
            const std::string getTexto() const;
            const int& getID() const;
           

            // Metodos
            void actualizar(const sf::Vector2i& posMouseVentana);
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
            ListaDesplegable(float x, float y, float ancho, float alto, sf::Font& fuente, unsigned tam_letra, std::string lista[], int num_elementos, int index_defecto = 0);
            ~ListaDesplegable();

            const int& getIDelementoAtivo() const;

            const bool getPpsTeclas();
            void actualizarPpsTeclas(const float& DT);

            void actualizar(const sf::Vector2i& posMouseVentana, const float& DT);
            void renderizar(sf::RenderTarget& target);
    };


    class SelectorTexturas
    {
        private:
            float _ppsTeclas;
            const float _ppsTeclasMax;
            
            float _tamanioCuadro;
            bool _activo;
            bool _esconder;
            gui::Boton* _botonEsconder;
            sf::RectangleShape _limites;
            sf::Sprite _sheet;
            sf::RectangleShape _selector;
            sf::Vector2u _posMouseCuadro;
            sf::IntRect _rectTextura;



        public:
            SelectorTexturas(float x, float y, float ancho, float alto, float sizeCuadro, const sf::Texture* plantilla_textura, sf::Font& fuente, std::string texto);
            ~SelectorTexturas();

            // Accesorios
            const bool& getActivo() const;
            const sf::IntRect& getRectTextura() const;

            const bool getPpsTeclas();
            void actualizarPpsTeclas(const float& DT);

            void actualizar(const sf::Vector2i& posMouseVentana, const float& DT);
            void renderizar(sf::RenderTarget& target);
    };

}
#endif // BOTON_H