#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
#include <iostream>

using namespace std;



int main()
{
	

	int holes=0;
	int beans=0;
	cout << "Welcome to mancala " << endl;
	cout << "enter # holes" << endl;
    cin >> holes;
	cout << "enter # beans" << endl;
    cin >> beans;
	Board b(holes, beans);// board declaration 

    Player* p1;
    Player* p2;
    int d = 0;
    string name;

    cout << "enter Player South name" << endl; 
    cin >> name; 

	cout << "Player South: select player type (1: Human, 2: bad computer, 3: smart computer" << endl;
    cin >> d; 
    if (d == 1)
    {
        p1 = new HumanPlayer(name);
    }
    else if (d == 2)
    {
        p1 = new BadPlayer(name);
    }
    else 
    {
        p1 = new SmartPlayer(name);
    }

    cout << "enter Player North name" << endl;
    cin >> name;

    cout << "Player North: select player type (1: Human, 2: bad computer, 3: smart computer" << endl;
    cin >> d;

    if (d == 1)
    {
        p2 = new HumanPlayer(name);
    }
    else if (d == 2)
    {
        p2 = new BadPlayer(name);
    }
    else
    {
        p2 = new SmartPlayer(name);
    }

	//p1 = new HumanPlayer("bob");// player declaration 
	//p2 = new SmartPlayer("joe");
	Game g(b, p1, p2);// game declaration 
	g.play();


}

/*
int main()
{
    Board b(3, 4);

    Player* p1 = new HumanPlayer("bob");
    Player* p2 = new SmartPlayer("joe");

    //cout<<p2->chooseMove(b, NORTH)<<endl;
    //b.setBeans(SOUTH, 0, 1);
    //b.setBeans(SOUTH, 1, 1);
    //b.setBeans(SOUTH, 2, 8);
    //b.setBeans(SOUTH, 3, 6);

    //b.setBeans(NORTH, 0, 2);
    //b.setBeans(NORTH, 1, 1);
    //b.setBeans(NORTH, 2, 0);
    //b.setBeans(NORTH, 3, 5);

    //b.print();

    //cout << p2->chooseMove(b, NORTH) << endl;


    Game g(b, p1, p2);
    
    
    //g.play();
}*/