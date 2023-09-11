#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Deck.hpp"
#include <vector>
using namespace std;

class Player{
    public:
    Player();
    Player(int balance);
    vector<Card> getHand();
    void hit(Deck &deck);
    void clearHand();
    private:
        int balance;
        vector<Card> hand;
};

Player::Player(){
    this->balance = 100;
}

Player::Player(int balance){
    this->balance = balance;
}
vector<Card> Player::getHand(){
    return this->hand;  
}
void Player::hit(Deck &deck){
    this->hand.push_back(deck.draw());
}
void Player::clearHand(){
    this->hand = {};
}
#endif