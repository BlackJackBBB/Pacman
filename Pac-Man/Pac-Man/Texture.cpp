#include "Texture.h"
#include "TextureLog.h"


Texture::Texture(const std::string location, const bool alphaChannel) :
	_id(0),
	_width(-1),
	_height(-1)
{
	if (location != "") {
		loadBmp(location, alphaChannel);
	}
}


Texture::~Texture() {
	_log.deregisterTexture(_id);
	if (!_log.isTextureUsed(_id)) glDeleteTextures(1, &_id);
}


Texture& Texture::loadBmp(const std::string location, const bool alphaChannel) {
	std::ifstream file(location, std::ios::binary);
	if (!file) exit(1);													//exception

	_id = _log.getTextureId(location);
	if (_id == 0) {
		if (!decodeBmp(file, alphaChannel)) exit(1);						//exception

		if (alphaChannel) uploadBmp(alphaChannel);
		else uploadBmp(!alphaChannel);

		delete[] _pixels;
		file.close();
	}
	_log.registerTexture(location, _id);

	return *this;
}


bool Texture::decodeBmp(std::ifstream& file, const bool alphaChannel) {
	unsigned char* dataBuff[] = { nullptr, nullptr };
	dataBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
	dataBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

	file.read((char*)dataBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)dataBuff[1], sizeof(BITMAPINFOHEADER));

	BITMAPFILEHEADER* bmpHeader = (BITMAPFILEHEADER*)dataBuff[0];
	BITMAPINFOHEADER* bmpInfo = (BITMAPINFOHEADER*)dataBuff[1];

	if (bmpHeader->bfType != 0x4D42) {
		return false;															
	}

	_pixels = new unsigned char[bmpInfo->biSizeImage];

	file.seekg(bmpHeader->bfOffBits, std::ios::beg);
	file.read((char*)_pixels, bmpInfo->biSizeImage);

	if (_pixels == nullptr) return false;	


	//swaping blue and red channel
	unsigned char tmpRGB = 0;
	if (alphaChannel) {
		for (unsigned long i = 0; i < bmpInfo->biSizeImage - 4; i += 4) {
			tmpRGB = _pixels[i];
			_pixels[i] = _pixels[i + 2];
			_pixels[i + 2] = tmpRGB;
		}
	}
	else {
		for (unsigned long i = 0; i < bmpInfo->biSizeImage - 3; i += 3) {
			tmpRGB = _pixels[i];
			_pixels[i] = _pixels[i + 2];
			_pixels[i + 2] = tmpRGB;
		}
	}

	_width = bmpInfo->biWidth;
	_height = bmpInfo->biHeight;

	delete[] dataBuff[0];
	delete[] dataBuff[1];

	return true;
}


void Texture::uploadBmp(const bool alphaChannel) {
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (alphaChannel) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);
	else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _pixels);

	glBindTexture(GL_TEXTURE_2D, NULL);
}


TextureLog Texture::_log;
