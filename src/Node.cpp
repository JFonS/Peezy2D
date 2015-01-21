#include "include/Node.hpp"
#include "include/ResourceManager.hpp"
#include "Debug.hpp"

Node::Node(): name("none"), zIndex(0) {}

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
	for (auto p : childrenOrder) p->update(dt);
}

const Transform & Node::getNodeTransform(){return Transform::Identity;}

void Node::onKeyDown(PEvent &e){}
void Node::onKeyUp(PEvent &e){}
void Node::onMouseMove(PEvent &e){}
void Node::onMouseDown(PEvent &e){}
void Node::onMouseUp(PEvent &e){}

void Node::onEvent(PEvent &e) {
	switch (e.type) {
    case Event::KeyPressed:
      onKeyDown(e);
      break;
    case Event::KeyReleased:
      onKeyUp(e);
      break;
    case Event::MouseMoved:
      onMouseMove(e);
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
