#include "Model.h"
#include "Parser.h"


Model::Model(std::string location) {
	std::ifstream file(location);

	if (!file) exit(1);             //exception

	Parser parser;
	std::string texturePath;
	parser.parseModel(file, _name, texturePath, _vertexCoordinates, _textureCoordinates, _polygons);

	_texture = new Texture(texturePath, true);

	file.close();
}


Model::~Model() {
	delete _texture;
}
