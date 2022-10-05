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

        std::map<std::string, gui::Boton*> _boton;

    private: // Metodos
        void iniciarVariables();
        void iniciarKeybinds();
        void iniciarFondo();
        void iniciarFuentes();
        void iniciarBotones();
	
	public:
		EstadoOpciones(sf::RenderWindow* ventana, std::map<std::string, int>* teclasSoportadas, std::stack<EstadoBase*>* estado);
		virtual ~EstadoOpciones();
        void actualizarBotones();
        void renderBotones(sf::RenderTarget& target);


        void actualizarInput(const float& DT);
        void actualizar(const float& DT);
        void renderizar(sf::RenderTarget* target = NULL);
};

#endif