#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H

class Atributos
{
	private: // revisar si hacer atributos privados con setter o si no vale la pena en este caso
		// Estadisticas
	public:
		int _hp;
		int _hpMax;
		int _dmgMin;
		int _dmgMax;
		int _defensa;


		// Atributos
		int _vitalidad; // checkear su usar int / unsigned para atributos y sistema de leveo
		int _fuerza;
		int _agilidad;
		int _destreza;
		int _inteligencia;

		// Sistema de niveles y experiencia
		int _nivel;
		int _experiencia;
		int _expSiguienteNivel;
		int _puntosAtributo;


	public:
		// Metodos
		Atributos();
		Atributos(int nivel);
		Atributos(int nivel, int experiencia, int hp, int vitalidad, int fuerza, int agilidad, int destreza, int inteligencia);
		virtual ~Atributos(); 

		// setters
		void setNivel(int nivel);
		void setExperiencia(int experiencia);
		void setHP(int hp);
		void setVitalidad(int vitalidad);
		void setFuerza(int fuerza);
		void setAgilidad(int agilidad);
		void setDestreza(int destreza);
		void setInteligencia(int inteligencia);
		void setPuntosAtributo(int puntos);

		// getters
		const int getDmg();
		const int getHP();
		const int getHPMax();
		const int getExp();
		const int getExpSiguienteNivel();
		const int getNivel();
		const int getVitalidad();
		const int getFuerza();
		const int getAgilidad();
		const int getDestreza();
		const int getInteligencia();
		const int getPuntosAtributo();


		// setters game
		void perderVida(const int hp);
		void ganarVida(const int hp);

		void perderExperiencia(const int exeriencia);
		void ganarExperiencia(const int experiencia);

		const bool estaVivo() const;

		void actualizarEstadisticas(const bool reset);
		void actualizarNivel();
		void actualizar();

		std::string debug() const;
};

#endif