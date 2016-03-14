#pragma once
#include <GL\freeglut.h>
#include <string>
#include <map>
#include <fstream>

class TextureLog;

class Texture {
public:

	// Construct texture from given file location with or without alpha channel.
	// If file location isn't set texture won't be loaded.
	Texture(const std::string location = "", const bool alphaChannel = false);

	// Destructor
	~Texture();

	// Load bitmap (.bmp) from given file location.
	// If bitmap contain alpha channel the parameter alphaChannel must be set true.
	Texture& loadBmp(const std::string location, const bool alphaChannel = false);

	// Get texture's ID.
	unsigned getId() const { return _id; }

private:

	// Data members
	unsigned _id;
	unsigned _width;
	unsigned _height;
	unsigned char* _pixels;
	static TextureLog _log;


	// Decode bitmap image (RGB or RGBA) from file location and store image bits in array _pixels.
	bool decodeBmp(std::ifstream&, const bool);

	// Upload loaded bitmap like texture on OpenGL (graphic procesor) with given parameters.
	void uploadBmp(const bool);

};

