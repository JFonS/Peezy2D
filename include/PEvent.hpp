#ifndef PEVENT_HPP
#define PEVENT_HPP

#include <SFML/Window.hpp>

using namespace sf;

class PEvent : public Event
{
public:

  PEvent(const Event &e);
  bool propagate;    
};

#endif
