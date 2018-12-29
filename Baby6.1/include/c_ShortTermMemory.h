#ifndef C_SHORTTERMMEMORY_H
#define C_SHORTTERMMEMORY_H

#include <c_Medulla.h>


class c_ShortTermMemory : public c_Medulla
{
    public:
        c_ShortTermMemory();
        virtual ~c_ShortTermMemory();

    protected:

    private:
        string ReceivedInputs[300];
        string ProcessedPatterns[300];
        string ResponsesSent[300];

        int StoragePlacement;
        void IncrementStoragePlacement(){
            StoragePlacement++;
            if(StoragePlacement>=300) StoragePlacement =299;}


    public:
        void SaveReceivedInput(string NewData,bool NewLine=false){
            if(NewLine) IncrementStoragePlacement();
            ReceivedInputs[StoragePlacement] += " " + NewData;}

        void SaveProcessedPattern(string NewData,bool NewLine=false){
            if(NewLine) IncrementStoragePlacement();
            ProcessedPatterns[StoragePlacement] += " " + NewData;}

        void SaveResponsesSent(string NewData,bool NewLine=false){
            if(NewLine) IncrementStoragePlacement();
            ResponsesSent[StoragePlacement] += " " + NewData;}

        void ReportStorageFlow(){

            for(int x =0; x<=StoragePlacement; x++)
                cout << ReceivedInputs[x] << "---" << ProcessedPatterns[x] << "---" << ResponsesSent[x] << endl;
            }
};

#endif // C_SHORTTERMMEMORY_H
