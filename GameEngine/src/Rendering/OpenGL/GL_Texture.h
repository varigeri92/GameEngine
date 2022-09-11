#pragma once
class GL_Texture
{
public:
	GL_Texture(const char* path);
	GL_Texture() = default;

	void Bind();
	int width, height, nrChannels;
private:
	unsigned int texture_ID;
	const char* terxturePath;
};

