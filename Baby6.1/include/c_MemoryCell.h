#ifndef C_MEMORYCELL_H
#define C_MEMORYCELL_H
#include <string>

using namespace std;
class c_MemoryCell
{
    public:
        c_MemoryCell();
        virtual ~c_MemoryCell();

    protected:

    private:
        string pCellData;          // the raw data
        string pCellDataLC;        // raw data in lower case
        string GivenName;          // if this noun or proper noun has a given name
        char pCellPurpose;         // s-sentence w-word r-response m-memory
        char pWordType;            // n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                   // n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object I(LC) Indirect object
                                   // s - plural possessive  X(cap) Directive j-joining word
                                   // initialize to 'u'
                                   // the decision on this word type is made elsewhere
        char SecondaryType;        // Could be used as another type i.e. light-n light red - A box is light -a
        char AlternateType;        // some words without modification could have a third type (All type references conform to pWordType definitions)
        char GenderClass;          // n - neutral e- either m - male only f - female only u - undefined
        bool pIsRoot;              // the root of a word
        bool pIsSet;               // Has been set with data before
        int  pNextVerb;            // pointer to next verb
        int  pNextNoun;            // pointer to next noun
        int  AdjectiveList[15][4]; // points to linked adjectives with verbs [0][0] = Adjective [0][1]..[0][3] = verbs
        int  AdjectiveCount;       // the number of adjectives here
        int  pToken;               // the token value of this data



    public:
        int    GetAdjectiveCount(){return AdjectiveCount;}
        char   GetSecondaryType(){return SecondaryType;}
        void   SetSecondaryType(char Type){SecondaryType = Type;}
        char   GetAlternateType(){return AlternateType;}
        void   SetAlternateType(char Type){AlternateType = Type;}
        string GetpCellDataString(){return pCellData;}
        string GetpCellDataLC(){return pCellDataLC;}
        void   SetpCellDataLC(string newData){pCellDataLC=newData;}
        char   GetpCellPurpose(){return pCellPurpose;}
        void   SetpCellPurpose (char NewData){pCellPurpose = NewData;}
        char   GetpWordType(){return pWordType;}
        void   SetpWordType(char NewData){pWordType = NewData;}
        bool   GetpIsRoot(){return pIsRoot;}
        void   SetpIsRoot(bool NewVal){pIsRoot = NewVal;}
        int    GetpNextVerb(){return pNextVerb;}
        void   SetpNextVerb(int NewVal){pNextVerb = NewVal;}
        int    GetpNextNoun(){return pNextNoun;}
        void   SetpToken(int NewVal){pToken=NewVal;}
        int    GetpToken(){return pToken;}
        bool   GetpIsSet() {return pIsSet;}
        void   SetGenderClass(char NewClass){GenderClass = NewClass;}
        char   GetGenderClass(){return GenderClass;}
        string GetGivenName(){return GivenName;}
        void   SetGivenName(string NewName){GivenName = NewName;}

        void SetpCellDataString(string NewData){
            pCellData = NewData;
            pIsSet = true;}


        void AccociateAdjective(int NewAdjective){                  //Stores New Tokenized Adjective at the end of the list
            int EndList; EndList = -1;
            int Matched; Matched = -1;
            for(int x =0; x <15; x++){
                if((AdjectiveList[x][0]==0) & (EndList == -1)){
                     EndList = x;}                                   //mark first occurrence of 0
                if(AdjectiveList[x][0] == NewAdjective)
                    Matched = x;
                    }
            if(!(Matched >=0))
               AdjectiveList[EndList][0]=NewAdjective;

            AdjectiveCount = EndList+1;

         }
         //-----END ACCOCIATEADJECTIVE----------------------------


        int GetAdjective(int Location){return AdjectiveList[Location][0];}

        int GetVerbWithAdjective(int AdjectiveLocation, int VerbLocation){
             return AdjectiveList[AdjectiveLocation][VerbLocation];}

        void AccociateAdjectiveWithVerb(int NewVerb,int AdjectiveToAssociate){  //Stores New Tokenized VERB with Tokenized Adjective at the end of the list 1,2,3
            int EndList;  EndList = -1;
            int Matched;  Matched = -1;
            int aMatched; aMatched = -1;
            for(int x = 0; x<15; x++){
                if(AdjectiveToAssociate == AdjectiveList[x][0])
                    aMatched = x;}

            if(!(aMatched == -1)){
            for(int x =1; x <4; x++){
                if((AdjectiveList[aMatched][x]==0) & (EndList == -1)){
                     EndList = x;}                                       //mark first occurrence of 0
                if(AdjectiveList[aMatched][x] == NewVerb)
                    Matched = x;
                    }
            if(Matched == -1)
               AdjectiveList[aMatched][EndList]=NewVerb;
            }

         }
         //-----END ACCOCIATE VERB WITH ADJECTIVE----------------------------

        int Tokenize (string str_Data)
        {
            int z;
            int y;
            int PlaceValue;
            int tmpToken;

                z = str_Data.size();
                PlaceValue = 1;
                tmpToken = 0;

                for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(str_Data[y-1]))*PlaceValue;
                    PlaceValue ++;}
            return tmpToken;

        }
};

#endif // C_MEMORYCELL_H
