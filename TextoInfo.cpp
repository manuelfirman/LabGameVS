#include "stdafx.h"
#include "TextoInfo.h"


void TextoInfo::iniciarFuente(std::string ruta_archivo_fuente)
{
	if (!_fuente.loadFromFile(ruta_archivo_fuente))
		std::cout << "ERROR::TEXTOINFO::NO SE PUDO CARGAR LA FUENTE: " << ruta_archivo_fuente << std::endl;
}

void TextoInfo::iniciarVariables()
{
}

void TextoInfo::iniciarPlantillas()
{
	_plantillas[POP_DEFAULT] = new Texto(_fuente, "", sf::Color::White, 20, 80.f, 100.f, 0.f, 0.f, 0.f, -1.f);
	_plantillas[POP_POSITIVO] = new Texto(_fuente, "", sf::Color::Green, 20, 80.f, 100.f, 0.f, 0.f, 0.f, -1.f);
	_plantillas[POP_NEGATIVO] = new Texto(_fuente, "", sf::Color::Red, 20, 80.f, 100.f, 0.f, 0.f, 0.f, -1.f);
	_plantillas[POP_EXPERIENCIA] = new Texto(_fuente, "", sf::Color::Yellow, 20, 80.f, 100.f, 0.f, 0.f, 0.f, -1.f);
	_plantillas[POP_MAPA] = new Texto(_fuente, "", sf::Color::Black, 20, 80.f, 100.f, 0.f, 0.f, 0.f, -1.f);
}

TextoInfo::TextoInfo(std::string ruta_archivo_fuente)
{
	this->iniciarFuente(ruta_archivo_fuente);
	this->iniciarVariables();
	this->iniciarPlantillas();

}

TextoInfo::~TextoInfo()
{
	for (auto* popUp : _popUps)
	{
		delete popUp;
	}

	for (auto& plantilla : _plantillas)
	{
		delete plantilla.second;
	}
}

void TextoInfo::agregarPopUp(const unsigned tipo_popUp, const float posX, const float posY, const std::string pre_texto, const std::string texto, const std::string post_texto)
{
	std::stringstream cadena;
	cadena << pre_texto << " " << texto << " " << post_texto;
	_popUps.push_back(new Texto(_plantillas[tipo_popUp], posX, posY, cadena.str()));
}

void TextoInfo::agregarPopUp(const unsigned tipo_popUp, const float posX, const float posY, const std::string pre_texto, const int valor_int, const std::string post_texto)
{
	std::stringstream cadena;
	cadena << pre_texto << " " << valor_int << " " << post_texto;
	_popUps.push_back(new Texto(_plantillas[tipo_popUp], posX, posY, cadena.str()));
}

void TextoInfo::agregarPopUp(const unsigned tipo_popUp, const float posX, const float posY, const std::string pre_texto, const float valor_float, const std::string post_texto)
{
	std::stringstream cadena;
	cadena << pre_texto << " " << valor_float << " " << post_texto;
	_popUps.push_back(new Texto(_plantillas[tipo_popUp], posX, posY, cadena.str()));
}

void TextoInfo::quitarPopUp()
{
	
}

void TextoInfo::actualizar(const float& DT)
{
	for (size_t i = 0; i < _popUps.size(); ++i)
	{
		_popUps[i]->actualizar(DT);
		
		if (_popUps[i]->finPopUp())
		{
			delete _popUps[i];
			_popUps.erase(_popUps.begin() + i);
		}
	}

}

void TextoInfo::renderizar(sf::RenderTarget& target)
{
	for (auto& popUp : _popUps)
	{
		popUp->renderizar(target);
	}
}
