#ifndef C_PERSONALITY_H
#define C_PERSONALITY_H

#include <c_ShortTermMemory.h>


class c_Personality : public c_ShortTermMemory
{
    public:
        c_Personality();
        virtual ~c_Personality();

    protected:


    private:
        string MyName;
        char MyGender;
        int MoodLevel;

    public:
        void SetName(string NewVal){MyName = NewVal;}
        void SetGender(char NewVal){MyGender = NewVal;}
        string GetMyName() {return MyName;}
        void SetMyName(string NewVal){MyName = NewVal;}
        void IncreaseMoodLevel(){MoodLevel++;}
        void DecreaseMoodLevel(){MoodLevel--;}
        int GetMoodLevel(){return MoodLevel;}



};

#endif // C_PERSONALITY_H
