#ifndef DECK_HPP
#define DECK_HPP
#include "Card.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <time.h>

const vector<string> deckVals = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
using namespace std;
//declaration of class deck that stores a vector of cards and has necessary helper methods
class Deck{
    public:
        Deck();
        Deck(const int NUMDECKS);
        vector<Card> getDeck();
        Card draw();
        void restart();
        void shuffle();
        void printDeck();
    private:
        vector<Card> deck;
        int numDecks;
};
Deck::Deck(){
    //loop to add one deck of cards to a deck
    //one for each type 2,3,4,5,etc.
    numDecks = 1;
    for(int i=0;i<13;i++){
        //another for 4 of each kind
        for(int j=0;j<4;j++){
            Card toPush(deckVals[i]);
            this->deck.push_back(toPush);
        }

    }
}
Deck::Deck(const int NUMDECKS){
    this->numDecks = NUMDECKS;
    for(int i=0;i<13;i++){
        //another for 4 of each kind
        for(int j=0;j<4*NUMDECKS;j++){
            Card toPush(deckVals[i]);
            this->deck.push_back(toPush);
        }

    }
}
vector<Card> Deck::getDeck(){
    return deck;
}
Card Deck::draw(){
    Card toReturn = deck.at(deck.size()-1);
    deck.pop_back();
    return toReturn;
}
void Deck::restart(){
    Deck newDeck(numDecks);
    newDeck.shuffle();
    this->deck = newDeck.deck;
}
void Deck::shuffle(){
    Deck shuffled(0);
    int random;
    int min = 0;
    int max;
    int size = deck.size();
    for(int i=0;i<size;i++){
        max = deck.size()-1;
        //set range of rand
        srand(time(NULL));
        random = rand() % ((max-min)+1)+min;
        shuffled.deck.push_back(deck.at(random));
        deck.erase(deck.begin()+random);
        
    }
    deck = shuffled.deck;
}
void Deck::printDeck(){
    for(int i=0;i<deck.size();i++){
        //another for 4 of each kind
            cout << this->deck.at(i).value;
    }
    cout << endl;
}

#endif