#ifndef C_LOBES_H
#define C_LOBES_H

#include <c_MemoryCell.h>
#include <iostream>
extern bool Verbose;
using namespace std;
class c_Lobes
{
    public:
        c_Lobes();
        virtual ~c_Lobes();

    protected:

        c_MemoryCell LeftLobeMemory[30000];
        c_MemoryCell RightLobeMemory[30000];

    private:
        int LeftLobeUsageCount;
        int RightLobeUsageCount;
        int MAXCELLCOUNT;


    public:
        int GetLeftLobeUsageCount(){return LeftLobeUsageCount;}
        int GetRightLobeUsageCount(){return RightLobeUsageCount;}
        int GetBrainCellCount(){return LeftLobeUsageCount+RightLobeUsageCount;}

        void SetMemoryCellStringData(char LR, string strData, bool& Result){
            int TokenizedstrData;
            Result = false;
            TokenizedstrData = Tokenize(strData);
            if(TokenizedstrData <= (MAXCELLCOUNT-1)){
                if(LR == 'r'){
                    RightLobeMemory[TokenizedstrData].SetpCellDataString(strData);}}}

        bool GetBrainCellIsSet(char LR, int Location){
            if(LR == 'r'){
                return RightLobeMemory[Location].GetpIsSet();}
                else
                    return LeftLobeMemory[Location].GetpIsSet();}


        char GetBrainWordType(string strData, char Brainside)
           {
            char tmpWordType;
            int tmpToken;
            tmpToken = Tokenize(strData);
            if (Brainside == 'l'){
               tmpWordType = LeftLobeMemory[tmpToken].GetpWordType();}
            if (Brainside == 'r'){
               tmpWordType = RightLobeMemory[tmpToken].GetpWordType();
            }
            return tmpWordType;}


        void BrainSetWordType(string strData, char Brainside, char tmpWordType){
            int tmpToken;
            tmpToken = Tokenize(strData);
            if (Brainside == 'l'){
               LeftLobeMemory[tmpToken].SetpWordType(tmpWordType);
               }
            if (Brainside == 'r'){
               RightLobeMemory[tmpToken].SetpWordType(tmpWordType);
               } }


        bool CheckForKnownWord (string strData){                                                //currently right side only
            int tmpToken; tmpToken = Tokenize(strData);                                         //**TODO ensure force lower case searching
            if(RightLobeMemory[tmpToken].GetpCellDataString() == strData){
                return true;}
                else{
                    return false;}}


        void InstallNewWord(string NewWord, char WordType, char Purpose, string NewWordLC, bool Update=false){     //currently right side only
            if(Verbose)cout << "[c_Lobes.h::InstallNewWord]\n";
            int tmpToken;
            tmpToken = Tokenize(NewWord);
            if (tmpToken){
                    if(!(RightLobeMemory[tmpToken].GetpIsSet())){
                        RightLobeMemory[tmpToken].SetpCellDataString(NewWord);
                        RightLobeMemory[tmpToken].SetpWordType(WordType);
                        RightLobeMemory[tmpToken].SetpCellPurpose(Purpose);
                        RightLobeMemory[tmpToken].SetpCellDataLC(NewWordLC);
                        if(Verbose)
                            cout << "Storing -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << endl;

                        RightLobeUsageCount++;}

                    else
                        if(Update){
                            RightLobeMemory[tmpToken].SetpCellDataString(NewWord);
                            RightLobeMemory[tmpToken].SetpWordType(WordType);
                            RightLobeMemory[tmpToken].SetpCellPurpose(Purpose);
                            RightLobeMemory[tmpToken].SetpCellDataLC(NewWordLC);
                            if(Verbose)
                                cout << "Updating -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << endl;
                        }
                        else
                            if(Verbose)
                             cout << "Not Storing -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << endl;
            }
        }



        int Tokenize (string str_Data,bool ForceLowerCase = true)
        {
            int z;
            int y;
            int PlaceValue;
            int tmpToken;

                z = str_Data.size();
                PlaceValue = 1;
                tmpToken = 0;
                if(ForceLowerCase){
                for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(tolower(str_Data[y-1])))*PlaceValue;
                    PlaceValue ++;}}
                  else {
                    for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(str_Data[y-1]))*PlaceValue;
                    PlaceValue ++;}
                  }

            return tmpToken;

        }

    bool CheckLinkOfTwoNounsWithAdjectives(string FirstNoun,string SecondNoun, string& VerbUsage, string MatchedAdjective[], int& MatchedCount){


       VerbUsage           = "";
       for(int x = 0; x<15; x++) MatchedAdjective[x] = "";
       bool Result; Result = false;
       int FirstNounAdjectiveCount,SecondNounAdjectiveCount;
       int TokenFirstNoun,TokenSecondNoun,intVerbUsage,intMatchedAdjective;
       int AdjectiveMatches; AdjectiveMatches = 0;

       TokenFirstNoun           = Tokenize(FirstNoun);
       TokenSecondNoun          = Tokenize(SecondNoun);
       FirstNounAdjectiveCount  = RightLobeMemory[TokenFirstNoun].GetAdjectiveCount();
       SecondNounAdjectiveCount = RightLobeMemory[TokenSecondNoun].GetAdjectiveCount();

       if((FirstNounAdjectiveCount == 0) | (SecondNounAdjectiveCount == 0)){
          //can't match, no adjectives to compare
          //returns empty strings and false.
          }
       else{
          for(int x = 0; x < FirstNounAdjectiveCount; x++){
            for(int y = 0; y < SecondNounAdjectiveCount; y++){
                if(RightLobeMemory[TokenFirstNoun].GetAdjective(x) == RightLobeMemory[TokenSecondNoun].GetAdjective(y)){
                    Result                                = true;
                    intMatchedAdjective                   = RightLobeMemory[TokenFirstNoun].GetAdjective(x);
                    MatchedAdjective[AdjectiveMatches]    = RightLobeMemory[intMatchedAdjective].GetpCellDataString();
                    intVerbUsage                          = RightLobeMemory[TokenFirstNoun].GetVerbWithAdjective(x,1);
                    VerbUsage                             = RightLobeMemory[intVerbUsage].GetpCellDataString();
                    AdjectiveMatches++;}
            } } }
          MatchedCount = AdjectiveMatches;
          return Result;
    }


    void SavePreAndPostPatternConstruction(string PreConstructionPattern,string PostConstructionPattern){

        int PreToken  = Tokenize(PreConstructionPattern,false);
        int PostToken = Tokenize(PostConstructionPattern,false);

        LeftLobeMemory[PreToken].SetpCellDataString(PreConstructionPattern);
        LeftLobeMemory[PreToken].SetpCellPurpose('1');    // pattern storage
        LeftLobeMemory[PreToken].SetpToken(PreToken);
        LeftLobeMemory[PreToken].SetPointerToNextPattern(PostToken);

        LeftLobeMemory[PostToken].SetpCellDataString(PostConstructionPattern);
        LeftLobeMemory[PostToken].SetpCellPurpose('1');    //pattern storage
        LeftLobeMemory[PostToken].SetpToken(PostToken);
        LeftLobeMemory[PostToken].SetPointerToNextPattern(PostToken);

        LeftLobeUsageCount += 2;
    }

    int L_GetNumberOfAdjectivesInMap(int CellAddress){return RightLobeMemory[CellAddress].GetNumberOfAdjectivesInMap();}
    int L_GetNumberOfVerbsInMap(int CellAddress){return RightLobeMemory[CellAddress].GetNumberOfVerbsInMap();}
    int L_GetNumberOfAdverbsInMap(int CellAddress){return RightLobeMemory[CellAddress].GetNumberOfAdverbsInMap();}
    int L_GetNumberOfRelatedNounsInMap(int CellAddress){return RightLobeMemory[CellAddress].GetNumberOfRelatedNounsInMap();}
    void L_AssociateAdjectiveInMap(string AdjectiveToAssociate,int CellAddress){RightLobeMemory[CellAddress].AssociateAdjectiveInMap(AdjectiveToAssociate);}
    void L_AssociateVerbToAdjectiveInMap(string AdjectiveToAssociate, string VerbToAssociate,int CellAddress){RightLobeMemory[CellAddress].AssociateVerbToAdjectiveInMap(AdjectiveToAssociate, VerbToAssociate);}
    void L_AssociateAdverbToVerbInMap(string AdverbToAssociate,string VerbToAssociate,int CellAddress){RightLobeMemory[CellAddress].AssociateAdverbToVerbInMap( AdverbToAssociate,VerbToAssociate);}
    string L_GetAdjective(int CellAddress,int Location){
         int AdjectiveToken = RightLobeMemory[CellAddress].GetAdjectiveFromMap(Location);
          return RightLobeMemory[AdjectiveToken ].GetpCellDataLC(); }

    string L_GetVerb(int CellAddress,int Location){
         int VerbToken = RightLobeMemory[CellAddress].GetVerbFromMap(Location);
          return RightLobeMemory[VerbToken].GetpCellDataLC(); }

    string L_GetAdverb(int CellAddress,int Location){
         int AdverbToken = RightLobeMemory[CellAddress].GetAdverbFromMap(Location);
          return RightLobeMemory[AdverbToken].GetpCellDataLC(); }

    void L_AssociateNounToNoun(string BaseNoun, string RelatedNoun){
         RightLobeMemory[Tokenize(BaseNoun)].AssociateNounInMap(RelatedNoun);}

    bool L_CheckForRelatedNoun(string BaseNoun, string NounToCheck){
         return RightLobeMemory[Tokenize(BaseNoun)].IsNounRelatedToMe(NounToCheck);}

    string L_GetRelatedNoun(int CellAddress,int Location){
         int NounToken = RightLobeMemory[CellAddress].GetNounFromMap(Location);
          return RightLobeMemory[NounToken].GetpCellDataLC(); }

};

#endif // C_LOBES_H
