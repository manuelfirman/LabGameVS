#ifndef ESTADOOPCIONES_H
#define ESTADOOPCIONES_H

#include "EstadoBase.h"
#include "Gui.h"

class EstadoOpciones : public EstadoBase
{
    private: // Atributos
        sf::Texture _texturaFondoOpciones;
        sf::RectangleShape _fondoOpciones;
        sf::Font _fuenteOpciones;
        sf::Font _fuenteBoton;

        sf::Text _textoOpciones;
        std::vector<sf::VideoMode> _modoVideo;

        std::map<std::string, gui::Boton*> _boton;

        std::map<std::string, gui::ListaDesplegable*> _listasDesplegables;


    private: // Metodos
        void iniciarVariables();
        void iniciarKeybinds();
        void iniciarFondo();
        void iniciarFuentes();
        void iniciarGUI();
        void iniciarTexto();
	
	public:
		EstadoOpciones(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado);
		virtual ~EstadoOpciones();
        void actualizarGUI(const float& DT);
        void renderizarGUI(sf::RenderTarget& target);


        void actualizarInput(const float& DT);
        void actualizar(const float& DT);
        void renderizar(sf::RenderTarget* target = NULL);
};

#endif