#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H
#include "EstadoBase.h"
#include "MenuPausa.h"
#include "Jugador.h"
#include "TileMap.h"


class EstadoJuego : public EstadoBase
{
private: // Atributos
    MenuPausa* _menuPausa;
    sf::Font _fuenteJuego;

    Jugador* player;

    TileMap mapa;


private: // Metodos
    void iniciarFuentes();
    void iniciarKeybinds();
    void iniciarTexturas();
    void iniciarMenuPausa();
    void iniciarJugadores();

public:
    EstadoJuego(DatosEstado* datos_estado);
    ~EstadoJuego();


    void actualizarInput(const float& DT);
    void actualizarInputJugador(const float& DT);
    void actualizarBotonesPausa();
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // ESTADOJUEGO_H
