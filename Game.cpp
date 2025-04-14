#include "Game.h"// use move to pot!
#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
    : m_board(b), m_southPlayer(south), m_northPlayer(north), m_currentSide(SOUTH)
{

}
void Game::display() const
{
    int p_N = m_board.beans(NORTH, 0);
    int p_S = m_board.beans(SOUTH, 0);

    cout << "North: " << m_northPlayer->name() << endl;

    for (int i = 1; i <= m_board.holes(); i++)
    {
        
        cout << " " << m_board.beans(NORTH, i);

    }
    cout << endl;
    cout << p_N;
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << "  ";
    }
    cout << p_S;
    cout << endl;
    for (int i = 1; i <= m_board.holes(); i++)
    {
        
        cout << " " << m_board.beans(SOUTH, i);
    }
    cout << endl;

    cout << "SOUTH: " << m_southPlayer->name() << endl;

    cout << endl;


}
void Game::status(bool& over, bool& hasWinner, Side& winner) const 
{
    // Check if all holes on the north side are empty
    if (m_board.beansInPlay(SOUTH) == 0 && m_board.beansInPlay(NORTH) == 0) //signifies the game is over if neither side has any beans
    { 
        over = true;
        int NorthPot = m_board.beans(NORTH, 0);
        int SouthPot = m_board.beans(SOUTH, 0);

        if (NorthPot == SouthPot) 
        {
            hasWinner = false; // Tie game means no winner
        }
        else 
        {
            hasWinner = true; //if the game isnt a tie and the game is over then there is a winner depending on which pot has more
            if (NorthPot > SouthPot) 
            {
                winner = NORTH;
            }
            else if (SouthPot > NorthPot) 
            {
                winner = SOUTH;
            }
            else {
                hasWinner = false; //tie game
            }
        }
    }

    else //the game is not over
    {
        over = false;
        hasWinner = false;
    }
}

int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
bool Game::move(Side s) // check 0 bean case for a side 
{
    bool over;
    bool hasWinner;
    Side winner;
    status(over, hasWinner, winner);
    
    
    // Check if the game is already over
    if (over)
    {
        
        return false;
    }
    int hole = 1; // check if this is an error 
    
    if (s == NORTH)
    {
        //cout << "fdsfds" << endl;
        hole = m_northPlayer->chooseMove(m_board, NORTH);
        cout << "hole chosen " << hole << endl;
        //cout << m_northPlayer->isInteractive() << endl;
        if (m_northPlayer->isInteractive())
        {
            cout << "(NORTH) turn" << endl;
            cout << "Press ENTER to continue..." << endl;
            cin.ignore(); // Wait for ENTER key
        }

    }
    else
    {
        
        hole = m_southPlayer->chooseMove(m_board, SOUTH);
        cout << "hole chosen " << hole << endl;
        if (m_southPlayer->isInteractive())
        {
            cout << "(SOUTH) turn" << endl;
            cout << "Press ENTER to continue..." << endl;
            cin.ignore(); // Wait for ENTER key
            
        }

    }

    //move by sowing 
    Side endSide;
    int endHole;
    m_board.sow(s, hole, endSide, endHole);

    Side opp;
    if (endSide == NORTH)
    {
        opp = SOUTH;
    }
    else
    {
        opp = NORTH;
    }

    // bean to empty spot case taking across hole to pot  
    if (m_board.beans(endSide, endHole) == 1 && m_board.beans(opp, endHole) != 0 && endSide== s)
    {
        if (s == NORTH)
        {

            m_board.moveToPot(NORTH, endHole, NORTH);
            m_board.moveToPot(SOUTH, endHole, NORTH);
        }
        else
        {

            m_board.moveToPot(NORTH, endHole, SOUTH);
            m_board.moveToPot(SOUTH, endHole, SOUTH);
        }
    }

    status(over, hasWinner, winner);

    // Check if the game is already over
    if (over)
    {
        return false;
    }

    if (endHole == 0 && over == false)// starts another move if bean to pot case 
    {
        

        if (endSide == NORTH)
        {
            system("cls");
            display();

            cout << "north extra move" << endl;
            bool on= false;
            while (!on && !over)
            {
                on = move(m_currentSide);
                status(over, hasWinner, winner);
                if (!over)
                {
                    cout << "invalid move (NORTH) AAA" << endl;
                }

            }
            m_currentSide = SOUTH;
        }
        else
        {
            system("cls");
            display();

            cout << "south extra move" << endl;
            
            bool on = false;
            while (!on && !over)
            {
                on = move(m_currentSide);
            
                status(over, hasWinner, winner);
                if (!over)
                {
                    cout << "invalid move (SOUTH) AAA" << endl;
                }
            }
            m_currentSide = NORTH;
        }
    }
    return true;
}

void Game::play()
{
    bool over = false;
    bool hasWinner = 0;
    Side winner;

    while (!over)
    {
        //check empty side case 
        if (m_board.beansInPlay(NORTH) == 0)// rule empty side leads other side to take all of it 
        {
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(NORTH, i, SOUTH);
            }
        }
        if (m_board.beansInPlay(SOUTH) == 0)
        {
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(SOUTH, i, NORTH);
            }
        }

        system("cls");
        display();

        if (m_currentSide == NORTH)
        {
            cout << "north move" << endl;

            while (!move(m_currentSide) && !over)
            {
                status(over, hasWinner, winner);
                if (!over)
                {
                    
                    cout << "invalid move (NORTH)" << endl;
                }
                
            }

            m_currentSide = SOUTH;
        }
        else
        {
            cout << "south move" << endl;
            while (!move(m_currentSide) && !over)
            {
                status(over, hasWinner, winner);
                if (!over)
                {
                    cout << "invalid move (SOUTH)" << endl;
                }

            }

            m_currentSide = NORTH;
        }



        if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0)// rule empty side leads other side to take all of it 
        {
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(SOUTH, i, SOUTH);
            }
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(NORTH, i, NORTH);

            }
        }


        status(over, hasWinner, winner);
    }

    if (hasWinner)
    {
        system("cls"); 
        cout << "GAME OVER" << endl;
        display();

        if (winner == NORTH)
        {
            cout << "NORTH: " << m_northPlayer->name() << " player wins" << endl;
        }
        else
        {
            cout << "SOUTH: " << m_southPlayer->name() << " player wins" << endl;
        }
    }
    else
    {
        cout << "tie game" << endl;
    }

}

/*
int main()
{
    Board b(3, 3);
    b.setBeans(SOUTH, 1, 1);
    b.setBeans(SOUTH, 1, 0);
    b.setBeans(SOUTH, 1, 1);

    Player* p1 = new HumanPlayer("bob");
    Player* p2 = new SmartPlayer("joe");

    Game g(b, p1, p2);
    g.move(SOUTH);
    

    //g.move(NORTH);
    //g.display();
    
    //g.play();


    return 0;
}*/
