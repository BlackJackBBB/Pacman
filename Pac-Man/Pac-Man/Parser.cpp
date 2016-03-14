#include "Parser.h"
#include "Box.h"


Parser::Parser() {}


Parser::~Parser() {}


std::vector<std::string> split(const std::string& string, const std::string& delim, const bool keepEmpty) {
	std::vector<std::string> result;
	if (delim.empty()) {
		result.push_back(string);
		return result;
	}
	std::string::const_iterator substart = string.begin(), subend;
	while (true) {
		subend = std::search(substart, string.end(), delim.begin(), delim.end());
		std::string temp(substart, subend);
		if (keepEmpty || !temp.empty()) {
			result.push_back(temp);
		}
		if (subend == string.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}


template<class T>
std::ifstream& operator>> (std::ifstream& file, Coordinate<T>& coordinate) {
	T x, y;

	file >> x >> y;
	coordinate.setX(x).setY(y);

	return file;
}


std::ifstream& operator>> (std::ifstream& file, Box& box) {
	std::string type;
	
	file >> type;
	if (type != "pp") exit(1); //exception
	Coordinate<int> pp;
	file >> pp;
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	file >> type;
	if (type != "w") exit(1); //exception
	unsigned w;
	file >> w;
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	file >> type;
	if (type != "h") exit(1); //exception
	unsigned h;
	file >> h;
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	box.setPivotPoint(pp).setWidth(w).setHeight(h);
	return file;
}


Parser& Parser::parseObject(std::ifstream& file, std::string& name, int& width, int& height, std::vector<Box>& boundingBoxes, std::vector<std::string>& animationsPaths) {
	using namespace std;

	string line;
	while (getline(file, line)) {
		vector<string> lineParts = split(line, " ");

		if (lineParts[0] != "#" && lineParts[0] != "\n") exit(1);   //exception

		if (lineParts[1] == "object_name") {
			getline(file, name);
		}
		else if (lineParts[1] == "width") {
			file >> width;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (lineParts[1] == "height") {
			file >> height;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (lineParts[1] == "bounding_boxes") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string ordinal;
				getline(file, ordinal);

				Box box;
				file >> box;
				boundingBoxes.push_back(box);
			}
		}
		else if (lineParts[1] == "animations_paths") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string path;
				getline(file, path);
				animationsPaths.push_back(path);
			}
		}
		else exit(1);     //exception
	}

	return *this;
}


Parser& Parser::parseModel(std::ifstream& file, std::string& name, std::string& texturePath, std::map<unsigned, Coordinate<int>>& vertices, std::map<unsigned, Coordinate<float>>& textureCoords, std::vector<std::array<unsigned, 4>>& polygons) {
	using namespace std;

	string line;
	while (getline(file, line)) {
		vector<string> lineParts = split(line, " ");

		if (lineParts[0] != "#" && lineParts[0] != "\n") exit(1);   //exception

		if (lineParts[1] == "model_name") {
			getline(file, name);
		}
		else if (lineParts[1] == "texture_path") {
			getline(file, texturePath);
		}
		else if (lineParts[1] == "vertices") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string type;
				file >> type;
				if (type != "v") exit(1); //exception

				Coordinate<int> vertice;
				file >> vertice;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				vertices[i + 1] = vertice;
			}
		}
		else if (lineParts[1] == "texture_coords") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string type;
				file >> type;
				if (type != "vt") exit(1); //exception

				Coordinate<float> coordVertice;
				file >> coordVertice;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				textureCoords[i + 1] = coordVertice;
			}
		}
		else if (lineParts[1] == "polygons") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string type;
				file >> type;
				if (type != "f") exit(1);   //exception

				unsigned a, b, c, d;
				file >> a >> b >> c >> d;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				std::array<unsigned, 4> temp = { a, b, c, d };
				polygons.push_back(temp);
			}
		}
		else exit(1); //exception
	}

	return *this;
}


Parser& Parser::parseMaze(std::ifstream& file, std::string& name, int& width, int& height, std::vector<std::pair<std::string, Coordinate<int>>>& staticObjects, std::vector<std::pair<std::string, Coordinate<int>>>& pallets, std::vector<std::pair<std::string, Coordinate<int>>>& powerPallets, std::unordered_map<std::string, Coordinate<int>>& objectsInfo) {
	using namespace std;

	string line;
	while (getline(file, line)) {
		vector<string> lineParts = split(line, " ");

		if (lineParts[0] != "#" && lineParts[0] != "\n") exit(1);   //exception

		if (lineParts[1] == "maze_name") {
			getline(file, name);
		}
		else if (lineParts[1] == "width") {
			file >> width;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (lineParts[1] == "height") {
			file >> height;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (lineParts[1] == "pallets") {
			string location;
			getline(file, location);

			unsigned nLine;
			file >> nLine;
			for (unsigned i = 0; i < nLine; i++) {
				string type;
				file >> type;
				if (type != "pp") exit(1);      //exception

				Coordinate<int> point;
				file >> point;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				pallets.push_back(make_pair(location, point));
			}
		}
		else if (lineParts[1] == "power_pallets") {
			string location;
			getline(file, location);

			unsigned nLine;
			file >> nLine;
			for (unsigned i = 0; i < nLine; i++) {
				string type;
				file >> type;
				if (type != "pp") exit(1);      //exception

				Coordinate<int> point;
				file >> point;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				powerPallets.push_back(make_pair(location, point));
			}
		}
		else if (lineParts[1] == "static_objects") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string ordinal;
				getline(file, ordinal);

				string location;
				getline(file, location);

				string type;
				file >> type;
				if (type != "pp") exit(1); //exception

				Coordinate<int> point;
				file >> point;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				staticObjects.push_back(make_pair(location, point));
			}
		}
		else if (lineParts[1] == "objects_info") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string ordinal;
				getline(file, ordinal);

				string objectName;
				getline(file, objectName);

				string type;
				file >> type;
				if (type != "pp") exit(1); //exception

				Coordinate<int> point;
				file >> point;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				objectsInfo.emplace(objectName, point);
			}
		}
	}

	return *this;
}


Parser& Parser::parseAnimation(std::ifstream& file, std::string& name, std::vector<std::string>& modelsPaths) {
	using namespace std;

	string line;
	while (getline(file, line)) {
		vector<string> lineParts = split(line, " ");

		if (lineParts[0] != "#" && lineParts[0] != "\n") exit(1);   //exception

		if (lineParts[1] == "animation_name") {
			getline(file, name);
		}
		else if (lineParts[1] == "models_paths") {
			unsigned nLine;
			file >> nLine;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (unsigned i = 0; i < nLine; i++) {
				string path;
				getline(file, path);
				modelsPaths.push_back(path);
			}
		}
		else exit(0);       //exception
	}

	return *this;
}

Parser& Parser::parseConfigurationFile(std::ifstream& file, int& resolutionWidth, int& resolutionHeight) {
	using namespace std;

	string line;
	while (getline(file, line)) {
		vector<string> lineParts = split(line, "=", false);

		if (lineParts[0] == "resolutionWidth") {
			resolutionWidth = stoi(lineParts[1]);
		}
		else if (lineParts[0] == "resolutionHeight") {
			resolutionHeight = stoi(lineParts[1]);
		}
	}

	return *this;
}