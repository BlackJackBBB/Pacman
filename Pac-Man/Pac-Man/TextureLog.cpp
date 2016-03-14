#include "TextureLog.h"


TextureLog::TextureLog() {}


TextureLog::~TextureLog() {}


TextureLog& TextureLog::registerTexture(const std::string location, unsigned textureId) {
	if (textureId == 0) return *this;             //mozda stavim exception

	auto entry = _logEntry.find(textureId);

	if (entry == _logEntry.end()) _logEntry.emplace(textureId, std::make_pair(location, 1));
	else std::get<1>(entry->second)++;

	return *this;
}


TextureLog& TextureLog::deregisterTexture(unsigned textureId) {
	auto entry = _logEntry.find(textureId);

	if (entry != _logEntry.end()) {
		if (std::get<1>(entry->second) == 1) _logEntry.erase(entry);
		else std::get<1>(entry->second)--;
	}
	
	return *this;
}


unsigned TextureLog::getTextureId(const std::string location) const {
	const auto it = std::find_if(_logEntry.begin(), _logEntry.end(), [&](const std::pair<unsigned, std::pair<std::string, unsigned>>& entry) { return location == entry.second.first; });
	if (it != _logEntry.end()) return it->first;
	else return 0;
}