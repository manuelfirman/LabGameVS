#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H

class Atributos
{
	private: // revisar si hacer atributos privados con setter o si no vale la pena en este caso


	public:
		// Atributos
		int vitalidad; // checkear su usar int / unsigned para atributos y sistema de leveo
		int fuerza;
		int agilidad;
		int destreza;
		int inteligencia;

		// Sistema de niveles y experiencia
		int nivel;
		int experiencia;
		int expSiguienteNivel;
		int puntosAtributo;

		// Estadisticas
		int hp;
		int hpMax;
		int dmgMin;
		int dmgMax;
		int defensa;
		int punteria;
		int suerte;


		// Metodos
		Atributos(int nivel);
		virtual ~Atributos();

		void actualizarEstadisticas();

		void levelUp();

		void actualizar();

};

#endif