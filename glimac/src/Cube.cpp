#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

void Cube::build() {
    m_Vertices = {-1.0f,-1.0f,-1.0f,
                  -1.0f,-1.0f, 1.0f,
                  -1.0f, 1.0f, 1.0f,
                  1.0f, 1.0f,-1.0f,
                  -1.0f,-1.0f,-1.0f,
                  -1.0f, 1.0f,-1.0f,
                  1.0f,-1.0f, 1.0f,
                  -1.0f,-1.0f,-1.0f,
                  1.0f,-1.0f,-1.0f,
                  1.0f, 1.0f,-1.0f,
                  1.0f,-1.0f,-1.0f,
                  -1.0f,-1.0f,-1.0f,
                  -1.0f,-1.0f,-1.0f,
                  -1.0f, 1.0f, 1.0f,
                  -1.0f, 1.0f,-1.0f,
                  1.0f,-1.0f, 1.0f,
                  -1.0f,-1.0f, 1.0f,
                  -1.0f,-1.0f,-1.0f,
                  -1.0f, 1.0f, 1.0f,
                  -1.0f,-1.0f, 1.0f,
                  1.0f,-1.0f, 1.0f,
                  1.0f, 1.0f, 1.0f,
                  1.0f,-1.0f,-1.0f,
                  1.0f, 1.0f,-1.0f,
                  1.0f,-1.0f,-1.0f,
                  1.0f, 1.0f, 1.0f,
                  1.0f,-1.0f, 1.0f,
                  1.0f, 1.0f, 1.0f,
                  1.0f, 1.0f,-1.0f,
                  -1.0f, 1.0f,-1.0f,
                  1.0f, 1.0f, 1.0f,
                  -1.0f, 1.0f,-1.0f,
                  -1.0f, 1.0f, 1.0f,
                  1.0f, 1.0f, 1.0f,
                  -1.0f, 1.0f, 1.0f,
                  1.0f,-1.0f, 1.0f
    };
}

Cube::Cube() {
    m_nVertexCount = 108;
    build();
}

const float* Cube::getDataPointer() const {
    return &m_Vertices[0];
}

GLsizei Cube::getVertexCount() const {
    return m_nVertexCount;
}