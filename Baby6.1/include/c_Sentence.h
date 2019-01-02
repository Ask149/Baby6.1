#ifndef C_SENTENCE_H
#define C_SENTENCE_H

#include <c_SubjectStack.h>


class c_Sentence : public c_SubjectStack
{
    public:
        c_Sentence();
        virtual ~c_Sentence();

    protected:

    private:
        int    WordCount;                       // no. of words in sentence not counting punctuation  initialize to 0
        int    SubjectLocation;                 // from 0 to WordCount, -1 = subject not located
        int    WordTokens[30];                  // dog = 625 initialize to 0
        bool   isContraction[30];               // true / false  initialize to false  initialize to ""
        int    QuoteLocation[30];               // "can't" set to 3 for this, set to -1 for "dog"
        int    IndirectObjectLocation;          // usually the second noun
        string Words[30];                       // Dog  i.e. original unedited word  initialize to ""
        string WordsLC[30];                     // dog  initialize to ""
        string SubWords[30];                    // replacement words, usually from subject stack
        string ContractionWordLongForm[30];     // i.e. can not  will not   initialize to ""
        string OriginalString;                  // the whole unedited string  initialize to ""
        string Pattern;                         // i.e. dnvua  initialize to ""
        char   Punctuation;                     // !  initialize to null
        bool   HasPunctuation;                  // true / false initialize to false
        bool   HasPluralPronoun;                // true / false initialize to false
        bool   IsQuestion;                      // true / false initialize to false
        char   WordType[30];                    // n-noun v-verb p-pronoun a-adjective d-determiner(the) r-subject representative(it that) u-unknown c-connecting word(and)  C(cap) Contraction word
                                                // n-noun p-pronoun v-verb q-question word a-adjective r-subject replacement P(cap) ProperNoun i.e. name A(cap) Adverb D(cap) Direct Object d(LC) Indirect object
                                                // initialize to 'u'
        char   SecondaryType[30];               // same as WordType[]
        char   AlternateType[30];               // same as WordType[]

        void InitializeVars(){
            for(int x =0; x < 30; x++){
                Words[x]                   = "";
                WordTokens[x]              = 0;
                QuoteLocation[x]           = -1;
                isContraction[x]           = false;
                WordsLC[x]                 = "";
                SubWords[x]                = "";
                ContractionWordLongForm[x] = "";
                WordType[x]                = 'u';
                SecondaryType[x]           = 'u';
                AlternateType[x]           = 'u';}

                WordCount                  = 0;
                SubjectLocation            = -1;
                OriginalString             = "";
                Pattern                    = "";
                HasPluralPronoun           = false;
                HasPunctuation             = false;
                IsQuestion                 = false;
                IndirectObjectLocation     = -1;}

    public:
        int    GetIndirectObjectLocation(){return IndirectObjectLocation;}
        void   SetIndirectObjectLocation(int NewVal){IndirectObjectLocation = NewVal;}
        bool   GetHasPluralPronoun(){return HasPluralPronoun;}
        void   SetHasPluralPronoun(bool newVal){HasPluralPronoun = newVal;}
        char   GetSecondaryType(int Location){return SecondaryType[Location];}
        void   SetSecondaryType(char Type,int Location){SecondaryType[Location] = Type;}
        char   GetAlternateType(int Location){return AlternateType[Location];}
        void   SetAlternateType(char Type,int Location){AlternateType[Location] = Type;}
        int    GetWordCount(){return WordCount;}
        char   GetPunctuation(){return Punctuation;}
        bool   GetHasPunctuation(){return HasPunctuation;}
        bool   GetIsQuestion(){return IsQuestion;}
        int    GetWordTokens(int loc){return WordTokens[loc];}
        string GetWords(int loc){return Words[loc];}
        string GetWordsLC(int loc){return WordsLC[loc];}
        string GetOriginalString(){return OriginalString;}
        char   GetWordType(int loc){return WordType[loc];}
        void   SetWordType(char Type, int loc){WordType[loc] = Type;}
        void   SetIsQuestion(bool ISQ){IsQuestion = ISQ;}
        void   SetSubjectLocation(int newLoc){SubjectLocation = newLoc;}
        int    GetSubjectLocation(){return SubjectLocation;}
        void   SetWords(string strData,int Loc){Words[Loc]=strData;}
        void   SetSubWords(int loc,string strData){SubWords[loc] = strData;}
        string GetSubWords(int loc){return SubWords[loc];}
        void   SetPattern(string strData){Pattern = strData;}
        string GetPattern(){return Pattern;}
        bool   GetisContraction(int Location){return isContraction[Location];}
        int    GetQuoteLocation(int Location){return QuoteLocation[Location];}



        void RebuildPattern(){
            Pattern = "";
            for(int x =0; x < GetWordCount(); x++) Pattern += GetWordType(x);}



        int GetVerbPointingToAdjective(){
            int VerbLoc; VerbLoc = -1;
            for(int x = 0; x < GetWordCount(); x++)
                if((GetWordType(x)=='v') & (GetWordType(x+1)=='a')) VerbLoc = x;
            if(VerbLoc == -1){
                for(int x = 0; x< GetWordCount(); x++){
                    if(GetWordType(x) == 'v')VerbLoc = x;}}
            return VerbLoc;
            }

        void Parse (string str_Sentence_Data)
{
    //----------------------Initialize-------------------------------------------------------------------------------------------------
                if(Verbose)cout << "[c_Sentence.h::Parse] " << str_Sentence_Data << endl;
                InitializeVars();
                OriginalString = str_Sentence_Data;
                int int_Word_Count;
                int_Word_Count = 0;
                int x; x = 0; int int_Sentence_Length;
                int int_Last_Pos;
                int int_Sentence_Token_Position=0; // Initialize Token Position to start
                int t; t = 0;
                int_Sentence_Length = str_Sentence_Data.size();
                int_Last_Pos = int_Sentence_Length;

                if(int_Sentence_Length <=0){
                    return;
                }


                while (str_Sentence_Data[x] == ' ')
                    {                                                                       //trim leading spaces
                        x++;
                        int_Sentence_Token_Position++;
                    }
                while (str_Sentence_Data[int_Last_Pos-1]==' ')                              //trim trailing spaces
                    {
                    int_Last_Pos--;
                    }

            //--------------------------Punctuation Check----------------------------------------------------------------
                char c_tmp_char;
                char c_Punctuation;
                IsQuestion = false;
                c_tmp_char = str_Sentence_Data[int_Last_Pos-1];
                if( !(((c_tmp_char >= 'A') & (c_tmp_char <= 'Z')) |
                        ((c_tmp_char >= 'a') & (c_tmp_char <= 'z')))
                   )
                  {

                    HasPunctuation = true;                                                                                          //SET Public Variable
                    c_Punctuation = str_Sentence_Data[int_Last_Pos-1];
                    Punctuation = c_Punctuation;
                    if(Punctuation == '?') IsQuestion = true;
                                                                                                                                    //SET Public Variable
                    int_Last_Pos --;
                  }
            //---------------------------------------------------------------------------------------------------------------
                 while (str_Sentence_Data[int_Last_Pos-1]==' ')                              //trim trailing spaces once more
                  {
                    int_Last_Pos--;
                  }
            //--------------------------------NOW PARSE THE SENTENCE---------------------------------------------------------

                t = str_Sentence_Data.find(" ",x);                              //find first occurrence of space after word

                while ( (t > 0) & (t  < int_Last_Pos))
                {
                    Words[int_Word_Count] = str_Sentence_Data.substr(x,t-x);    //extract word
                    x = t+1;                                                    //move pointer
                    t = str_Sentence_Data.find(" ",x);                          //find next space
                    int_Word_Count++;
                    while ((str_Sentence_Data[x] == ' ') & (t < int_Last_Pos))
                     {
                            x++;
                            t = str_Sentence_Data.find(" ",x);
                     }

                }




                Words[int_Word_Count] = str_Sentence_Data.substr(x,int_Last_Pos-x);
                int_Word_Count++;


                WordCount = int_Word_Count;

            //-----------------------------------------TOKENIZE ALL WORDS AND CHECK FOR CONTRACTION WORDS-------------
                int QuoteLoc;
                for (x = 0; x < int_Word_Count; x++)
                {

                    QuoteLoc = Words[x].find('\'');
                    if((QuoteLoc >=0)&(QuoteLoc<int_Last_Pos)){
                        WordType[x] = 'C';  //Contraction flag~ Possible plural possessive
                        isContraction[x] = true;}
                    QuoteLocation[x] = QuoteLoc;
                    string tmpWord;
                    tmpWord = Words[x];
                    WordsLC[x] = "";
                     //Set WordsLC-----------------------------
                        for(int t = 0; t < Words[x].size(); t++)
                            tmpWord[t] =  tolower(tmpWord[t]);
                        WordsLC[x] = tmpWord;
                     //----------------------------------------
                     WordTokens[x] = Tokenize(WordsLC[x]);
                }
              //-----------------------------END OF TOKENIZE AND CONTRACTION CHECK----------------------------------------


            }// --------END OF PARSE-------------------------------------
};

#endif // C_SENTENCE_H
