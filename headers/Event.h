#ifndef EVENT
#define EVENT
#include <string>
using namespace std;
class Event {
    private:
    int time;
    string name;
    int newValue;
    public:
    Event(int t,string n,int nv);//time,name,newValue
    int getTime();
    string getName();
    int getNewValue();
};



#endif
