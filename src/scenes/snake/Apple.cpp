#include "scenes/snake/Apple.hpp"
#include "nodes/Sprite.hpp"

Apple::Apple() {
    m_transform.setPosition(200.0f, 200.0f);
    addChild(std::make_unique<Sprite>());
}

Apple::~Apple() {
    // Destructor implementation
}

void Apple::update(float deltaTime) {
    // Update logic for the apple (if any)
}

void Apple::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        if (auto sprite = dynamic_cast<Sprite*>(child.get())) {
            sprite->circle(10.0f); // Set the size of the apple
            sprite->setColor(1.0f, 0.0f, 0.0f, 1.0f); // Set the color of the apple to red
            sprite->draw(renderer);
        }
    }
}