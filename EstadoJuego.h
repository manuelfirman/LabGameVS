#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H
#include "EstadoBase.h"
#include "MenuPausa.h"
#include "Jugador.h"
#include "TileMap.h"

class EstadoBase;
class MenuPausa;
class Jugador;
class TileMap;

class sf::View;
class sf::Font;
class sf::RenderTexture;

class EstadoJuego : public EstadoBase
{
private: // Atributos
    sf::View _vistaCam;
    // Para no renderizar todo de una vez en ventana (Dividirla en fragmentos)
    sf::RenderTexture _renderTextura; // Lienzo
    sf::Sprite _renderSprite; // Contenedor de lienzos

    MenuPausa* _menuPausa;
    sf::Font _fuenteJuego;

    Jugador* player;

    TileMap* _tileMap;




private: // Metodos
    void renderizadoDiferido();
    void iniciarVistaCam();
    void iniciarFuentes();
    void iniciarKeybinds();
    void iniciarTexturas();
    void iniciarMenuPausa();
    void iniciarJugadores();
    void iniciarTileMap();

public:
    EstadoJuego(DatosEstado* datos_estado);
    ~EstadoJuego();


    void actualizarVistaCam(const float& DT);
    void actualizarInput(const float& DT);
    void actualizarInputJugador(const float& DT);
    void actualizarBotonesPausa();
    void actualizarTileMap(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // ESTADOJUEGO_H
