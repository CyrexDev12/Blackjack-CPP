#include <iostream>
#include <stack>
#include "Card.h"
#include "Game.h"
using namespace std;



int main() {
    Game game;
    //Initalize the deck and start the game
    int roundCount = 0; 
    bool status = true;
    char input = 0; 
    stack<Card> Deck;

    while (status) {
        if (roundCount % 3 == 0 || roundCount == 0) {   // We will shuffle after every 3 rounds
        cout << "Shuffling the deck! We shuffle after every 3 rounds\n";
        Deck = game.createDeck();
        }

        game.startGame(Deck);
         cout << "\nWould you like to play again? (y/n): ";
         cin >> input;
         if (input == 'y') {
        roundCount++;
         } else {
            status = false; // Game will end 
         }

    }

    
    return 0; 
}