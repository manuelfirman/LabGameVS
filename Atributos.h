#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H

class Atributos
{
	private: // revisar si hacer atributos privados con setter o si no vale la pena en este caso


	public:
		// Atributos
		int _vitalidad; // checkear su usar int / unsigned para atributos y sistema de leveo
		int _fuerza;
		int _agilidad;
		int _destreza;
		int _inteligencia;

		// Sistema de niveles y experiencia
		unsigned _nivel;
		unsigned _experiencia;
		unsigned _expSiguienteNivel;
		unsigned _puntosAtributo;

		// Estadisticas
		int _hp;
		int _hpMax;
		int _dmgMin;
		int _dmgMax;
		int _defensa;
		int _punteria;
		int _suerte;


		// Metodos
		Atributos(int nivel);
		virtual ~Atributos();

		void actualizarEstadisticas(const bool reset);

		void subirExp(const unsigned experincia);

		void actualizarNivel();

		void actualizar();

		std::string debug() const;

};

#endif