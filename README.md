[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Jgqz1aO5)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11369890&assignment_repo_type=AssignmentRepo)
# Introduction
In Project 2, you are working on the `Player` class that would represent a player in the game of Spades. Notice in `Player.h` that the `Player` class is an abstract class since it has at least one pure virtual function (in reality, all of the functions in the class are pure virtual). This is because a `Player` should not represent an actual instantiable player but act as an abstract concept of one. It is through inheritance that we will create an instantiable player class.

For Project 2, I would like you to create a `Human` class that inherits from `Player` to allow a person to play the game on the terminal. This Human class should be declared and defined inside the Player.cpp file. 

You might notice that when you are done with creating this Human class in the .cpp file, that when you go to test it, you are not able to work with the Human class directly. This is because the interface file (aka the header file), doesn't include Human but only Player. We can only work with code that was in the interface file. 

So how does one create a `Human` object without directly creating a `Human` object? Well, notice at the bottom of the header file, there is a function called `Player_factory`. This function acts as the interface to any `Player` type defined in the `Player.cpp` file. To use this function, all you need to do is give the name of the `Player`, and mention the type of `Player` they will be. For our case, the only `Player` we will be creating in this project is the `Human` player, but just imagine if we were to work on this project more and had created other types of players like a `SimpleAI` player or a `DifficultAI` player. This factory function would allow us to choose which type of player we want arbitrarily, rather than hard coding it. 

# Human Player
## Overview
This player would represent a person playing the game. The implementation of this class is left up to you as I don't care how this class is implemented but just that it works the way I expect it to work. I do have some tips below in case you need some guidance on where to start. 

Ideally the Human class should have at least four private member variables:
- Container that stores the players card, aka the hand (*suggestion*: `vector`)
- `string` to store the name of the player
- `int` for the number of tricks the player took during the hand
- `int` for the bid that the player placed before playing the hand

## Functions
### `Human(std::string name);` 
The parameterize constructor for Human. Should set the member variable for the name of the player, along with starting out with an empty hand (player has no cards). The number of tricks and the bid should be set to zero.

### `const std::string& get_name() const;`
Returns the name of the player.

### `void set_bid();`
Sets the bid for the player. Please follow these steps below:
- Ask the player `"Does Player " + player.name + " want to bid blind nil? [y/n]\n"`
	- User input is `n` 
		- Set their bid to be zero and mark it as blind nil. *DO NOT PRINT OUT THEIR HAND*
	- User input is `y` 
	  	- Print out user's complete hand in ascending order (details below) 
		- Print out `"How much would you like to bid (0 to 13 inclusive)?\n"`
		- If the user gives a value from 0 to 13 inclusive, then set the bid to that
		- Otherwise, print `"How much would you like to bid (0 to 13 inclusive)?\n"` and repeat until the previous step is fulfilled. 
	- User input is something else
		- Print out ``"Please answer using only `y` for yes or `n` for no.\n"``
		- Repeat until the user gives `y` or `n`

#### Example:
```cpp
Player* player = Player_factory("Bob", "Human");
// cards were added to player's hand
player->set_bid();
```
Terminal below after calling set_bid function on player:
```
>> Does Player Bob want to bid blind nil? [y/n]
<< g
>> Please answer using only `y` for yes or `n` for no.
<< Y
>> Please answer using only `y` for yes or `n` for no.
<< n
>> [1] Two of Clubs
>> [2] Nine of Clubs
>> [3] Queen of Clubs
>> [4] King of Clubs
>> [5] Ace of Clubs
>> [6] Eight of Diamonds
>> [7] Ten of Diamonds
>> [8] Nine of Hearts
>> [9] Ten of Hearts
>> [10] Two of Spades
>> [11] Five of Spades
>> [12] Nine of Spades
>> [13] Ace of Spades
>> How much would you like to bid (0 to 13 inclusive)?
<< -1
>> Please answer with values from 0 to 13 inclusive.
<< 14
>> Please answer with values from 0 to 13 inclusive.
<< 13
```

### `int get_bid() const;`
Returns the bid of the player during the hand. Remember that a nil bid and blind nil bid should both be a bid of zero. 

### `bool add_trick();`
Increments the player's trick count by one. Only does this if the player's current trick count is less than the max hand size. If the addition is successful, return true.

### `int get_trick() const;`
Returns the number of tricks the player won during the hand.

### `bool nil_bid() const;`
Returns true if the player bid nil. Remember that a nil bid is different from a blind nil bid. Therefore, if a player bid blind nil, then this function should return false.

### `bool blind_nil_bid() const;`
Returns true is the player bid blind nil. 

### `bool add_card(const Card& c);`
Adds a card to the player's hand. Only does this if the size of the hand is less than the max hand size. Return true if the addition was successful. 

If you are using a `vector` to store the cards, then you might want to add the cards in such a way so that it the hand remains sorted (think insertion sort). This would make printing out the sorted hand so much easier since it would then just be a simple traversal.

### `Card lead_card(bool broken_spade)`
Play the leading card of the trick. If `broken_spade` is `false` and there exist at least one card in the player's hand that is not a Spade, then the playable cards are any card that is not Spades. Else, all cards in the hand are considered playable.

Follow the steps below:
1. If the hand is empty, throw `std::out_of_range("Player has no more cards to play with.")`
2. Figure out the playable cards based on the rules above
3. Print out the playable cards (details below)
4. Ask the user for the card using this question: `"Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n"`
	a. Repeat until the user gives a correct value
5. Select the card, remove it from the player's hand, and return the card

### `Card play_card(const Card& led_card)`
Play a non-leading card during the trick. This function is very similar to the `lead_card` function but the only difference is what is considered playable. Whereas the `lead_card` function means that the player is leading the trick, the `play_card` function means that someone already led the trick and that the player must follow suit if they have cards of that lead suit. If the player doesn't have any cards of the leading suit, then they can play any card.

Therefore the playable hand for the `play_card` function should only be lead suit cards if the player's hand contains any; otherwise the playable hand is the player's hand itself. 

Follow the steps mentioned in `lead_card`, while keeping in mind of the playable hand for `play_card`.

### `void reset();`
Resets the player to initial values. This means bid and tricks are zero and there are no cards in the player's hand.

## Tips
- Implement some private helper functions that would help you implement the public facing functions: 
	- `print_hand` function that takes in a playable hand as a parameter and prints the cards in the hand as such `[[card_index + 1]] [rank] of [suit]\n` in ascending sorted order. So for example, `"[1] Two of Clubs\n[2] Three of Diamonds\n[3] Ace of Spades\n"`. Notice that there is the `[]` surround the index in the example. It is needed.
	- `remove_card` function that would remove the Card from the player's hand in such a way that the hand would still remain in sorted order.
- While the type of container that would store the player's hand is up to you, I suggest using a vector for it's simplicity. 

# Notes
## Improved Compilation Times
I've improved the compilation times when you compile the test files via the Makefile. If you take a look at the Makefile, you'll notice that I am compiling every file to an object file then combining the object files into the executable. Compiling this way improves the compilation time as we only need to re-execute the compilation of the files that were changed rather than compiling everything at once every time the command is ran.

## Updated `test_card.cpp` 
This repo has the updated version of the test_card.cpp file. 

## Testing Incrementally Using the Test Files
I have not mentioned this before, but if you would like to test a function from your code instead of the entire code itself, you can do that with the test files. In the test files, notice how there are two parameters for every `TEST_CASE`; the first parameter is the name of the test case, and the second parameter is the tag. Using this tag, we can select which test we would like to run during the execution of the test file.

To do this, instead of using the make command `make test_file_name`, use `make test_[file_name].exe`. This other command only makes the executable rather than both making the executable and executing it. Once the executable is created, you can pass in the tag of test case you would like to run as such `./test_file.exe [tag]`. The `[]` surrounding the tag name is necessary when running this command. For example, I would run `make test_player.exe` on the terminal, then run `./test_player.exe [one]` to run only the first test case. *KEEP IN MIND* that if you make any new changes to any files, that you need to run the command that recompiled the code.

# Submission
Make sure you include the `.cpp` files from the previous project, along with the `Player.cpp` file. As always, **DO NOT MODIFY** the header files. Please submit the files to Gradescope via your GitHub repos. 

----

# Overview
The projects in this class will have you work your way up to create a game of Spades. Spades is a simple trick-taking card game. A trick-taking card game is one where whoever plays the highest card, however it is defined, during the "trick" wins the "trick." With Spades, there are four players who play in teams of two. The objective of the game is to have your team win 300 points or have the opposing team lose with -200 points. Points earned or lost are determined by how many tricks the team wins in comparison to how many tricks they predicted they would take during the game session (aka, their bid). 

If reading the rules don't help you to understand the game, then [play a few games](https://spades-game.online/) to get a feel for it. Our rules are mostly the same as the rules on this website.

# Rules
## Players
- Four players
- Fixed partnerships of two. Partners sit opposite to each other. Deal and play is clockwise.
	- *Example:* A list of players is `[P0, P1, P2, P3]`. Game play is clockwise so it always moves to the right in the array, which in the perspective of a player, it is to their left. `P0` and `P2` are on `Team0` and `P1` and `P3` are on `Team1`.

## Cards
- 52 cards
- Spades is trump, meaning it has a higher value than a card of another suit regardless of rank.
- Rank from highest to lowest: Ace, King, Queen, Jack, 10, 9 ,8 , 7, 6, 5, 4, 3, 2
- Suit from highest to lowest: Spades, Hearts, Diamonds, Clubs

## Deal
- First dealer chosen at random and turn to deal is clockwise.
- Cards are shuffled.
- Cards dealt singly in clockwise order from starting from player to the left of the dealer.
	- *Example:* If I have the Cards in a Pack like this `[A, B, C, D, E, F, G, H]` and a list of players `[P0, P1, P2, P3]` with `P0` as the dealer, then `P1` cards are `A, E`, `P2` cards are `[B, F]`, `P3` cards are `[C, G]` and `P0` cards are `[D, H]`.
- Each player gets 13 cards at the end of the deal.

## Bidding
- All four players bid the number of tricks they think they'll win during the game's session (the hand).
- Bidding starts with player to the left of the dealer and continues clockwise.
- Everyone must bid a number from 0 to 13 after looking at their cards. 
	- A bid of zero is known as a *nil*. The team can get special points if it succeeds and a penalty if it fails.
	- A *blind nil* is when the player declares a *nil* bid before looking at their cards. Again, there are special points if successful and penalty if it fails.
- The bid for the team is derived from the adding together the two members' bids.
	- *Example*: North bids 2 and Souths bids 3, therefore their team has a bid of 5.
- Once the bidding stage is done, no player can change their bid.

## Play
- Player to the left of the dealer starts the first trick.
- The leading player cannot start with a Spade card unless either the player has no more non-Spade cards, or someone broke spades. To break spades means to be the first player to play a Spade card during the hand.
- Game play is clockwise.
- Each player must follow suit if able. If not, then the player can play any card.
- The winner of the trick leads the next trick.

### Winning a Trick
- A trick containing a spade is won by the highest spade played.
- If no spade is played, then the trick is won by the highest card leading suit, meaning the highest card that played the same suit as the leading card.

## Scoring
- When a team takes at least or more tricks than they bid, then they receive a score equal to 10 times the bid. Any additional tricks are called *bags* and are worth an extra one point each.
	- *Example*: Team One bid 5 tricks and won 5 tricks, therefore their score is `current_score + 50`. 
	- *Example*: Team Two bid 6 tricks and won 8 tricks so their score is `current_score + 62`.
- If a team does not fulfill their bid, then they lose 10 points times the number of tricks they bid.
	- *Example*: Team One bid 8 tricks but only won 6 tricks, therefore their score is `current_score - 80`.
- *Sandbagging rule*: Overtricks are known as *bags*. If a team accumulates ten or more bags, then 100 will be deducted from their score. Any bags beyond ten will be carried over to the next cycle of ten overtricks.
	- *Example*: Team One bids 3 tricks and wins 6 tricks. If the number of bags they've accumulated up until that point was 9 bags, then after the trick, they'll have 12 bags, which means they have to add (33 - 100) to their score. Since they have more then ten bags (12 bags) at that point, the extra two bags carry over to the next game, meaning they start off with two bags. 
- If a bid of *nil* is successful by a player, then the team receives 100 points in addition to the points won or lost by the partner of the nil bidder. 
	- *Example*: Player One of Team One successfully bid nil. Player Two of Team One bid three tricks and won four. Therefore, Team One's total score is `current_score + 100 + 31`.
	- *Example*: Player One of Team One successfully bid nil. Player Two of Team One bid five tricks but lost with four tricks. Therefore, Team One's total score is `current_score + 100 - 50`.
- If a bid of *nil* is not successful, then the team loses 100 points and the tricks earned by the nil bidder counts as bags for the team.
	- *Example*: Player One of Team One lost their *nil* bid by two tricks. Player Two bid three tricks and won four. Therefore, Team One's total score is `current_score - 100 + 33`.
	- *Example*: Player One of Team One lost their nil bid by two tricks. Player Two bid five tricks but lost by four. Therefore, Team One's total score is `current_score - 100 - 50`.
- *Blind nil* bids are worth double that of a regular *nil* bid meaning +/- 200 points.
- Once the scoring is finished, if a team ends up with at least 300 points or higher, they win the game. If a team ends up with at least -200 points or lower, they lose the game. If neither team meet these criteria, then we deal cards to the players again and start again, keeping track of the score from previous sessions.

# Card class
A `Card` object is represented by two attributes, a `Rank` and a `Suit`. The provided starter file `Card.h` is pretty self explanatory. Only thing I want to specify is that the comparison operators that we are overloading for the Cards should not be considering the trump suit or lead suit. It is only based on standard card values. Comparison of cards is based on suit first then rank. The `card_less` function on the other hand does consider trump suit and lead suit. Go back to [[#Winning a Trick]] to read on how this should be determined.

# Pack class
Once you finish creating the implementation of the `Card` class, then you can move onto the `Pack` class. A `Pack` object represents a pack of cards. There are different operations that you can act on these pack of card and these are declared in the provided starter file `Pack.h`. 

A input stream used to initialize a Pack would have all 52 Cards in any order using the format `[rank] of [suit]\n`. Below is an example of such an input stream with only the first three lines.
```txt
Two of Hearts
Ace of Spades
Jack of Diamonds
```
