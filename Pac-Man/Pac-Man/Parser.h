#pragma once
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include "Coordinate.h"
#include "Window.h"

class Box;

class Parser {
public:

	// Constructor.
	Parser();

	// Destructor.
	~Parser();

	// Parse object from file (.pob) and load it's name, width, height, bunding boxes and file paths to animations.
	Parser& parseObject(std::ifstream& file, std::string& name, int& width, int& height, std::vector<Box>& boundingBoxes, std::vector<std::string>& animationsPaths);

	// Parse model from file and load it's name, path to texture, vertices, texture coordinates and polygons.
	Parser& parseModel(std::ifstream& file, std::string& name, std::string& texturePath, std::map<unsigned, Coordinate<int>>& vertices, std::map<unsigned, Coordinate<float>>& textureCoords, std::vector<std::array<unsigned, 4>>& polygons);

	// Parse maze from file and load it's name,
	// width, height, paths to static objects and their position (pivot point),
	// paths to pallets and their pivot point,
	// paths to power pallets and their pivot point,
	// info about soame objects and their initial position in the maze. 
	Parser& parseMaze(std::ifstream& file, std::string& name, int& width, int& height, std::vector<std::pair<std::string, Coordinate<int>>>& staticObjects, std::vector<std::pair<std::string, Coordinate<int>>>& pallets, std::vector<std::pair<std::string, Coordinate<int>>>& powerPallets, std::unordered_map<std::string, Coordinate<int>>& objectsInfo);

	// Parse animation from file and load it's name and paths to models.
	Parser& parseAnimation(std::ifstream& file, std::string& name, std::vector<std::string>& modelsPaths);

	Parser& parseConfigurationFile(std::ifstream& file, int& resolutionWidth, int& resolutionHeight);
};


// Split string by specified delim into vector of substrings.
// With parameter keepEmpty choose if you want to keep empty substring in a case where there is no characters after delim.
std::vector<std::string> split(const std::string& string, const std::string& delim, const bool keepEmpty = true);


// Read box object from fromated file.
std::ifstream& operator>> (std::ifstream&, Box&);


// Read coordinate from formated file.
template<class T>
std::ifstream& operator>> (std::ifstream&, Coordinate<T>&);