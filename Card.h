#ifndef CARD_H
#define CARD_H

#include <String> 
#include <iostream>
using namespace std; 


class Card {
    protected: 
        string suit; 
        string name; 
        int value; 


    public: 
        Card(string CardSuite, string CardName, int CardValue);

       void display() const; 

};

 



#endif 