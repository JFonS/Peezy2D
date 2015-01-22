#include "../include/Node.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Debug.hpp"
#include "../include/PeezyWin.hpp"

Node::Node(): name("none"), zIndex(0), mouseIsOver(false) {}

Node::Node(string n): name(n), zIndex(0), mouseIsOver(false) {}

Node::~Node()
{
    DbgWarning("destroyed");
    for(auto it : childrenOrder)
    {
       delete it;
    }
}

string Node::getName() const { return name; }
int Node::getIndex() const { return zIndex; }

void Node::setIndex(int z) { zIndex = z; }

bool Node::zIndexSort(const Node* first, const Node* second) {
	if (first->getIndex() < second->getIndex()) return true;
	else if (first->getIndex() == second->getIndex()) return first > second;
	else return false;
}

void Node::addChild(Node* go) {
	string name = go->getName();

	if (name == "none") {
		name = "node"; 
		name.append(to_string(childID));
		++childID;
	}

	children.insert(pair<string,Node*>(name,go));
	DbgLog("Added " << name << " to " << this->name);  
	childrenOrder.push_front(go);
}

Node* Node::getChild(string name) {
	if (children.find(name) != children.end()) {
		return children[name];
	} else {
		DbgWarning("The node doesn't exist");
	}
	return NULL;
}

void Node::draw(RenderTarget& target, const Transform& parentTransform) {
	Transform combinedTransform = parentTransform * getNodeTransform();
	onDraw(target, parentTransform);
	childrenOrder.sort(zIndexSort);
	for (auto p : childrenOrder) p->draw(target, combinedTransform);
}

void Node::update(float dt) {
	onUpdate(dt);
    if(mouseIsOver) onMouseOver();
	for (auto p : childrenOrder) p->update(dt);
}

const Transform & Node::getNodeTransform(){return Transform::Identity;}

void Node::onEvent(PEvent &e) {
	switch (e.type) {
    case Event::KeyPressed:
      onKeyDown(e);
      break;
    case Event::KeyReleased:
      onKeyUp(e);
      break;
    case Event::MouseMoved:
    {
      bool wasOver = mouseIsOver;
      mouseIsOver = isMouseOver(Vector2f(e.mouseMove.x, e.mouseMove.y));

      if(wasOver and not mouseIsOver) onMouseExit(e);
      else if(not wasOver and mouseIsOver) onMouseEnter(e);

      if(mouseIsOver) onMouseOver();

      onMouseMove(e);
      }
      break;
    case Event::MouseButtonPressed:
      onMouseDown(e);
      break;
    case Event::MouseButtonReleased:
      onMouseUp(e);
      break;
    default: break;
  }
  if (e.propagate) for (auto p : childrenOrder) p->onEvent(e);
}

bool Node::isMouseOver(const Vector2f mousePos)
{
    return getBoundingBox().contains(PeezyWin::peekScene()->camera * getNodeTransform().getInverse() * mousePos);
}

Rect<float> Node::getBoundingBox()
{
    return Rect<float>(.0f, .0f, .0f, .0f);
}

Vector2f Node::localToGlobal(Vector2f pos) {
    return PeezyWin::peekScene()->camera.transformPoint(pos);
}

Vector2f Node::globalToLocal(Vector2f pos) {
    return PeezyWin::peekScene()->camera.getInverse().transformPoint(pos);
}

