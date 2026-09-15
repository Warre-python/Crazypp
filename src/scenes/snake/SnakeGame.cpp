#include "scenes/snake/SnakeGame.hpp"
#include "scenes/snake/Snake.hpp"
#include "scenes/snake/Apple.hpp"
#include "core/Text.hpp"
#include "core/Sprite.hpp"
#include "core/Texture.hpp"

SnakeGame::SnakeGame() {
    addChild(std::make_unique<Snake>()); 
    addChild(std::make_unique<Apple>());
    auto sprite = std::make_unique<Sprite>();
    sprite->setTexture(new Texture("res/textures/WarroxCraft.png"));
    sprite->setPosition(400.0f, 300.0f);
    addChild(std::move(sprite));


    auto text = std::make_unique<Text>(
        "",
        "res/fonts/ARIAL.TTF",
        32
    );
    text->setPosition(50.0f, 50.0f);
    text->setColor(1.0f, 1.0f, 1.0f, 1.0f); // White color
    text->setText("Score: 0");
    addChild(std::move(text));


    
}

SnakeGame::~SnakeGame() {
    // Destructor implementation    
}

void SnakeGame::update(float deltaTime) {
    processInput();
    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}

void SnakeGame::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}

void SnakeGame::processInput() {
    
}

void SnakeGame::increaseScore(int amount) {
    m_score += amount;
    getChild<Text>()->setText("Score: " + std::to_string(m_score));
}
