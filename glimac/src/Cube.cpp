#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

void Cube::build(float size) {
    m_Vertices = {
            -size,-size,-size,
            -size,-size, size,
            -size, size, size,
            size, size,-size,
            -size,-size,-size,
            -size, size,-size,
            size,-size, size,
            -size,-size,-size,
            size,-size,-size,
            size, size,-size,
            size,-size,-size,
            -size,-size,-size,
            -size,-size,-size,
            -size, size, size,
            -size, size,-size,
            size,-size, size,
            -size,-size, size,
            -size,-size,-size,
            -size, size, size,
            -size,-size, size,
            size,-size, size,
            size, size, size,
            size,-size,-size,
            size, size,-size,
            size,-size,-size,
            size, size, size,
            size,-size, size,
            size, size, size,
            size, size,-size,
            -size, size,-size,
            size, size, size,
            -size, size,-size,
            -size, size, size,
            size, size, size,
            -size, size, size,
            size,-size, size
    };
}

Cube::Cube(float size) {
    m_nVertexCount = 108;
    build(size);
}

const float* Cube::getDataPointer() const {
    return &m_Vertices[0];
}

GLsizei Cube::getVertexCount() const {
    return m_nVertexCount;
}