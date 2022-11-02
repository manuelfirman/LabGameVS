#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H

#include "EstadoBase.h"
#include "EstadoOpciones.h"
#include "EstadoTutorial.h"
#include "MenuPausa.h"

#include "Jugador.h"
#include "GUIJugador.h"
#include "TileMap.h"

#include "Espada.h"
#include "Orbe.h"

#include "ManagerEnemigos.h"
#include "SpawnerEnemigos.h"
#include "Demon.h"

#include "TextoInfo.h"


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

    //Enemigos
    ManagerEnemigos* _managerEnemigos;
    std::vector<Enemigos*> _enemigos;

    // Texto
    TextoInfo* _popUps;

    // Audio
    Audio* _audio;
    std::map<std::string, sf::SoundBuffer> _bufferSonidosJ;

    // 
    bool _botonesPausa;
    bool _resetVentana;

    // Timers sonido
    sf::Clock _timerSonidoEnemigos;
    sf::Clock _muerteEnemigo;
    

private: // Metodos
    void iniciarVariables();
    void renderizadoDiferido();
    void iniciarVistaCam();
    void iniciarFuentes();
    void iniciarKeybinds();
    void iniciarTexturas();
    void iniciarSonidos();
    void iniciarAudio();
    void iniciarMenuPausa();
    void iniciarSombras();
    void iniciarJugadores();
    void iniciarGUIJugador();
    void iniciarManagerEnemigos();
    void iniciarTileMap();
    void iniciarPopUps();

public:
    EstadoJuego(DatosEstado* datos_estado);
    EstadoJuego(DatosEstado* datos_estado, const std::string ruta_slot);
    ~EstadoJuego();

    const bool guardarPartida(const std::string ruta_slot);
    const bool cargarPartida(const std::string ruta_slot);


    const bool puedeSonar();

    void actualizarVistaCam(const float& DT);
    void actualizarInput(const float& DT);
    void actualizarInputJugador(const float& DT);
    void actualizarBotonesPausa();

    void actualizarJugador(const float& DT);
    void actualizarEnemigos(const float& DT);
    void actualizarAtaques(Enemigos* enemigo, const int indice, const bool basico, const float& DT);
    void actualizarTileMap(const float& DT);

    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget* target = NULL);
};

#endif // ESTADOJUEGO_H
