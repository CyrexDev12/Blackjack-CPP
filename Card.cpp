#include "Card.h"
#include <iostream>

Card::Card(string cardSuite, string CardName, int CardValue) 
: suit(cardSuite), name(CardName), value(CardValue)
{}

void Card::display() const {
            cout << name << " of " << suit << " (Value: " << value << ") ";
        }