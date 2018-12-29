#ifndef C_BRAIN_H
#define C_BRAIN_H

#include <c_Cerebellum.h>


class c_Brain : public c_Cerebellum
{
    public:
        c_Brain();
        virtual ~c_Brain();





        c_Personality UserPersonality;
        c_ShortTermMemory ShortTermMemory;

        c_Sentence SlowSpeakSentence;
        c_Sentence LastSentence;
        c_Sentence CommandCheckSentence;


        int rBrainCellCount;
        int lBrainCellCount;
        char GenClass;


    public:
        void SetMyName (string NewVal){SetName(NewVal);}
        void SetUserName (string NewVal){UserPersonality.SetName(NewVal);}
        void SetMyGender (char NewVal){SetGender(NewVal);}
        void SetUserGender (char NewVal){UserPersonality.SetGender(NewVal);}








//---------------------------------------------------------------------------------------------------------------------------------------------------
//********************************************* First Processing Point / Cortex is Main Processor****************************************************

        void ProcessUserInput(string& strData){
            if(Verbose)cout << "[c_Brain.h::ProcessUserInput]" << endl;
            int a, ConfidenceLevel;
            string b,c,CheckedPattern;
            int SubjectLocation;
            bool Greeting;
            a = 0;


            CommandCheckSentence.Parse(strData);
            a = CommandTrap();
            Parse(strData);                                                              //break sentence down
            CheckForGreetings(Greeting);
           if(Greeting == false){


            if(a == 0){                                                                   //check for command
             SaveReceivedInput(strData,true);                                             //update short term memory
             SetWordTypes();                                                              //try to set all word types
             SubjectLocation = FindSubject();                                             //try to located subject
             SetSubjectLocation(SubjectLocation);                                         //set the suggestion
             CheckedPattern = PatternReview(GetPattern(),ConfidenceLevel);                //see if language class can enhance pattern
             if(Verbose){
                    cout << "Processed Pattern:" << CheckedPattern << ":" << GetPattern() << "Confidence level: " << ConfidenceLevel << endl;}
             if(CheckedPattern != GetPattern()){
                SetPattern(CheckedPattern);
                for(int x = 0; x < GetWordCount(); x++){
                    SetWordType(CheckedPattern[x],x);
                }
                SubjectLocation = FindSubject();
                SetSubjectLocation(SubjectLocation);
             }
             DecipherCurrentSentence();                                                             //work with sentence
             SetSubjectLocation(SubjectLocation);                                                  //store the location or -1
             a = StoreNewWords();                                                                  //save any new words in rBrainCells
             SaveProcessedPattern(GetPattern());                                                   //update short term memory
             if(SubjectLocation >=0)
                SetSubject(GetWordTokens(SubjectLocation),GetWords(SubjectLocation));
             }
            else
                if(a == -1)
            {
                strData = "end";
            }
           }//end Greeting check

            }
//-----------------------------------------------END FIRST PROCESSING---------------------------------------------------------------------------------



        void Report(){
        int WC; int sbj;
        WC = GetWordCount();
        cout << "Punctuation Flag:" << GetHasPunctuation() << "  Punctuation Character:" << GetPunctuation() << endl;
        cout << "Word Count:" << WC << " Pattern:" << GetPattern() << endl;
        for (int x = 0; x < WC; x++){
            cout << x << " " << GetWords(x) << ":" << GetWordTokens(x) <<  " Type:"
            << GetWordType(x) << " isContraction:" << GetisContraction(x) << " Quote Location:" << GetQuoteLocation(x) << endl;
        }
            cout << "Cell Usage(r):" << GetRightLobeUsageCount() <<  " Cell Usage(l):" << GetLeftLobeUsageCount() << endl;
        }







        int CommandTrap()
        {
            int Command;
            int Count;
            Command = 0;
            int Control; Control =0;
            Count = CommandCheckSentence.GetWordCount();
            Command = CommandCheckSentence.GetWordTokens(0);
            if(Count >1)
             Command = Command + CommandCheckSentence.GetWordTokens(1);



            switch (Command)
            {

            case 623: //end
                {
                    Control = -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 1090: // exit
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 2699: // mood level
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 2979: // goodbye
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 3337:    // cell report
                {
                    cout << "Cell Report:Right Brain" << endl << endl;
                    cout << "Cell String:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpCellDataString() << endl;
                    cout << "Cell String (LC):" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpCellDataLC() << endl;
                    cout << "Cell Word Type:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpWordType() << endl;
                    cout << "Cell Secondary Word Type:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetSecondaryType() << endl;
                    cout << "Cell Alternate Word Type:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetAlternateType() << endl;
                    cout << "Cell Gender:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetGenderClass() << endl;
                    cout << "Cell Primary Usage:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpCellPurpose() << endl;
                    cout << "Cell Root Pointer:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpNextNoun() << endl;
                    cout << "Cell Data is Set:" << RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpIsSet() << endl;
                    cout << "Cell Location by token:" << CommandCheckSentence.GetWordTokens(2) << endl;
                    int q,z;
                    if(RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetpWordType()=='n'){
                        for(int x = 0; x < 15; x++){
                            q = CommandCheckSentence.GetWordTokens(2); z = RightLobeMemory[q].GetAdjective(x);
                            if(z >0){
                                cout << "Adjective " << x << " " <<  RightLobeMemory[RightLobeMemory[CommandCheckSentence.GetWordTokens(2)].GetAdjective(x)].GetpCellDataString()<< " Verbs: ";
                                for(int y = 1; y < 4; y++){
                                    cout << RightLobeMemory[RightLobeMemory[q].GetVerbWithAdjective(x,y)].GetpCellDataString() << " ";
                                }
                                cout << endl;
                            }
                        }
                    }


                    Control = 2;
                    break;
                }
            case 3058:   //verbose
                {
                    if(Verbose)
                        Verbose = false;
                    else
                        Verbose = true;

                    Control = 2;
                    break;
                }
            case 3387:  //report flow
                {
                    ReportStorageFlow();
                    Control = 2;
                    break;
                }

            case 3383:  //report last
                {
                    Report();
                    Control = 2;
                    break;
                }
            case 4854:  //moodlevel
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 5352:  //subject report
                {
                    Control = 2;
                    cout << "no. Token Memory Subject string\n";
                    for(int x =0; x<15; x++){
                        if(GetSubject(x)>0)
                            cout << x << ":   " << GetSubject(x) << "    " << RightLobeMemory[GetSubject(x)].GetpCellDataString() << " " << GetstrSubject(x) << endl;}

                }



            }
            if((Control != 0)&(Verbose))
                cout << "[c_Brain.h::CommandTrap]-successful\n";
            else
                if(Verbose) cout << "[c_Brain.h::CommandTrap]-no command found\n";
            return Control;
        }



        int Respond(){    //can delete this

        //if(lBrainCellCount == 0){
        //    cout << "Hello. My name is " << MyPersonality.GetMyName() << endl;
        //    return 1;                                                         //ask user for more input

         return CommandTrap() ;

        return 0;
        }










      //scan sentence words and set their types
      //   Check memory storage first (search only lowercase storage)
      //     if already stored set the sentence word type to the memory value
      //     if not, has already been initialized to 'u' unless sentence parser has set something other than 'u'
      //    doCorrection is control to not override wordtype stored in brain  true = change it to whatever is set by others

       void SetWordTypes(bool doCorrection = false)
        {
            if(Verbose){cout << "[c_Brain.h::SetWordTypes]" << endl;}
            char tmpTypeInSentence, tmpTypeInMemoryCell, tmpTypeFromLanguageHelper;
            bool isSetInMemory;
            for(int x = 0; x < GetWordCount(); x++){
                    tmpTypeInSentence         = GetWordType(x);
                    tmpTypeInMemoryCell       = GetBrainWordType(GetWordsLC(x),'r');
                    tmpTypeFromLanguageHelper = FindWordType(GetWordsLC(x));
                    isSetInMemory             = GetBrainCellIsSet('r',Tokenize(GetWordsLC(x)));
                    if(Verbose){
                        cout << "WordLC:  " << GetWordsLC(x) << endl;
                        cout << "     Sentence Set:" << tmpTypeInSentence << endl;
                        cout << "     MemoryCell Set:" << tmpTypeInMemoryCell << endl;
                        cout << "     Language helper Set:" << tmpTypeFromLanguageHelper << endl;
                        cout << "      Memory Cell Previously set?" << isSetInMemory << endl;}

                    if(isSetInMemory & doCorrection) isSetInMemory = false;

                    if(isSetInMemory == false){
                        if(tmpTypeInSentence == 'u')
                            SetWordType(tmpTypeFromLanguageHelper,x);}
                    else{
                        SetWordType(tmpTypeInMemoryCell,x);}

                     if( GetWordType(x) == 'q') SetIsQuestion(true);

            }
        }//------END SET WORD TYPES---------------------------------------------------------------

///------------------------------------------------------------------------------------------------

//---------------------------------FINDSUBJECT()--------------------------------------------------
        int FindSubject()
        {
            if(Verbose)cout << "[c_Brain.h::FindSubject]" << endl;
            int DeterminerLocation;       DeterminerLocation = -1;
            int UnknownLocation;          UnknownLocation    = -1;
            int WordCount;                WordCount          =  0;
            int SubLocation;              SubLocation        = -1;
            int NounLocation;             NounLocation       = -1;
            int ProNounLocation;          ProNounLocation    = -1;
            string Pattern;               Pattern            = "";

            WordCount = GetWordCount();
            for(int x = 0; x < WordCount; x++){
                if(GetWordType(x)== 'd')DeterminerLocation = x;
                if(GetWordType(x)== 'u')UnknownLocation    = x;
                if(GetWordType(x)== 'n')NounLocation       = x;
                if(GetWordType(x)== 'r')SubLocation        = x;
                if(GetWordType(x)== 'p')ProNounLocation    = x;
                Pattern += GetWordType(x);
            }
            SetPattern(Pattern);
            if((SubLocation == -1) & (NounLocation != -1))
                SubLocation = NounLocation;
            else
                if((SubLocation == -1) & (ProNounLocation !=-1))
                    SubLocation = ProNounLocation;
            else
                if((SubLocation == -1) & (DeterminerLocation != -1))
                    SubLocation = DeterminerLocation +1;
            else
                if((SubLocation == -1) & (UnknownLocation != -1))
                    SubLocation = UnknownLocation;


            if(Verbose)
                    cout << "Suggested subject location:" << SubLocation << " Pattern:" << GetPattern() << endl;

            return SubLocation;
        }
//--------------------------------------------------end Find Subject----------------------------------------------------------

        void TrySubject()
        {
          int SubjectLoc;
          int Complexity;
          int Response;
          SubjectLoc = GetSubjectLocation();
          Complexity = GetWordCount();
          //cout << "Subject Location:" << SubjectLoc << endl;

           switch(Complexity)
           {


             case 4:
               {
                   DecipherCurrentSentence();

                   SlowSpeak(GetWords(0)+ " " + GetWords(3)+ " " + GetWords(SubjectLoc)+ ".");
                   SlowSpeak("Is this right?");
                   Response = RequestUserResponse();
                   if(Response == 1){
                    cout << "Yeah!" << endl;
                    //tell user to describe subject or suggest the subject we're understanding
                    //set assumptions
                    //set/adjust subject stack
                   }
                   else{
                    SlowSpeak("Oh. Let me try again.");   //subject is wrong
                    SlowSpeak("Is " + GetWords(3) + " " + GetWords(1) + " " + GetWords(2)+ "?");
                    Response = RequestUserResponse();
                     if(Response == 1){
                        //reset subject location
                        //tell user to describe subject or suggest the subject we're understanding
                       //set assumptions
                       //set/adjust subject stack
                     }

                   }
                   break;
               }

           }

            //if(SubjectLoc){
            //cout << "Tech me about " << Sentence.GetWords(SubjectLoc) << ",please." << endl;
            //}
        }
//------------------------------STORE NEW WORDS-----------------------------------------------------------------
        int StoreNewWords()
        {
         if(Verbose)cout << "[c_Brain.h::StoreNewWords]" << endl;
         int NewWords; NewWords = 0;

         for (int x = 0; x < GetWordCount(); x++)
         {
             if( !(CheckForKnownWord(GetWords(x))))
                {NewWords++;}
                InstallNewWord(GetWords(x),GetWordType(x),'w',GetWordsLC(x),true);
                if(GetWordType(x)=='a'){
                        if(GetSubjectLocation() >=0 )
                            RightLobeMemory[GetWordTokens(GetSubjectLocation())].AccociateAdjective(GetWordTokens(x));
                    int z; z = GetVerbPointingToAdjective();
                    if(z >=0)
                        RightLobeMemory[GetWordTokens(GetSubjectLocation())].AccociateAdjectiveWithVerb(GetWordTokens(z),GetWordTokens(x));
                }
         }


            return NewWords;

        }
};

#endif // C_BRAIN_H
