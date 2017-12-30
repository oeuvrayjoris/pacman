#pragma once

#include <vector>
#include "common.hpp"

class Cube {
	public:
		// Constructor
		Cube(float size);

		// Methods
		void build(float size);
		const float* getDataPointer() const;
		GLsizei getVertexCount() const;

	private:
		// Attr
		std::vector<float> m_Vertices;
		GLsizei m_nVertexCount; // Nombre de sommets
};