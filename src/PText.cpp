#include "../include/PText.hpp"

PText::PText() : outline(true), blowing(false), flickering(false), visibleFlicker(true), outlineStroke(3),
                 originalSize(30), flickerToggleTime(0), totalTimesFlicker(0), timesFlickered(0), blowingTime(-1),
                 outlineColor(Color::Black)
{
    font =  new Font();
    if(not font->loadFromFile("assets/arial.ttf")) DbgError("Error loading the font 'assets/arial.ttf'.");
    else setFont(*font);

    fClock = new Clock();
    bClock = new Clock();

    setCharacterSize(originalSize);
    setColor(Color::White);
    setString("");
}
PText::PText(const char* str) : PText() { setString(str); }
PText::PText(const Vector2f& pos) : PText() { setPosition(pos); }
PText::PText(const Font& f) : PText()
{
    font = new Font(f);
    setFont(*font);
}
PText::PText(const char* str, const Vector2f& pos) : PText()
{
    setPosition(pos);
    setString(str);
}
PText::PText(const Font& f, const Vector2f& pos) : PText()
{
    font = new Font(f);
    setPosition(pos);
    setFont(*font);
}
PText::PText(const char* str, const Font& f, const Vector2f& pos) : PText()
{
    font = new Font(f);
    setPosition(pos);
    setString(str);
    setFont(*font);
}

PText::~PText()
{
    DbgWarning("destroyed");
    if(fClock) delete fClock;
    if(bClock) delete bClock;
    if(font)  delete font;
}

void PText::setOutline(bool outline)     { this->outline = outline; }
void PText::setOutlineColor(Color c)     { outlineColor = c; }
void PText::setOutlineStroke(int stroke) { outlineStroke = stroke; }

void PText::blow(float multiplier, int msTotalTime)
{
    originalSize = getCharacterSize();
    blowingMult = multiplier - 1.0f;
    blowingTime = msTotalTime;
    blowing = true;
    bClock->restart();
}

void PText::flicker(int times, float msToggleTime)
{
    flickering = true;
    timesFlickered = 0;
    totalTimesFlicker = times;
    flickerToggleTime = msToggleTime;
    visibleFlicker = visibleFlicker ? false : true;
    fClock->restart();
}

void PText::onUpdate(float dt)
{
    if(timesFlickered < totalTimesFlicker and fClock->getElapsedTime().asMilliseconds() >= flickerToggleTime)
    {
        visibleFlicker = visibleFlicker ? false : true;
        if(visibleFlicker) ++timesFlickered;
        fClock->restart();
    }

    if(blowing)
    {
        float bms = float(bClock->getElapsedTime().asMilliseconds());
        int bt = blowingTime/2;
        if(bms <= bt) setCharacterSize( originalSize * (1.0f + blowingMult * (bms/bt)) );
        else if(bms >= bt)
        {
            if(bms >= blowingTime){ blowing = false; setCharacterSize(originalSize); }
            else setCharacterSize( originalSize * ( 1.0f + blowingMult - blowingMult * ((bms-bt)/bt) ) );
        }
    }
}

const Transform &PText::getNodeTransform()
{
    return Text::getTransform();
}

Rect<float> PText::getLocalBB()
{
    return Text::getLocalBounds();
}

void PText::onDraw(RenderTarget& target, const Transform& transform) 
{
    if(not visibleFlicker) return;

    if(outline)
    {
        Color lastColor = getColor();
        Vector2f pos = getPosition();
        setColor(outlineColor);
        for(int x = 0; x < outlineStroke; ++x)
        {
            for(int y = 0; y < outlineStroke; ++y)
            {
                setPosition(pos.x + x, pos.y); target.draw(*this, transform);
                setPosition(pos.x - x, pos.y); target.draw(*this, transform);
                setPosition(pos.x, pos.y + y); target.draw(*this, transform);
                setPosition(pos.x, pos.y - y); target.draw(*this, transform);
                setPosition(pos.x + x, pos.y + y); target.draw(*this, transform);
                setPosition(pos.x + x, pos.y - y); target.draw(*this, transform);
                setPosition(pos.x - x, pos.y + y); target.draw(*this, transform);
                setPosition(pos.x - x, pos.y - y); target.draw(*this, transform);
            }
        }
        setColor(lastColor);
        setPosition(pos);
    }

    target.draw(*this, transform);
}
