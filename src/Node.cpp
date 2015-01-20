#include "include/Node.hpp"
#include "include/ResourceManager.hpp"
#include "Debug.hpp"

Node::Node(): name("none"), zIndex(0) {}

string Node::getName() const { return name; }

int Node::getIndex() const { return zIndex; }

void Node::setIndex(int z) { zIndex = z; }

bool Node::zIndexSort(const Node* first, const Node* second) {
	return first->getIndex() <= second->getIndex();
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
