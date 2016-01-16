#include "../include/PEvent.hpp"

PEvent::PEvent(const Event &e) :  Event(e), propagate(true)
{
}
