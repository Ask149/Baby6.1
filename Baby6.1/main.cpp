#include <iostream>
#include <c_Brain.h>

using namespace std;

c_Brain Brain;
bool Verbose;

int main()
{
Brain.SetMyGender('f');
string Raw_Sentence;
Verbose = false;
//ProcessVerbFile();



cout << ">>";
getline (cin,Raw_Sentence);
while (Raw_Sentence != "end")
{
    Brain.ProcessUserInput(Raw_Sentence);

    if(Raw_Sentence != "end")
    {
    cout << ">>";
    Raw_Sentence = "";
    getline(cin,Raw_Sentence);
    }
}
    return 0;
}
