#include <glimac/FreeflyCamera.hpp>

void FreeflyCamera::computeDirectionVectors() {
    m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi));
    m_LeftVector = glm::vec3( glm::sin(m_fPhi + glm::pi<float>()/2), 0, glm::cos(m_fPhi + glm::pi<float>()/2) );
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

FreeflyCamera::FreeflyCamera() {
    m_Position = glm::vec3(0,0,0);
    m_fPhi = glm::pi<float>();
    m_fTheta = 0.f;
    computeDirectionVectors();
}

void FreeflyCamera::moveLeft(float t) {
    m_Position += (t*m_LeftVector);
    computeDirectionVectors();
}

void FreeflyCamera::moveFront(float t) {
    m_Position += (t*m_FrontVector);
    computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees) {
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees) {
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const {
    glm::mat4 viewMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    return viewMatrix;
}
