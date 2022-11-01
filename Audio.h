#ifndef AUDIO_H
#define AUDIO_H
class Audio
{
	private:
		sf::Music _musica;
		sf::Sound _sonido;
		std::map<std::string, sf::SoundBuffer>& _bufferSonido;
		

	public:
		Audio(const std::string ruta_musica, std::map<std::string, sf::SoundBuffer>& buffers_sonido);
		~Audio();

		void playMusica();
		void stopMusica();
		void playSonido(const std::string nombre_sonido);
};

#endif