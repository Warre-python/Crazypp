#pragma once
#include <vector>
#include <memory>
#include "Transform.hpp"

class Node {
public:
    virtual ~Node() = default;

    virtual void update(float deltaTime) {}
    virtual void draw() {}

    void addChild(std::unique_ptr<Node> child);

protected:
    Node* m_parent = nullptr;
    std::vector<std::unique_ptr<Node>> m_children;

private:
    void setParent(Node* parent) {
        m_parent = parent;
    }


    Transform2D m_transform;

    
};

