#ifndef DEALER_HPP
#define DEALER_HPP
#include "Deck.hpp"

using namespace std;

class Dealer{
    public:
        Dealer();
        void hit(Deck &deck);
        vector<Card> getHand();
        void clearHand();
    private:
        vector<Card> hand;
};

//dealer doesnt get anything to start this is just here so we can give him stuff later
Dealer::Dealer(){

}
vector<Card> Dealer::getHand(){
    return this->hand;  
}
void Dealer::hit(Deck &deck){
    this->hand.push_back(deck.draw());
}
void Dealer::clearHand(){
    this->hand = {};
}
#endif