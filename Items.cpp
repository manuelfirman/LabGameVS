#include "stdafx.h"
#include "Items.h"

Items::Items(int nivel, unsigned valor)
{
	_nivel = 1;
	_tipo = tipo_item::BASE;
	_valor = valor;
}

Items::~Items()
{
}
