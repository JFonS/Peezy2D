#ifndef BUTTONTEXT_H
#define BUTTONTEXT_H

#include <SFML/Graphics.hpp>
#include "PText.hpp"
#include <string>
#include <map>
#include <list>

using namespace std;

class ButtonText : public PText
{
public:

    string textIdle, textOver, textDown;
    Color outlineColorIdle, outlineColorOver, outlineColorDown,
          colorIdle, colorOver, colorDown;
    bool outlineIdle, outlineOver, outlineDown;
    function<void()> downFunction;

    ButtonText();
    ~ButtonText();

    virtual void onMouseEnter(PEvent &e);
    virtual void onMouseExit(PEvent &e);
    virtual void onMouseDown(PEvent &e);
    virtual void onMouseUp(PEvent &e);

    void goToIdle();
    void goToOver();
    void goToDown();
};

#endif // BUTTONTEXT_H
