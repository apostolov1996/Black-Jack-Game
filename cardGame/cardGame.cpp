#include <iostream>
#include <array>
#include <algorithm>
#include<ctime>
#include <random>

enum class CardRank {
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,

	MAX_RANKS
};

enum class CardSuit {
	SUITS_CLUBS,
	SUITS_DIAMONDS,
	SUITS_HEARTHS,
	SUITS_SPADES,

	MAX_SUITS
};

typedef struct {
	CardRank rank{};
	CardSuit suit{};
}Card;


void printCard(const Card &ptrCard) {
	switch (ptrCard.rank) {
	case CardRank::RANK_2:
		std::cout << '2';
		break;
	case CardRank::RANK_3:
		std::cout << '3';
		break;
	case CardRank::RANK_4:
		std::cout << '4';
		break;
	case CardRank::RANK_5:
		std::cout << '5';
		break;
	case CardRank::RANK_6:
		std::cout << '6';
		break;
	case CardRank::RANK_7:
		std::cout << '7';
		break;
	case CardRank::RANK_8:
		std::cout << '8';
		break;
	case CardRank::RANK_9:
		std::cout << '9';
		break;
	case CardRank::RANK_10:
		std::cout << "10";
		break;
	case CardRank::RANK_JACK:
		std::cout << 'J';
		break;
	case CardRank::RANK_QUEEN:
		std::cout << 'Q';
		break;
	case CardRank::RANK_KING:
		std::cout << 'K';
		break;
	case CardRank::RANK_ACE:
		std::cout << 'A';
		break;
	default:
		std::cout << "Invalid input\n";
		break;
	}

	switch (ptrCard.suit) {
	case CardSuit::SUITS_CLUBS:
		std::cout << 'C';
		break;
	case CardSuit::SUITS_DIAMONDS:
		std::cout << 'D';
		break;
	case CardSuit::SUITS_HEARTHS:
		std::cout << 'H';
		break;
	case CardSuit::SUITS_SPADES:
		std::cout << 'S';
		break;
	default:
		std::cout << "Invalid input\n";
		break;
	}
	std::cout << "  ";
}

int getInteger() {
	int integer{};
	while (true) {
		std::cin >> integer;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input, try again.\n";
		}
		else {
			std::cin.ignore(32767, '\n');
			return integer;
		}
	}
}

double getDouble() {
	double doubleNumber{};
	while (true) {
		std::cin >> doubleNumber;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input, try again.\n";
		}
		else {
			std::cin.ignore(32767, '\n');
			return doubleNumber;
		}
	}
}


using deckArray = std::array<Card, (static_cast<int>(CardSuit::MAX_SUITS))*(static_cast<int>(CardRank::MAX_RANKS))>;
deckArray createDeck() {
	deckArray temp;
	int index{ 0 };
	for (int i{ 0 }; i < static_cast<int>(CardRank::MAX_RANKS); i++) {
		for (int j{ 0 }; j < static_cast<int>(CardSuit::MAX_SUITS); j++) {
			temp[index].rank = static_cast<CardRank>(i);
			temp[index].suit = static_cast<CardSuit>(j);
			index++;
		}
	}
	return temp;
}

void printDeck(deckArray &deck) {
	int counter{ 0 };
	for (auto &card : deck) {
		counter++;
		printCard(card);
		if (counter == 13) {
			std::cout << '\n';
			counter = 0;
		}
	}
}

void shuffleDeck(deckArray &deck) {
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(Card &card) {
	// 10, Jack, King and Queen value = 10
	constexpr int kingValue{ 10 };
	// Ace value = 11
	constexpr int aceValue{ 11 };

	if (card.rank <= CardRank::RANK_10) {
		return static_cast<int>(card.rank) + 2;
	}
	switch (card.rank) {
	case CardRank::RANK_JACK:
	case CardRank::RANK_KING:
	case CardRank::RANK_QUEEN:
		return kingValue;
		break;
	case CardRank::RANK_ACE:
		return aceValue;
		break;
	default:
		std::cout << "Invalid value\n";
		return -1;
	    break;
	}

}


int getCard(deckArray &deck, int &cardIndex) {

	// If cardIndex is > deck.size, then we have no more cards in the deck.
	int deckLength = static_cast<int>(deck.size());
	int value{};


	if (cardIndex < deckLength) {
		value=getCardValue(deck.at(cardIndex));
		cardIndex++;
		return value;
	}
	else {
		std::cout << "No more cards in the deck.\n";
		return 0;
	}
}

int getPlayerTurn() {
	std::cout << "\n\n";
	std::cout << "1) Hint - you will get another card and the value of that card is added to your score\n";
	std::cout << "2) Stand - your turn is over, your total score is calculated on the cards you have\n";
	int operation{};
	while (true) {
		std::cout << "Operation: ";
		operation = getInteger();
		if (operation != 1 && operation != 2) {
			std::cout << "Invalid input, please try again.\n";
		}
		else {
			return operation;
		}
	}
}

void playerScoreCalculator(deckArray &deck, int &cardIndex, int &playerScore) {
	std::cout << "Player card on the table: ";
	printCard(deck.at(cardIndex));
	std::cout << '\n';
	playerScore = playerScore + getCard(deck, cardIndex);
}

void dealerScoreCalculator(deckArray &deck, int &cardIndex, int &dealerScore) {
	std::cout << "Dealer card on the table: ";
	printCard(deck.at(cardIndex));
	std::cout << '\n';
	dealerScore = dealerScore + getCard(deck, cardIndex);
}


bool playBlackJack(deckArray &deck) {
	// IF TRUE --- PLAYER WON
	// IF FALSE --- DEALER WON
	
	int cardIndex{ 0 };
	int dealerScore{ 0 };
	int playerScore{ 0 };
	
	std::cout << "\nNEW BLACK JACK GAME STARTED\n\n";

    // 1) Dealer gets the first card.
	std::cout << "DEALER TURN !\n";
	std::cout << "DEALER FIRST CARD\n";
	std::cout << "----------------------------------------------\n";
	dealerScoreCalculator(deck, cardIndex, dealerScore);
	std::cout << "----------------------------------------------\n\n";

	// 2) Player gets two cards to start.
	std::cout << "PLAYER TURN !\n";
	std::cout << "PLAYER FIRST TWO CARDS\n";
	std::cout << "----------------------------------------------\n";
	playerScoreCalculator(deck, cardIndex, playerScore);
	playerScoreCalculator(deck, cardIndex, playerScore);
	std::cout << "----------------------------------------------\n";
    //3) PLAYER TURN:
	   /* The player goes first.
       A player can repeatedly “hit” or “stand”.
       If the player “stands”, their turn is over, and their score is calculated based on the cards they have been dealt.
       If the player “hits”, they get another card and the value of that card is added to their total score.*/
	while (true) {
		std::cout << "FINISH THE GAME OR TAKE THE RISK!\n";
		int playerTurn{ getPlayerTurn() };
		if (playerTurn == 1) {
			std::cout << "----------------------------------------------\n";
			playerScoreCalculator(deck, cardIndex, playerScore);
			std::cout << "----------------------------------------------\n";
		}
		else {
			std::cout << "Your turn is over.\n";
			std::cout << "----------------------------------------------\n\n";
			break;
		}
	}

	// 4) Player controll score.
	   // If the player goes over a score of 21, they bust and lose immediately.
	if (playerScore > 21) {
		return false;
	}
	// 5) Else we start with the dealer turn.
	   /* The dealer goes after the player.
       The dealer repeatedly draws until they reach a score of 17 or more, at which point they stand.
       If the dealer goes over a score of 21, they bust and the player wins immediately.*/
	else {

		std::cout << "DEALER TURN !\n";
		while (dealerScore < 17) {
			std::cout << "----------------------------------------------\n";
			dealerScoreCalculator(deck, cardIndex, dealerScore);
			std::cout << "----------------------------------------------\n";
		}
		if (dealerScore > 21) {
			return true;
		}
		else {
			// Otherwise, if the player has a higher score than the dealer, the player wins. Otherwise, the player loses (we’ll consider ties as dealer wins for simplicity).
			return (playerScore > dealerScore);
		}
	}
}


void printMainMenu() {
	std::cout << "----------------------------------------------\n";
	std::cout << "1) Tutorial - How to play.\n";
	std::cout << "2) Start new game.\n";
	std::cout << "3) See your earnings.\n";
	std::cout << "4) Receive earnings.\n";
	std::cout << "5) Exit.\n";
}

int getMenuOperation() {
	int menuOperation{};
	while (true) {
		std::cout << "Operation: ";
		menuOperation=getInteger();
		if (menuOperation < 1 || menuOperation>5) {
			std::cout << "Invalid input, please try again.\n";
		}
		else {
			return menuOperation;
		}
	}
}

void printInstructions() {
	std::cout << "- The dealer gets one card to start (in real life, the dealer gets two, but one is face down so it doesn’t matter at this point).\n\n";
	std::cout << "- The player gets two cards to start.\n\n";
	std::cout << "- The player goes first.\n\n";
	std::cout << "- A player can repeatedly “hit” or “stand”. \n\n";
	std::cout << "- If the player “stands”, their turn is over, and their score is calculated based on the cards they have been dealt.\n\n";
	std::cout << "- If the player “hits”, they get another card and the value of that card is added to their total score.\n\n";
	std::cout << "- An ace normally counts as a 1 or an 11 (whichever is better for the total score). For simplicity, we’ll count it as an 11 here.\n\n";
	std::cout << "- If the player goes over a score of 21, they bust and lose immediately.\n\n";
	std::cout << "- The dealer goes after the player. \n\n";
	std::cout << "- The dealer repeatedly draws until they reach a score of 17 or more, at which point they stand.\n\n";
	std::cout << "- If the dealer goes over a score of 21, they bust and the player wins immediately.\n\n";
	std::cout << "- Otherwise, if the player has a higher score than the dealer, the player wins. Otherwise, the player loses (we’ll consider ties as dealer wins for simplicity).\n\n";
}

//CONSIDERING THE BETTING UNIT, WHEN YOU BET, IF YOU WIN, WE WILL DOUBLE YOUR MONEY.
double getBet() {
	std::cout << "Insert your bet: ";
	return getDouble();
}

void earningsCalculator(bool &gameResult, double &bet, double &earnings) {
	constexpr double moltiplicator{ 2 };
	if (gameResult == true) {
		earnings = earnings + bet * moltiplicator;
	}
	else {
		earnings = earnings - bet;
	}
}

void printEarnings(double &earnings) {
	std::cout << "Your actual earnings are: " << earnings << "$ \n";
}

void printResult(bool &gameResult, double &earnings) {
	std::cout << "FINAL RESULT OF THE GAME\n";
	std::cout << "----------------------------------------------\n";
	if (gameResult == true) {
		std::cout << "You won !\n";
		printEarnings(earnings);
	}
	else {
		std::cout << "You lost !\n";
		printEarnings(earnings);
	}
	std::cout << "----------------------------------------------\n";
}

void backToTheMain(bool &startGame, double &earnings) {
	int option{};
	while (true) {
		std::cout << "1) Go back to the main menu\n";
		std::cout << "2) Exit and receive earnings.\n";
		std::cout << "Operation: ";
		option = getInteger();
		if (option != 1 && option!=2) {
			std::cout << "Invalid input, please try again.\n";
		}
		break;
	}
	startGame=(option == 1 && earnings>0);
}


int main() {
	deckArray deck{ createDeck() };
	std::cout << "\n----------------------------------------------\n";
	std::cout << "Welcome to our online casino.\n";
	std::cout << "Here you can play the brand new Black Jack Game\n";
	std::cout << "----------------------------------------------\n\n";
	std::cout << "Starting deposit: ";
	double earnings{getDouble()};
	bool startGame = (earnings > 0);
	while (startGame) {
		printMainMenu();
		std::cout << "----------------------------------------------\n";
		int menuOperation{ getMenuOperation() };
		std::cout << "----------------------------------------------\n";
		double bet{};
		bool gameResult{};
		switch (menuOperation) {
		case 1:
			printInstructions();
			backToTheMain(startGame, earnings);
			break;
		case 2:
			shuffleDeck(deck);
			bet = getBet();
			gameResult=playBlackJack(deck);
			earningsCalculator(gameResult, bet, earnings);
			printResult(gameResult, earnings);
			backToTheMain(startGame, earnings);
			break;
		case 3:
			printEarnings(earnings);
			backToTheMain(startGame, earnings);
			break;
		case 4:
			earnings = 0;
			backToTheMain(startGame, earnings);
			break;
		case 5:
			startGame = false;
			std::cout << "Goodbye!\n";
			break;
		default:
			break;
		}
	}
	std::cout << "Your deposit is empty. Please insert money and then you can play a new game.\n";
	return 0;
}