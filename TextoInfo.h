#ifndef TEXTOINFO_H
#define TEXTOINFO_H

enum tipo_popUp{ POP_DEFAULT = 0, POP_MAPA, POP_NEGATIVO, POP_POSITIVO, POP_EXPERIENCIA };

class TextoInfo
{
	private:
		class Texto
		{
			private:
				sf::Text _texto;
				float _dirX;
				float _dirY;
				float _tiempo;
				float _velocidad;


			public:
				Texto(sf::Font& fuente, std::string texto, sf::Color color, unsigned tam_letra, float tiempo, float velocidad, float posX, float posY, float dirX, float dirY)
				{
					_texto.setFont(fuente);
					_texto.setString(texto);
					_texto.setFillColor(color);
					_texto.setCharacterSize(tam_letra);
					_texto.setPosition(posX, posY);

					_dirX = dirX;
					_dirY = dirY;
					_tiempo = tiempo;
					_velocidad = velocidad;

				}

				Texto(Texto* pop, float posX, float posY, std::string texto)
				{
					_texto = pop->_texto;
					_texto.setString(texto);
					_texto.setPosition(posX, posY);
					_dirX = pop->_dirX;
					_dirY = pop->_dirY;
					_tiempo = pop->_tiempo;
					_velocidad = pop->_velocidad;
				}

				~Texto(){};
				
				const bool finPopUp() const
				{
					if (_tiempo <= 0.f) return true;
					else return false;
				}

				void actualizar(const float& DT)
				{
					if (_tiempo > 0.f)
					{
						_tiempo -= 100.f * DT;

						_texto.move(_dirX * _velocidad * DT, _dirY * _velocidad * DT);
					}

				}

				void renderizar(sf::RenderTarget& target)
				{
					target.draw(_texto);
				}
		};

		sf::Font _fuente;
		std::map<unsigned, Texto*> _plantillas;
		std::vector<Texto*> _popUps;

	private:
		void iniciarFuente(std::string ruta_archivo_fuente);
		void iniciarVariables();
		void iniciarPlantillas();

	public:
		TextoInfo(std::string ruta_archivo_fuente);
		~TextoInfo();


		void agregarPopUp(const unsigned tipo_popUp, const float posX, const float posY, const std::string pre_texto, const std::string texto, const std::string post_texto);	// string pop
		void agregarPopUp(const unsigned tipo_popUp, const float posX, const float posY, const std::string pre_texto, const int valor_int, const std::string post_texto);		// int pop
		void agregarPopUp(const unsigned tipo_popUp, const float posX, const float posY, const std::string pre_texto, const float valor_float, const std::string post_texto);	// float pop
		void quitarPopUp();

		void actualizar(const float& DT);
		void renderizar(sf::RenderTarget& target);

};

#endif