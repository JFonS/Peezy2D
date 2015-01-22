#include <SFML/Graphics.hpp>

#include "../include/Debug.hpp"
#include "../include/GameObject.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Scene.hpp"
#include "../include/PText.hpp"
#include "../include/PeezyWin.hpp"
#include "../pong/Pong.hpp"

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    Pong game = Pong();
    game.play();
    return 0;
}

