#ifndef C_CEREBELLUM_H
#define C_CEREBELLUM_H

#include <c_Cortex.h>


class c_Cerebellum : public c_Cortex
{
    public:
        c_Cerebellum();
        virtual ~c_Cerebellum();

    protected:

    private:


public:
//---------------------------------FINDSUBJECT()--------------------------------------------------
        int FindSubject()
        {
            if(Verbose)cout << "[c_Cerebellum.h::FindSubject]" << endl;
            int DeterminerLocation;       DeterminerLocation = -1;
            int UnknownLocation;          UnknownLocation    = -1;
            int WordCount;                WordCount          =  0;
            int SubLocation;              SubLocation        = -1;
            int NounLocation;             NounLocation       = -1;
            int SecondNounLocation;       SecondNounLocation = -1;
            int ProNounLocation;          ProNounLocation    = -1;
            string Pattern;               Pattern            = "";
            bool PickingSubject;          PickingSubject     = true;

            WordCount = GetWordCount();
            for(int x = 0; x < WordCount; x++){
                if(GetWordType(x)== 'd')if(DeterminerLocation == -1) DeterminerLocation = x;
                if(GetWordType(x)== 'u')if(UnknownLocation == -1)    UnknownLocation    = x;
                if(GetWordType(x)== 'n'){if(NounLocation == -1)    { NounLocation       = x;} else SecondNounLocation = x;}
                if(GetWordType(x)== 'r')if(SubLocation == -1)        SubLocation        = x;
                if(GetWordType(x)== 'p')if(ProNounLocation == -1)    ProNounLocation    = x;
                Pattern += GetWordType(x);
            }
            SetPattern(Pattern);
            if(SecondNounLocation != -1) SetIndirectObjectLocation(SecondNounLocation);
            while(PickingSubject){
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
              PickingSubject = false;
            }
            if(Verbose)
                    cout << "Suggested subject location:" << SubLocation << " Pattern:" << GetPattern() << " Indirect Object Location:" << GetIndirectObjectLocation()<< endl;

            return SubLocation;
        }
//--------------------------------------------------end Find Subject----------------------------------------------------------
};

#endif // C_CEREBELLUM_H
