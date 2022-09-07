#include "GL_Texture.h"
#include "stb_image.h"
#include "GL/glew.h"
#include "Log.h"
GL_Texture::GL_Texture(const char* path)
{
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG_ERROR("Failed To load Texture");
	}
	stbi_image_free(data);

}

void GL_Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texture_ID);
}
