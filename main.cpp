#include <SFML/Graphics.hpp>



/*
CREAR VENTANA PRINCIPAL -> sf::RenderWindow window(sf::VideoMode(800, 600), "SFMl window");

CARGAR UN SPRITE PARA MOSTRAR ->    sf::Texture texture;
                                    if(!texture.loadFromFile("cute_image.jpg"))
                                        return EXIT_FAILURE;
                                        sf::Sprite sprite(texture);

CREA UN TEXTO GRAFICO PARA MOSTRAR ->   sf::Font font;
                                        if(!font.loadFromFile("arial.ttf"))
                                            return EXIT_FAILURE;
                                        sf::Text text("Hello SFML", font, 50);

CARGAR MUSICA PARA REPRODUCIR ->    sf::Music music;
                                    if(!music.openFromFile("nice_music.ogg"))
                                        return EXIT_FAILURE;
REPRODUCIR MUSICA -> music.play();

COMENZAR GAME LOOP -> while(window.isOpen())

PROCESAR EVENTOS -> sf::Event event;
                    while(window.pollEvent(event)){
                        if(event.type == sf::Event::Closed) // Cerrar ventana: exit
                            window.close();
                    }

Limpiar pantalla -> window.clear();
Actualiza ventana -> window.display();
Imprime Sprite -> window.draw(sprite);
Imprime String -> window.draw(text);


*/

#include "Game.h"

int main()
{
    Game game;
    game.gameloop();
    return 0;
}