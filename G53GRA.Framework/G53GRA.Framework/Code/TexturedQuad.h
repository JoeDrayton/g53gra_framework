#pragma once

#include "DisplayableObject.h"
#include <string>

class TexturedQuad :
	public DisplayableObject
{
public:
	TexturedQuad(const std::string& filename);
	~TexturedQuad() {};

	void Display();

private:
	void DrawQuad();
	GLint texID;
};

