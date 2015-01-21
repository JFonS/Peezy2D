#include <SFML/Graphics.hpp>

#include "Debug.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "PText.hpp"
#include "PeezyWin.hpp"

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    Vector2i winSize(600, 600);
    PeezyWin win = PeezyWin(winSize);
    return 0;
}

