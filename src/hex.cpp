#include "hex.h"

terrainType::terrainType(std::string iName, int movementCost)
  : cName(iName), cMovementCost(movementCost)
{
  
}

hex::hex()
  : q(0), r(0)
{
  
}

hex::hex(int iQ, int iR, int iLevel, terrainType* iType)
  : q(iQ), r(iR), level(iLevel), cType(iType)
{

}

int hex::getQ() const
{
  return q;
}

int hex::getR() const
{
  return r;
}

int hex::getEnterCost(hex beginningHex) const
{
  int enterCost = 1;
  enterCost += abs(this->level - beginningHex.level);
  enterCost += this->cType->cMovementCost;
  return enterCost;
}

HexMap::HexMap()
  : data()
{
  ;
}

bool HexMap::addRow(hex firstHex)
{
  if (findHex(firstHex.getQ(), firstHex.getR()) != NULL)
    return false;
  std::vector<hex> newRow;
  newRow.push_back(firstHex);
  data.push_back(newRow);
  return true;
}

bool HexMap::addRow(std::vector<hex> newRow)
{
  for (unsigned i = 0; i < newRow.size(); i++)
    if (findHex(newRow[i].getQ(),newRow[i].getR()) != NULL)
      return false;
  data.push_back(newRow);
  return true;
}

bool HexMap::addHex(hex newHex)
{
  if (findHex(newHex.getQ(), newHex.getR()) != NULL)
    return false;
  std::vector<hex>* targetRow = findRow(newHex.getR());
  if (targetRow != NULL)
    targetRow->push_back(newHex);
  else
    addRow(newHex);
  return true;
}

hex* HexMap::findHex(int iQ, int iR)
{
  hex* targetHex = NULL;
  for (unsigned i = 0; i < data.size(); i++)
    {
      for (unsigned j = 0; j < data[i].size(); j++)
	{
	  if (data[i][j].getQ() == iQ && data[i][j].getR() == iR)
	    {
	      targetHex = &(data[i][j]);
	      return targetHex;
	    }
	}
    }
  return targetHex;
}

int HexMap::getNumRow()
{
  return data.size();
}

int HexMap::getColumnNumAtRow(int targetRow)
{
  if (targetRow >= data.size())
    return 0;
  return data[targetRow].size();
}

int HexMap::getNumHex()
{
  int numHex = 0;
  for (unsigned i = 0; i < data.size(); i++)
    numHex += data[i].size();
  return numHex;
}

std::vector<hex>* HexMap::findRow(int iR)
{
  for (unsigned i = 0; i < data.size(); i++)
    if (data[i].front().getR() == iR)
      return &(data[i]);
  return NULL;
}

bool operator==(const hex& lhs, const hex& rhs)
{
  if (lhs.getQ() == rhs.getQ() && lhs.getR() == rhs.getR())
    return true;
  return false;
}

bool operator!=(const hex& lhs, const hex& rhs)
{
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& out, const hex& obj)
{
  out << '(' << obj.getQ() << ',' << obj.getR() << ')';
  return out;
}

int main()
{
  terrainType* testType = new terrainType("test",1);
  HexMap iMap = HexMap();
  for (unsigned i = 0; i < 10; i++)
    {
      hex newHex = hex(0,i,0,testType);
      iMap.addHex(newHex);
    }
  for (unsigned i = 0; i < 5; i++)
    {
      hex newHex = hex(i,9,0,testType);
      iMap.addHex(newHex);
    }
  std::cout << "Map's row count: " << iMap.getNumRow() << std::endl;
  std::cout << "Map's hex count: " << iMap.getNumHex() << std::endl;
  return 0;
}
