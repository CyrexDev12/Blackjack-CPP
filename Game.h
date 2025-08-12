#ifndef GAME_H
#define GAME_H

#include <String> 
#include <list>
#include <stack> 
#include "Card.h"
using namespace std;


class Game {
    public: 

    stack<Card> createDeck();
    

    // Make sure to handle aces in this method
    void startGame(stack<Card> deck);



};








#endif 