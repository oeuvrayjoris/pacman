#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac {
    void Cube::build(float size) {
        std::vector<float> vertices = {
                -size, -size, -size, // Left
                -size, -size, size,
                -size, size, size,
                size, size, -size, // Back
                -size, -size, -size,
                -size, size, -size,
                size, -size, size, // Bottom
                -size, -size, -size,
                size, -size, -size,
                size, size, -size, // Back
                size, -size, -size,
                -size, -size, -size,
                -size, -size, -size, // Left
                -size, size, size,
                -size, size, -size,
                size, -size, size, // Bottom
                -size, -size, size,
                -size, -size, -size,
                -size, size, size, // Front
                -size, -size, size,
                size, -size, size,
                size, size, size, // Right
                size, -size, -size,
                size, size, -size,
                size, -size, -size, // Right
                size, size, size,
                size, -size, size,
                size, size, size, // Top
                size, size, -size,
                -size, size, -size,
                size, size, size, // Top
                -size, size, -size,
                -size, size, size,
                size, size, size, // Front
                -size, size, size,
                size, -size, size
        };

        std::vector<float> normals = {
                -size, 0.0f, 0.0f, // Left
                -size, 0.0f, 0.0f,
                -size, 0.0f, 0.0f,
                0.0f, 0.0f, -size, // Back
                0.0f, 0.0f, -size,
                0.0f, 0.0f, -size,
                0.0f,-size, 0.0f, // Bottom
                0.0f,-size, 0.0f,
                0.0f,-size, 0.0f,
                0.0f, 0.0f, -size, // Back
                0.0f, 0.0f, -size,
                0.0f, 0.0f, -size,
                -size, 0.0f, 0.0f, // Left
                -size, 0.0f, 0.0f,
                -size, 0.0f, 0.0f,
                0.0f,-size, 0.0f, // Bottom
                0.0f,-size, 0.0f,
                0.0f,-size, 0.0f,
                0.0f, 0.0f, size, // front
                0.0f, 0.0f, size,
                0.0f, 0.0f, size,
                size, 0.0f, 0.0f, // right
                size, 0.0f, 0.0f,
                size, 0.0f, 0.0f,
                size, 0.0f, 0.0f, // right
                size, 0.0f, 0.0f,
                size, 0.0f, 0.0f,
                0.0f, size, 0.0f, // top
                0.0f, size, 0.0f,
                0.0f, size, 0.0f,
                0.0f, size, 0.0f, // top
                0.0f, size, 0.0f,
                0.0f, size, 0.0f,
                0.0f, 0.0f, size, // front
                0.0f, 0.0f, size,
                0.0f, 0.0f, size,
        };

        int j=0;
        for(int i=0; i<vertices.size(); i+=3) {
            ShapeVertex vertex;
            vertex.position = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
            vertex.normal = glm::vec3(normals[i], normals[i+1], normals[i+2]);
            //vertex.texCoords = glm::vec2(coords_uv[j], coords_uv[j+1]);
            j+=2;
            m_Vertices.push_back(vertex);
        }
    }

    Cube::Cube(float size) {
        m_nVertexCount = 108;
        build(size);
    }

    const ShapeVertex * Cube::getDataPointer() const {
        return &m_Vertices[0];
    }

    GLsizei Cube::getVertexCount() const {
        return m_nVertexCount;
    }
}