#include <iostream>

#include <glimac/TrackballCamera.hpp>

TrackballCamera::TrackballCamera() {
    m_fDistance = 13.7;
    m_fAngleX = 54;
    m_fAngleY = 0;
}

void TrackballCamera::print() {
    std::cout << "Distance = " << m_fDistance << std::endl;
    std::cout << "AngleX = " << m_fAngleX << std::endl;
    std::cout << "AngleY = " << m_fAngleY << std::endl;
}

void TrackballCamera::moveFront(float delta) {
    m_fDistance += delta;
}

void TrackballCamera::rotateLeft(float degrees) {
    m_fAngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees) {
    m_fAngleX += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 ViewMatrix;

    ViewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(0, 0, -m_fDistance));
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleY), glm::vec3(0,1,0));
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));

    return ViewMatrix;
}
