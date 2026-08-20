#include "core/Node.hpp"

void Node::addChild(std::unique_ptr<Node> child) {
	if (!child) {
		return;
	}

	child->setParent(this);
	m_children.push_back(std::move(child));
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
