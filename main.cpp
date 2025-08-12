#include <iostream>
#include <stack>
#include "Card.h"
#include "Game.h"
using namespace std;



int main() {
    Game game;
    //Initalize the deck and start the game
    stack<Card> Deck = game.createDeck();

   game.startGame(Deck);
    
    return 0; 
}