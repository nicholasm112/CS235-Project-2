/*
Nicholas Morgan
CSCI 235
Project 1
6/7/23
*/
#include "Pack.h"
#include <iostream>
#include <array>
#include <string>



/* Default constructor
   *  @post Initializes the Pack from lowest card to highest card. Arrange
   *  cards of lowest suit from lowest to highest rank then move onto the
   *  next suit. Order of suits and ranks are defined in the project specs.
   */
Pack::Pack() {
  


   for (int i = 0; i < 52; i++) {
        Card* card = new Card(Rank{i%13}, Suit{i/13});
       cards[i] = *card;
       delete card;
   }
    next = 0;
}


   /* Parameterized constructor
   *  @pre pack_input contains a valid representation of a Pack as defined
   *       in the project specs.
   *  @post Initializes the Pack by reading from pack_input
   *  @param pack_input int index = 0;
   */
Pack::Pack(std::istream& pack_input) {
    std::string c;
    std::string rank_;
    std::string suit_;
    int i = 0;

    while(pack_input >> rank_ >> c >> suit_){    
        cards[i] = Card(string_to_rank(rank_) ,string_to_suit(suit_));
        i++;   
    }
    

    next = 0;
}


   /* Removes the next card from the pack and returns it
   *  @pre Requires that there are cards remaining in the pack
   *  @post Increment the next index
   *  @return next card in the pack
   */
   Card Pack::deal_one() {
        if(next < 52){
            Card card = cards[next];
            next++;
            return card;
        }
        throw("Error Pack Empty()");
        
   }


   /* Reset the new index to first card in the Pack
   *  @post reset index to initial value
   */
   void Pack::reset() {
       next = 0;
   }


   /* In-place Faro shuffle on pack of cards
   *  @post Shuffles the cards using in-place faro shuffle fifteen times
   *        and resets the index
   *        See: https://en.wikipedia.org/wiki/In_shuffle
   */
//shuffle 15 times, 27,1,28,2,29,3 .... 52,26
void Pack::shuffle() {
    std::array<Card, PACK_SIZE> hand1;
    std::array<Card, PACK_SIZE> hand2;
    int k, l = 0;

    for(int i=0; i < 15; i++) {
        for(int j = 0; j < 26; j++){
            hand1[j] = cards[j];
            hand2[j] = cards[j+26];
        }
        k = 0;
        l = 0;
        for(int j = 0; j < 52; j++){
            if(j%2 == 1){
                cards[j] = hand1[k];
                k++;
            }
                
            else{
                cards[j] = hand2[l];
                l++;
            }
        }
    }
    reset();
}


   /* Determines if there are no more cards in the pack
   *  @return true if the pack is empty
   */
   bool Pack::empty() const {
       return (next>=PACK_SIZE);
   }