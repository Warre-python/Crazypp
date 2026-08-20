#pragma once
#include <vector>
#include <memory>
#include "Transform.hpp"
#include "rendering/Renderer.hpp"


class Node {
public:
    virtual ~Node() = default;

    virtual void update(float deltaTime) {}
    virtual void draw(Renderer& renderer) {}

    void addChild(std::unique_ptr<Node> child);
    void move(float deltaX, float deltaY);
    glm::mat4 getWorldMatrix() const;

protected:
    Node* m_parent = nullptr;
    std::vector<std::unique_ptr<Node>> m_children;
    Transform2D m_transform;
private:
    void setParent(Node* parent) {
        m_parent = parent;
    }


    

    
};

