#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

#include "Board.h"
#include "Side.h"
#include <string>
//#include <vector>
//#include <cstdlib> // for rand() and srand()
//#include <ctime> // for time()

//Place your Player class definition here, as well as the definitions for the HumanPlayer, BadPlayer, and SmartPlayer classes.


class Player
{
public:
    Player(std::string name);
    std::string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();

private:
    std::string m_name;
};
class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name);
    bool isInteractive() const override;
    int chooseMove(const Board& b, Side s) const override;
};
class BadPlayer : public Player {
public:
    BadPlayer(std::string name);
    bool isInteractive() const override;
    int chooseMove(const Board& b, Side s) const override;
};

class SmartPlayer : public Player {
public:
    SmartPlayer(std::string name);
    bool isInteractive() const override;
    int chooseMove(const Board& b, Side s) const override;

    private:
    int evaluate(const Board b, Side s, int hole, int max, const Side actual) const;
    //int evaluate(const Board& b, Side s, int hole) const;
    //int evaluateMove(const Board& b, Side s, Side currentSide, int hole, int depth) const {

    //int evaluate(const Board& b, Side s);
};



#endif