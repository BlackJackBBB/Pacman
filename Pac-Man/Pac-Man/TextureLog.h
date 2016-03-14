#pragma once
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <string>

class TextureLog {
public:

	// Constructor
	TextureLog();

	// Destructor
	~TextureLog();

	// Register texture with given file location and ID.
	// If same texture have been registred before increase number of users by one.
	TextureLog& registerTexture(const std::string location, unsigned textureId);

	// Deregister texure with given ID by decreasing number of users by one.
	// If texture have no user it is removed from log.
	TextureLog& deregisterTexture(unsigned textureId);

	// Return true if texture with given ID is registred.
	bool isTextureUsed(unsigned texutreId) const { return _logEntry.find(texutreId) != _logEntry.end(); }

	// Return true if texture from given file location is loaded.
	bool isTextureUsed(const std::string location) const { return std::find_if(_logEntry.begin(), _logEntry.end(), [&location](const std::pair<unsigned, std::pair<std::string, unsigned>>& entry) { return location == entry.second.first; }) != _logEntry.end(); }
	
	// Return ID of texture with given file location.
	unsigned getTextureId(const std::string location) const;

private:

	// Data members
	std::unordered_map<unsigned, std::pair<std::string, unsigned>> _logEntry;

};

