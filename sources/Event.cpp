#include "../headers/Event.h"
    Event::Event(int t,string n,int nv):time(t),name(n),newValue(nv){}//time,name,newValue
    int Event::getTime(){return time ;}
    string Event::getName(){return name ;}
    int Event::getNewValue(){return newValue;}