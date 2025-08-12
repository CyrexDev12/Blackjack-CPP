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

       // Getters
       int getCardValue() {
        return value;
       }

       string getCardName() {
        return name; 
       }

       string getCardSuit() {
        return suit; 
       }


};

 



#endif 