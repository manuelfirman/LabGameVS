#ifndef AUDIO_H
#define AUDIO_H
class Audio
{
	private:
		sf::Sound _sonidoJugador;
		sf::Sound _sonidoEnemigo;
		std::map<std::string, sf::SoundBuffer> _bufferSonido;
		std::map<std::string, sf::Sound> _musica;

	public:
		Audio();
		~Audio();

		void playE(const std::string nombre_sonido);
		void playJ(const std::string nombre_sonido);

};

#endif