#ifndef IA_H
#define IA_H

#include "Entidades.h"

class IA
{
	private:
		Entidades& _jugador;
		Entidades& _entidad;
		

	public:
		IA(Entidades& jugador, Entidades& entidad);
		~IA();

		void seguir(const float& DT);
	
};

#endif // !IA_H
