#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "glad.h"
#include <GLFW/glfw3.h>
#include "errorHandling.h"

#include <ft_glm.h>

class ObjLoader
{
  public:
    ObjLoader();
    ~ObjLoader();

     enum class FaceType {
        TRIANGLE,
        SQUARE
    };

    class FileNotFound : public std::exception {
      public :
       virtual const char *what() const throw();
    };

    class ErrorParsing : public std::exception {
      public :
       virtual const char *what() const throw();
    };

    class ErrorF : public std::exception {
      public :
       virtual const char *what() const throw();
    };

    void loadOBJ(const std::string &filepath, 
         std::vector<ft_glm::vec3> &vertices, 
         std::vector<ft_glm::vec2> &uvs,
         std::vector<ft_glm::vec3> &normals,
              ft_glm::vec3 &maxs,
              ft_glm::vec3 &mins) const;

  private:


    std::vector<std::string> _split(const std::string &str, char delimiter) const;
    void _checkVertices(const std::vector<ft_glm::vec3> &vertices, const std::vector<ft_glm::vec2> &uvs, const std::vector<ft_glm::vec3> &normals) const;

    void _parseV(ft_glm::vec3 &vertex, std::vector<ft_glm::vec3> &temp_vertices, ft_glm::vec3 &maxs, ft_glm::vec3 &mins) const;

    void _parseFLineFromTriangle(unsigned int size, const std::string &line, std::vector<unsigned int> &vertexIndices, 
std::vector<unsigned int> &uvIndices, std::vector<unsigned int> &normalIndices) const;

    void _parseFLineFromSquare(unsigned int size, const std::string &line, std::vector<unsigned int> &vertexIndices, 
std::vector<unsigned int> &uvIndices, std::vector<unsigned int> &normalIndices) const;

    unsigned int _getFSlotSize(const std::string &filepath) const;
    FaceType _getFType(const std::string &line) const;

};


// --------------------

std::ostream &operator<<(std::ostream &o, const ObjLoader::FaceType &righty);


