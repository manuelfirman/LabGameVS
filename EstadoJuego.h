#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H
#include "EstadoBase.h"
#include "MenuPausa.h"
#include "Jugador.h"
#include "GUIJugador.h"
#include "TileMap.h"
#include "Espada.h"
#include "Orbe.h"

class EstadoBase;
class MenuPausa;
class Jugador;
class TileMap;
class GUIJugador;

class sf::View;
class sf::Font;
class sf::RenderTexture;
class sf::Shader;

class EstadoJuego : public EstadoBase
{
private: // Atributos
    sf::View _vistaCam;
    sf::Vector2i _vistaPosicionCuadros;

    // Para no renderizar todo de una vez en ventana (Dividirla en fragmentos)
    sf::RenderTexture _renderTextura; // Lienzo
    sf::Sprite _renderSprite; // Contenedor de lienzos
    // Menu pausa
    MenuPausa* _menuPausa;
    sf::Font _fuenteJuego;
    // Jugador
    Jugador* _jugador;
    GUIJugador* _GUIJugador;
    // Mapa
    TileMap* _tileMap;

    sf::Shader _sombra;


private: // Metodos
    void renderizadoDiferido();
    void iniciarVistaCam();
    void iniciarFuentes();
    void iniciarKeybinds();
    void iniciarTexturas();
    void iniciarMenuPausa();
    void iniciarSombras();
    void iniciarJugadores();
    void iniciarGUIJugador();
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
