
#include "Player.h"
#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
const int MAX_DEPTH = 100;

using namespace std;

Player::Player(string name)
{
    m_name = name;
}
string Player::name() const
{
    return m_name;
}
bool Player::isInteractive() const
{
    return false; // Assuming Player is not interactive by default
}
Player::~Player() {}

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}
bool HumanPlayer::isInteractive() const {
    return true; // HumanPlayer is interactive
}
int HumanPlayer::chooseMove(const Board& b, Side s) const {
    int hole;

    cout << "Enter a hole number to make a move: ";
    cin >> hole;
    /*if (b.beans(s, hole) > 0) {
        return hole;
    }
    else
    {
        return -1;
    }*/

    return hole;
}

BadPlayer::BadPlayer(std::string name) : Player(name)
{

}
bool BadPlayer::isInteractive() const {
    return false; // BadPlayer is not interactive
}
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    for (int i = 1; i <= b.holes(); i++)
    {
        if (b.beans(s, i) != 0)
        {
            return i;
        }
    }

    return -1;
}

SmartPlayer::SmartPlayer(std::string name) : Player(name) {}
bool SmartPlayer::isInteractive() const
{
    return false; // SmartPlayer is not interactive
}

/*int SmartPlayer::chooseMove(const Board& b, Side s) const
{

    return 1;
}*/


int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    
    int holes = b.holes();
    int bestHole = 1;
    int bestScore = 1;

    Board copy(b);

    // Iterate over each hole to find the best move
    for (int hole = 1; hole <= holes; hole++) {
        if (b.beans(s, hole) > 0) {
            //int score = evaluate(copy, s, hole, 0, hole);
            int score = evaluate(copy, s, hole, 0, s);

            // Update the best move if the current score is better
            if (score > bestScore) {
                bestHole = hole;
                bestScore = score;
            }
        }
    }

    return bestHole;
}
/*
int SmartPlayer::evaluate(Board b, Side s, int hole, int max, const Side actual) const
{
    
    if (b.beansInPlay(s) == 0 || max == 0) // ends game return pot num
    {
        if (s == actual)
        {
            Side endSide;
            int endHole=-1;
            for (int i = 1; i <= b.holes(); i++)
            {
                Board temp(b);
                

                b.sow(actual, i, endSide, endHole);

            }
            if (endHole == 0)
            {
                return b.beans(s, 0)  + b.beansInPlay(actual) + 10;
            }
        }
        
        Side opp2;
        if (actual == NORTH)
        {
            opp2=SOUTH;
        }
        else
        {
            opp2 = NORTH;
        }

        return b.beans(s, 0)+b.beansInPlay(actual);    
    }

    
    
    Side endSide;
    int endHole;
    b.sow(s, hole, endSide, endHole);

    Side opp = actual;
    if (s == NORTH)
    {
        opp = SOUTH;
    }
    else
    {
        s = NORTH;
    }

    // bean to empty spot case taking across hole to pot  
    if (b.beans(endSide, endHole) == 1 && b.beans(opp, endHole) != 0)
    {
        if (s == NORTH)
        {

            b.moveToPot(NORTH, endHole, NORTH);
            b.moveToPot(SOUTH, endHole, NORTH);
        }
        else
        {

            b.moveToPot(NORTH, endHole, SOUTH);
            b.moveToPot(SOUTH, endHole, SOUTH);
        }
    }

    //capture case 
    if (b.beans(endSide, endHole) == 1 && b.beans(opp, endHole) != 0)
    {
        if (s == NORTH)
        {

            b.moveToPot(NORTH, endHole, NORTH);
            b.moveToPot(SOUTH, endHole, NORTH);
        }
        else
        {

            b.moveToPot(NORTH, endHole, SOUTH);
            b.moveToPot(SOUTH, endHole, SOUTH);
        }
    }

    //int bestHole = -1;
    int bestScore = 1;
    int score = 1;

    for (int i = 1; i <= b.holes(); i++)
    {
        if (b.beans(s, i) != 0)// possible move
        {
            if (s == NORTH)
            {
                score =evaluate(b, opp, i, max - 1, actual);

            }
            else
            {
                score =evaluate(b, opp, i, max - 1, actual);

            }

            if (score > bestScore) 
            {
                
                bestScore = score;
            }

        }


    }

    return 1;// for g32 compiler 

}
*/

int SmartPlayer::evaluate(Board b, Side s, int hole, int max, const Side actual) const
{
    if (b.beansInPlay(s) == 0 || max == 0) {// ends game return pot num

        if (s == actual) {
            Side endSide;
            int endHole = -1;
            for (int i = 1; i <= b.holes(); i++) {
                Board temp(b);
                b.sow(actual, i, endSide, endHole);
            }
            if (endHole == 0) {
                return  b.beans(s, 0) + b.beansInPlay(actual) - b.beans(opponent(s), 0) - b.beansInPlay(opponent(actual)) + 50;
            }
        }


        return b.beans(s, 0) + b.beansInPlay(actual) - b.beans(opponent(s), 0) - b.beansInPlay(opponent(actual));
    }

    Side endSide;
    int endHole;
    b.sow(s, hole, endSide, endHole);

    Side opp = actual;
    if (s == NORTH) {
        opp = SOUTH;
    }
    else {
        s = NORTH;
    }
    //capture case
    if (b.beans(endSide, endHole) == 1 && b.beans(opp, endHole) != 0) {

        if (s == NORTH) {


            b.moveToPot(NORTH, endHole, NORTH);
            b.moveToPot(SOUTH, endHole, NORTH);
            return  b.beans(s, 0) + b.beansInPlay(actual) - b.beans(opponent(s), 0) - b.beansInPlay(opponent(actual)) + 100;
        }
        else {


            b.moveToPot(NORTH, endHole, SOUTH);
            b.moveToPot(SOUTH, endHole, SOUTH);
            return  b.beans(s, 0) + b.beansInPlay(actual) - b.beans(opponent(s), 0) - b.beansInPlay(opponent(actual)) + 100;
        }
    }

    int bestScore = 1;
    int score = 1;

    for (int i = 1; i <= b.holes(); i++) {

        if (b.beans(s, i) != 0) {// possible move  

            if (s == NORTH) {

                score = evaluate(b, opp, i, max - 1, actual);

            }
            else {

                score = evaluate(b, opp, i, max - 1, actual);

            }

            if (score > bestScore) {


                bestScore = score;
            }

        }


    }
    return 1;
}



/*int main()
{
    Board b(3, 3);
    
    b.setBeans(SOUTH, 1, 6);
    b.setBeans(SOUTH, 2, 3);
    b.setBeans(SOUTH, 3, 3);

    b.setBeans(NORTH, 1, 1);
    b.setBeans(NORTH, 2, 2);
    b.setBeans(NORTH, 3, 3);
    b.print();
    //b.print();

    //cout << "fdds" << endl;

    Player* p = new SmartPlayer("Bob");
    cout << p->chooseMove(b, NORTH) << endl;
    //cout << "SOUTH: move " << p->chooseMove(b, SOUTH);
    //cout<<p->evaluate(b, NORTH, 1, 5, SOUTH)<<endl;

}*/


