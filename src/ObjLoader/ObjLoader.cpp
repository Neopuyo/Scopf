#include "ObjLoader.h"


ObjLoader::ObjLoader() {

}

ObjLoader::~ObjLoader() {

}

void ObjLoader::loadOBJ(const std::string &filepath, 
              std::vector<glm::vec3> &vertices, 
              std::vector<glm::vec2> &uvs,
              std::vector<glm::vec3> &normals,
              ft_glm::vec3 &maxs,
              ft_glm::vec3 &mins) const {

  // [!][+] parse les caract spe + fini en .obj

  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> temp_vertices; 
  std::vector<glm::vec2> temp_uvs;
  std::vector<glm::vec3> temp_normals;

  // float minX, minY, minZ, maxX, maxY, maxZ;
  bool isFirstVertex = true;

  std::ifstream stream(filepath);
  if (!stream.is_open()) {
    throw FileNotFound();
  }

  unsigned int fSlotSize;
  
  try {
    fSlotSize = _getFSlotSize(filepath);
  } catch (std::exception &e) {
    std::cout << "_getFSlotSize  raised except" << std::endl;
    throw e;
  }

  std::string line;

  while(std::getline(stream, line)) {
    std::istringstream iss(line);
    std::string header;
    
    iss >> header; // the first 'word' of line goes into header
    if (header == "v") {
      // [!][+] TODO: extract v part
      ft_glm::vec3 vertex;
      iss >> vertex.x >> vertex.y >> vertex.z;
      if (isFirstVertex) {
        maxs = vertex;
        mins = vertex;
        isFirstVertex = false;
      } else {
        if (vertex.x < mins.x)
          mins.x = vertex.x;
        if (vertex.y < mins.y)
          mins.y = vertex.y;
        if (vertex.z < mins.z)
          mins.z = vertex.z;

        if (vertex.x > maxs.x)
          maxs.x = vertex.x;
        if (vertex.y > maxs.y)
          maxs.y = vertex.y;
        if (vertex.z > maxs.z)
          maxs.z = vertex.z;
      }
      temp_vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
    } else if (header == "vt") {
      glm::vec2 uv;
      iss >> uv.x >> uv.y;
      temp_uvs.push_back(uv);
    } else if (header == "vn") {
      glm::vec3 normal;
      iss >> normal.x >> normal.y >> normal.z;
      temp_normals.push_back(normal);
    } else if (header == "f") {
      FaceType type = _getFType(line);
  
      if (type == FaceType::TRIANGLE)
        _parseFLineFromTriangle(fSlotSize, line, vertexIndices, uvIndices, normalIndices);
      else 
        _parseFLineFromSquare(fSlotSize, line, vertexIndices, uvIndices, normalIndices);

    } else {
      // the line is skip, considered as comment
    }
  }
    // Now process the indices and build the final vertex, uv and normal vectors
    // For each vertex of each triangle
    std::cout << "vertexIndices.size() = " << vertexIndices.size() << std::endl;
    std::cout << "temp_vertices.size() = " << temp_vertices.size() << std::endl;
    std::cout << "temp_uvs.size() = " << temp_uvs.size() << std::endl;
    std::cout << "temp_normals.size() = " << temp_normals.size() << std::endl;


    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        vertices.push_back(vertex);
        if (fSlotSize < 2) { continue; }

        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        uvs.push_back(uv);
        if (fSlotSize < 3) { continue; }

        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex - 1];
        normals.push_back(normal);
    }

  // _checkVertices(vertices, uvs, normals); // [!] Debug only

}

// To get which format is used for f line : v or v/vt or v/vt/vn
// our parsing accept files with only 3 or 4 vertex per f line
unsigned int ObjLoader::_getFSlotSize(const std::string &filepath) const {
std::ifstream stream(filepath);
  if (!stream.is_open()) {
    throw FileNotFound();
  }

  std::string line;
  unsigned int size = 0;
  bool sizeSet = false;

  while(std::getline(stream, line)) {
    std::istringstream iss(line);
    std::string header;
    std::vector<std::string> tokens;
    std::vector<std::string> slot1, slot2, slot3;


    iss >> header; // the first 'word' of line goes into header
    if (header == "f") {
      tokens = _split(line, ' ');
       if (tokens.size() != 4 && tokens.size() != 5) { throw ErrorF(); } 

       slot1 = _split(tokens[1], '/');
       slot2 = _split(tokens[2], '/');
       slot3 = _split(tokens[3], '/');

       if (slot1.size() != slot2.size() || slot1.size() != slot3.size()) { throw ErrorF(); }
       if (slot1.size() == 0 || slot1.size() > 3) { throw ErrorF(); }

       if (sizeSet) {
        if (slot1.size() != size) { throw ErrorF(); }
       } else {
        sizeSet = true;
        size = slot1.size();
       }
    }
  }

  if (!sizeSet) { throw ErrorF(); }
  return size;
}

// Does f line represent a square or triangle
// need to be called after _getFSlotSize() to ensure size is 4 or 5 only 
// the header 'f' is included in size
ObjLoader::FaceType ObjLoader::_getFType(const std::string &line) const {
  std::vector<std::string> tokens;

  tokens = _split(line, ' ');

  return tokens.size() == 4 ? FaceType::TRIANGLE : FaceType::SQUARE ;
}

void ObjLoader::_parseFLineFromTriangle(unsigned int size, const std::string &line, std::vector<unsigned int> &vertexIndices, 
std::vector<unsigned int> &uvIndices, std::vector<unsigned int> &normalIndices) const {

      std::vector<std::string> tokens = _split(line, ' ');
      if (tokens.size() != 4 && tokens.size() != 5) { throw ErrorF(); }

      std::vector<std::string> slot1 = _split(tokens[1], '/');
      std::vector<std::string> slot2 = _split(tokens[2], '/');
      std::vector<std::string> slot3 = _split(tokens[3], '/');


      if (slot1.size() != size || slot2.size() != size || slot3.size() != size) { 
        std::cout << "[ErrorParsing] slot1or2or3.size() != size of f" << std::endl;
        throw ErrorF(); 
      }

      vertexIndices.push_back(std::stoi(slot1[0]));
      vertexIndices.push_back(std::stoi(slot2[0]));
      vertexIndices.push_back(std::stoi(slot3[0]));
      if (size < 2) { return; }

      uvIndices.push_back(std::stoi(slot1[1]));
      uvIndices.push_back(std::stoi(slot2[1]));
      uvIndices.push_back(std::stoi(slot3[1]));
      if (size < 3) { return; }

      normalIndices.push_back(std::stoi(slot1[2]));
      normalIndices.push_back(std::stoi(slot2[2]));
      normalIndices.push_back(std::stoi(slot3[2]));
}

void ObjLoader::_parseFLineFromSquare(unsigned int size, const std::string &line, std::vector<unsigned int> &vertexIndices, 
std::vector<unsigned int> &uvIndices, std::vector<unsigned int> &normalIndices) const {

  std::vector<std::string> tokens;
  tokens = _split(line, ' ');

  if (tokens.size() == 5) {
    std::string line1 = "f ";
    std::string line2 = "f ";

    line1 += tokens[1] + " " + tokens[2] + " " + tokens[3];
    line2 += tokens[1] + " " + tokens[3] + " " + tokens[4];

    _parseFLineFromTriangle(size, line1, vertexIndices, uvIndices, normalIndices);
    _parseFLineFromTriangle(size, line2, vertexIndices, uvIndices, normalIndices);
  }
}


std::vector<std::string> ObjLoader::_split(const std::string &str, char delimiter) const {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        if (token.size() > 0)
          tokens.push_back(token);
    }
    return tokens;
}

void ObjLoader::_checkVertices(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uvs, const std::vector<glm::vec3> &normals) const {
  std::cout << "--- Vertices (" << vertices.size() << ")" << std::endl;
  for (const auto &vertex : vertices) {
      std::cout << "  " << vertex.x << ", " << vertex.y << ", " << vertex.z << std::endl;
  }

  std::cout << "--- UVs(" << uvs.size() << ")" << std::endl;
  for (const auto &uv : uvs) {
      std::cout << "  " << uv.x << ", " << uv.y << std::endl;
  }

  std::cout << "--- Normals(" << normals.size() << ")" << std::endl;
  for (const auto &normal : normals) {
      std::cout << "  " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
  }
  
}

const char *ObjLoader::FileNotFound::what() const throw() {
  return ("File not found");
}

const char *ObjLoader::ErrorParsing::what() const throw() {
  return ("File is not correctly formated");
}

const char *ObjLoader::ErrorF::what() const throw() {
  return ("File has an incorrect f line");
}

// ------------------------------------------

std::ostream &operator<<(std::ostream &o, const ObjLoader::FaceType &righty) {
  if (righty == ObjLoader::FaceType::TRIANGLE)
    o << "TRIANGLE";
  else if (righty == ObjLoader::FaceType::SQUARE)
    o << "SQUARE";
  else
    o << "ERROR FACE TYPE";
  return o;
}

