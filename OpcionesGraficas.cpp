#include "stdafx.h"
#include "OpcionesGraficas.h"

OpcionesGraficas::OpcionesGraficas()
{
	_titulo = "default";
	_resolucion = sf::VideoMode::getDesktopMode();
	_modosVideo = sf::VideoMode::getFullscreenModes();
	_fullscreen = false;
	_sincVertical = false;
	_opcionesContexto.antialiasingLevel = 0;
	_limiteFramerate = 120;
}

// Metodos
void OpcionesGraficas::guardarEnArchivo(const std::string ruta)
{
	std::ofstream archivoOUT(ruta);

	if (archivoOUT.is_open()) {
		archivoOUT << _titulo;
		archivoOUT << _resolucion.width << " " << _resolucion.height;
		archivoOUT << _limiteFramerate;
		archivoOUT << _fullscreen;
		archivoOUT << _sincVertical;
		archivoOUT << _opcionesContexto.antialiasingLevel;
	}

	archivoOUT.close();
}
void OpcionesGraficas::cargarDesdeArchivo(const std::string ruta)
{
	std::ifstream archivoIN(ruta);

	if (archivoIN.is_open()) {
		std::getline(archivoIN, _titulo);
		archivoIN >> _resolucion.width >> _resolucion.height;
		archivoIN >> _limiteFramerate;
		archivoIN >> _fullscreen;
		archivoIN >> _sincVertical;
		archivoIN >> _opcionesContexto.antialiasingLevel;
	}

	archivoIN.close();
}