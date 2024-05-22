#include "BMPLoader.h"


BMPLoader::BMPLoader(const std::string &bmpFile) {
  m_textureID = _loadBMP(bmpFile);
}


BMPLoader::~BMPLoader() {
  LOGCHECK(glDeleteTextures(1, &m_textureID));
}

void BMPLoader::Bind() {
  LOGCHECK(glActiveTexture(GL_TEXTURE0));
  LOGCHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
}


GLuint BMPLoader::_loadBMP(const std::string &bmpFile) {
  GLuint textureID;

  if (!_checkFormat(bmpFile)) { return 0; }
  textureID = _accessImageData(bmpFile);

  return textureID;
}


/*
  * A BMP header is 54 bytes long.
  * It start with 'B' follwed by 'M' chars 
  * Color depth bit at offset 0x1C(28) and should be 24
  * Compression field bit at offset 0x1E(30) and should be 0
  * Image Data is at 0x0A(10) offset (can be deduced from BMP_HEADER_SIZE if missing)
  * Image Size is at 0x22(34) offset (can be computed from width and size if 0)
  * Image Width is at 0x12(18) offset
  * Image Height is at 0x16(22) offset
*/
bool BMPLoader::_checkFormat(const std::string &bmpFile) {

  int fileLength; 
  char header[BMP_HEADER_SIZE];

  for (char c : bmpFile) {
    if (!isalnum(c) && c != '_' && c != '.' && c != '/') {
        std::cerr << "Invalid character in bmp filename."<< std::endl;
        return false;
    }
  }

  if (bmpFile.length() < 5) {
    std::cerr << "Invalid bmp texture file, please use a correct name ending with '.bmp'." << std::endl;
    return false;
  }

  std::string ext = bmpFile.substr(bmpFile.length() - 4);
  if (ext.compare(".bmp") != 0 && ext.compare(".BMP") != 0) {
      std::cerr << "Invalid bmp file extension." << std::endl;
      return false;
  }

  // open file as binary + cursor at end
  std::ifstream file(bmpFile, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
      std::cerr << bmpFile << " could not be opened, check path and permissions." << std::endl;
      return false;
  }

  fileLength = file.tellg();

  if (fileLength < BMP_HEADER_SIZE) {
      std::cerr << "Not a correct BMP file, header is too short." << std::endl;
      return false;
  }

  file.seekg(0);
  file.read(header, BMP_HEADER_SIZE);

  if (header[0] != 'B' || header[1] != 'M') {
      std::cerr << "Not a correct BMP file, header must start with BM." << std::endl;
      return false;
  }

  int *bppPtr = reinterpret_cast<int*>(&header[0x1C]);
  if (*bppPtr != 24) {
      std::cerr << "Not a correct BMP file, wrong bpp value." << std::endl;
      return false;
  }

  int *compPtr = reinterpret_cast<int*>(&header[0x1E]);
  if (*compPtr != 0) {
      std::cerr << "Not a correct BMP file, wrong compression value." << std::endl;
      return false;
  }

  m_meta.dataPos = *(reinterpret_cast<int*>(&header[0x0A]));
  m_meta.imageSize = *(reinterpret_cast<int*>(&header[0x22]));
  m_meta.imageWidth = *(reinterpret_cast<int*>(&header[0x12]));
  m_meta.imageHeight = *(reinterpret_cast<int*>(&header[0x16]));

  if (m_meta.imageSize == 0)
    m_meta.imageSize = m_meta.imageWidth * m_meta.imageHeight * RGB;
  
  if (m_meta.dataPos == 0)
    m_meta.dataPos = BMP_HEADER_SIZE;

  file.close();
  return true;
}

GLuint BMPLoader::_accessImageData(const std::string &bmpFile) {

  std::ifstream file(bmpFile, std::ios::binary);
  GLuint textureID;
  char *dataBuffer;

  try {
    dataBuffer = new char[m_meta.imageSize];
  }
  catch (const std::bad_alloc& e) {
      std::cerr << "Error: Failed to allocate memory for data buffer. "
                << "Error message: " << e.what() << std::endl;
      return 0;
  }

  if (!file.is_open()) {
      std::cerr << bmpFile << " could not be opened, check path and permissions." << std::endl;
      return 0;
  }

  file.seekg(m_meta.dataPos);
  file.read(dataBuffer, m_meta.imageSize);

  if (!file) {
    std::cout << "error: only " << file.gcount() << " could be read";
    delete[] dataBuffer;
    return 0;
  }

  LOGCHECK(glGenTextures(1, &textureID));
  LOGCHECK(glBindTexture(GL_TEXTURE_2D, textureID));
  LOGCHECK(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m_meta.imageWidth, m_meta.imageHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, dataBuffer));

  delete[] dataBuffer;

  LOGCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  LOGCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)); 

  return textureID;
}

