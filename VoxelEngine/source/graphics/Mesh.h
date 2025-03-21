#ifndef GRAPHICS_MESH_H_
#define GRAPHICS_MESH_H_

#include <stdlib.h>

class Mesh {
	unsigned int vao;
	unsigned int vbo;
	size_t vertices;
public:
	Mesh(const float* buffer, size_t vertices, const int* attrs);
	~Mesh();

	void draw(unsigned int primitive);
};

#endif /* GRAPHICS_MESH_H_ */