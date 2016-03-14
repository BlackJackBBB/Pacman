#pragma once
#include <map>
#include <vector>
#include <array>
#include <fstream>
#include "Coordinate.h"
#include "Texture.h"


class Model {
public:

	// Construct model from given file location. 
	// If location is vaild exception occur.
	Model(std::string location);

	// Destructor
	~Model();

	// Get reference to polygons container.
	const std::vector<std::array<unsigned, 4>>& getPolygons() const { return _polygons; }

	// Get reference to specified vertex coordinate.
	const Coordinate<int>& getVertexCoordinate(unsigned ordinal) const { return _vertexCoordinates.at(ordinal); }

	// Get reference to specified texture coordinate.
	const Coordinate<float>& getTextureCoordinate(unsigned ordinal) const { return _textureCoordinates.at(ordinal); }

	// Get reference to texture.
	const Texture& getTexture() const { return *_texture; }

	// Get models's name.
	std::string getName() const { return _name; }

private:

	// Data members
	std::string _name;
	Texture* _texture;
	std::map<unsigned, Coordinate<int>> _vertexCoordinates;
	std::map<unsigned, Coordinate<float>> _textureCoordinates;
	std::vector<std::array<unsigned, 4>> _polygons;

};

