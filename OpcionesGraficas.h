#ifndef OPCIONESGRAFICAS_H
#define OPCIONESGRAFICAS_H


class OpcionesGraficas // publica
{
public:
	// Atributos
	std::string _titulo;
	sf::VideoMode _resolucion;
	std::vector<sf::VideoMode> _modosVideo;
	bool _fullscreen;
	bool _sincVertical;
	unsigned _limiteFramerate;
	sf::ContextSettings _opcionesContexto;

	
	// Constructor
	OpcionesGraficas();

	// Metodos
	void guardarEnArchivo(const std::string ruta);
	void cargarDesdeArchivo(const std::string ruta);
};
#endif 