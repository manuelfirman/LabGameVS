#ifndef SONIDO_H
#define SONIDO_H
class Sonido
{
	private:
		std::map<std::string, sf::SoundBuffer> _buffer;
		sf::Sound _sonido;
		
	public:
		Sonido();
		~Sonido();
		void agregarSonido(std::string nombre_sonido, std::string ruta_sonido);
		void play(std::string nombre_sonido);
};

#endif