#ifndef SONIDO_H
#define SONIDO_H
class Sonido
{
	private:

		std::string _prefijo;

		std::map<std::string, sf::SoundBuffer>& _buffer;
		sf::Sound _sonido;


		
	public:
		Sonido(std::map<std::string, sf::SoundBuffer>& sonidos, std::string prefijo);
		~Sonido();

		void play(std::string nombre_sonido);
};

#endif