#ifndef C_SUBJECTSTACK_H
#define C_SUBJECTSTACK_H

//#include <c_Language.h>
#include <c_Personality.h>

class c_SubjectStack :  public c_Personality  //public c_Language
{
    public:
        c_SubjectStack();
        virtual ~c_SubjectStack();
    private:

        int Subjects[15];                           //These Subjects are tokenized words
        string strSubjects[15];
        string strTmpSubject;
        int SubjectCount;
        int tmpSubject;
    public:

        void SetSubject (int Subject,string strSubject)  //Push down old subjects
        {
            for(int x = 0; x< 15; x++)                      //swap to front if been here before
            if(Subjects[x]== Subject){
                tmpSubject     = Subjects[0];               //matched so swap to the front as the active subject
                strTmpSubject  = strSubjects[0];
                Subjects[0]    = Subject;
                strSubjects[0] = strSubject;
                Subjects[x]    = tmpSubject;                //move the old front subject to this place
                strSubjects[x] = strTmpSubject;}
            if(Subjects[0] != Subject){                     //no move down if already current
                    tmpSubject = Subjects[1];
                    strTmpSubject = strSubjects[1];
                for (int x = 14; x >0; x--){
                    Subjects[x] = Subjects[x-1];
                    strSubjects[x] = strSubjects[x-1];
                }
                Subjects[0] = Subject;
                strSubjects[0] = strSubject;
                SubjectCount++;
                if(SubjectCount > 15) SubjectCount = 15;}
        }



        int GetSubject(int Place=0)    //0 = current
        {
            return Subjects[Place];
        }
        string GetstrSubject(int Place)
        {
            return strSubjects[Place];
        }
        int GetSubjectCount()
        {
            return SubjectCount;
        }
};

#endif // C_SUBJECTSTACK_H
