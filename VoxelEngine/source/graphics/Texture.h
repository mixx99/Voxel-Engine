#pragma once

#include <string>


class Texture
{
public:
	unsigned int id;
	Texture(unsigned int id);
	~Texture();

	void bind();
};

extern Texture* load_texture(std::string filename);
