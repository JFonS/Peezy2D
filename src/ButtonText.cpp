#include "../include/ButtonText.hpp"


ButtonText::ButtonText() : PText(),
                            outlineColorIdle(Color::Red), outlineColorOver(Color::Green),
                            outlineColorDown(Color::Blue), colorIdle(Color::Black), colorOver(Color::Black),
                            colorDown(Color::Black), outlineIdle(false), outlineOver(true), outlineDown(true)
{
    textIdle = "I'm a button!";
    textOver = "Over meeah!";
    textDown = "Don't touch me biatch!";
    downFunction = [](){}; //do nothing
    goToIdle();
}

ButtonText::~ButtonText() { }

void ButtonText::onMouseEnter(PEvent &e) { goToOver(); }
void ButtonText::onMouseExit(PEvent &e) { goToIdle(); }
void ButtonText::onMouseDown(PEvent &e) { goToDown(); }
void ButtonText::onMouseUp(PEvent &e) { if(mouseIsOver) goToOver(); else goToIdle(); }

void ButtonText::goToIdle() {
    setString(textIdle);
    setOutline(outlineIdle);
    setOutlineColor(outlineColorIdle);
}

void ButtonText::goToOver() {
    setString(textOver);
    setOutline(outlineOver);
    setOutlineColor(outlineColorOver);
}

void ButtonText::goToDown() {
    setString(textDown);
    setOutline(outlineDown);
    setOutlineColor(outlineColorDown);
    downFunction();
}

