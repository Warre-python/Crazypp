#pragma once
#include "../../core/Node.hpp"
#include <vector>


class Apple : public Node {
public:
    Apple();
    ~Apple();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

private:
};