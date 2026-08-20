#pragma once
#include <glm/glm.hpp>

class Transform2D {
public:
    Transform2D();
    ~Transform2D();

    void setPosition(float x, float y);
    void setRotation(float angle);
    void setScale(float scaleX, float scaleY);

    float getPositionX() const { return m_position[0]; }
    float getPositionY() const { return m_position[1]; }
    float getRotation() const { return m_rotation; }
    float getScaleX() const { return m_scale[0]; }
    float getScaleY() const { return m_scale[1]; }

    glm::mat4 getMatrix() const;

    
private:
    float m_position[2];
    float m_rotation;
    float m_scale[2];
};