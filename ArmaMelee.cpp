#include "stdafx.h"
#include "ArmaMelee.h"

ArmaMelee::ArmaMelee(int nivel, unsigned valor, std::string ruta_textura)
	: Armas(nivel, valor, ruta_textura)
{
	//std::cout << "Test arma melee" << std::endl;
	_tipo = tipo_item::ARMA_MELE;

}

ArmaMelee::~ArmaMelee()
{
}
