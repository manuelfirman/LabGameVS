#ifndef ITEMS_H
#define ITEMS_H

enum tipo_item{ BASE = 0, ARMA_RANGO, ARMA_MELE };

class Items
{
	private:

	protected:
		int _nivel;
		int _tipo;
		unsigned _valor;


	public:
		Items(int nivel, unsigned valor);
		virtual ~Items();
};

#endif // !ITEMS_H
