#include "nodes/Node.hpp"

void Node::addChild(std::unique_ptr<Node> child) {
	if (!child) {
		return;
	}

	child->setParent(this);
	m_children.push_back(std::move(child));
}
void Node::getChildren(std::vector<Node*>& children) const {
	for (const auto& child : m_children) {
		children.push_back(child.get());
	}
}

void Node::setPosition(float x, float y) {
	m_transform.setPosition(x, y);
}

glm::vec2 Node::getPosition() const {
	return glm::vec2(m_transform.getPositionX(), m_transform.getPositionY());
}

void Node::move(float deltaX, float deltaY) {
	m_transform.setPosition(
		m_transform.getPositionX() + deltaX,
		m_transform.getPositionY() + deltaY);
}

glm::mat4 Node::getWorldMatrix() const {
	if (m_parent) {
		return m_parent->getWorldMatrix() * m_transform.getMatrix();
	}

	return m_transform.getMatrix();
}

	


