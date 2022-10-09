#include "stdafx.h"
#include "Atributos.h"

Atributos::Atributos(int nivel)
{
	this->vitalidad = 1;
	this->fuerza = 1;
	this->agilidad = 1;
	this->destreza = 1;
	this->inteligencia = 1;

	this->nivel = nivel;
	this->experiencia = 0;
	this->expSiguienteNivel = 0;
	this->puntosAtributo = 0;

}

Atributos::~Atributos()
{
}

void Atributos::actualizarEstadisticas()
{
}
