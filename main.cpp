#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    
    
    GameObject go;
    
    sf::Vector2i winSize(600,600);
    sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "");
    sf::RectangleShape line(sf::Vector2f(sqrt(50*50 + 50*50), 4));
    line.setOrigin(line.getGlobalBounds().width/2,line.getGlobalBounds().height/2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        for (int i = 0; i < winSize.x; ++i) {
            for (int j = 0; j < winSize.y; ++j) {
                if (rand()%2 == 0) line.setRotation(45);
                else line.setRotation(135);
                line.setPosition(i*50+25,j*50+25);
                window.draw(line);
            }
        }
        window.display();
    }
    
    return 0;
}

