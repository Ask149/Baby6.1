#include "c_MemoryCell.h"

c_MemoryCell::c_MemoryCell()
{
    //ctor
    pCellData = "";
    pCellDataLC = "";
    pCellPurpose = 'u'; //undefined
    pWordType    = 'u';
    pIsRoot = false;
    pNextVerb = 0;
    pNextNoun = 0;
    pToken = 0;
    pIsSet = false;
    GenderClass = 'n';
    SecondaryType = 'u';
    AlternateType = 'u';
    for(int x = 0; x < 15; x++){
            AdjectiveList[x][0]=0;
            AdjectiveList[x][1]=0;
            AdjectiveList[x][2]=0;
            AdjectiveList[x][3]=0;}
    AdjectiveCount = 0;
    advDescriptors.clear();
    verbDescriptors.clear();
    adjDescriptors.clear();
    PointerToNextPattern = 0;
}

c_MemoryCell::~c_MemoryCell()
{
    //dtor
}
