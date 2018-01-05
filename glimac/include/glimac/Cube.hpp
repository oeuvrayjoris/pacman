#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

	class Cube {
	public:
		Cube(float size);

		void build(float size);
		const ShapeVertex *getDataPointer() const;
		GLsizei getVertexCount() const;

	private:
		std::vector<ShapeVertex> m_Vertices;
		GLsizei m_nVertexCount;
	};
}