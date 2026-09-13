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
    template <typename T>
    T* getChild() {
        for (const auto& child : m_children) {
            if (auto castedChild = dynamic_cast<T*>(child.get())) {
                return castedChild;
            }
        }
        return nullptr;
    }

    Node *getParent() const {
        return m_parent;
    }
    
    void getChildren(std::vector<Node*>& children) const;
    void setPosition(float x, float y);
    glm::vec2 getPosition() const;
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

