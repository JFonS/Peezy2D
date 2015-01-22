#include "../include/Peezy2D.hpp"
#include "../pong/Pong.hpp"

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    Pong game = Pong();
    game.play();
    return 0;
}

