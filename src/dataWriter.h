#include <vector>
#include <fstream>

#include "hex.h"

#ifndef __DATA_WRITER_H__
#define __DATA_WRITER_H__

string CSETTINGFILE = "setting.ini";

class DataWriter
{
private:
  int windowDimen [2];
  std::string terrainFile;
public:
  DataWriter();
  std::vector<terrainType*> readTerrainFile();
};

#endif