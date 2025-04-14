#include "Board.h"// put holes connected to n/s pot 

#include <iostream>
#include <cassert>


using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole) 
{
    // Initialize number of holes
    m_holes = nHoles;

    // Create the South Pot and the North holes
    head_S = new Hole;
    tail_N = head_S;

    head_S->beans = 0;
    head_S->id = 0;
    head_S->side = SOUTH;
    head_S->pot = nullptr;
    head_S->across = nullptr;

    for (int i = 0; i < nHoles; i++) 
    {
        Hole* temp = new Hole;
        temp->beans = nInitialBeansPerHole;
        temp->side = NORTH;
        temp->id = nHoles - i;

        tail_N->next = temp;
        tail_N = temp;
    }

    // Create the North pot and South holes
    head_N = new Hole;
    tail_S = head_N;

    head_N->beans = 0;
    head_N->id = 0;
    head_N->side = NORTH;
    head_N->pot = nullptr;
    head_N->across = nullptr;

    for (int i = 1; i <= nHoles; i++) 
    {
        Hole* temp = new Hole;
        temp->beans = nInitialBeansPerHole;
        temp->side = SOUTH;
        temp->id = i;

        tail_S->next = temp;
        tail_S = temp;
    }

    // Link South pot to North last hole and North pot to South first hole
    tail_S->next = head_S;
    tail_N->next = head_N;

    // Link across holes
    Hole* temp_across1 = head_S->next;
    Hole* temp_across2 = head_N->next;

    for (int i = 1; i <= nHoles; i++) 
    {
        for (int j = 1; j <= nHoles; j++) 
        {
            if (temp_across2->id == temp_across1->id) 
            {
                temp_across2->across = temp_across1;
                temp_across2->across->across = temp_across2;
            }
            temp_across1 = temp_across1->next;
        }
    }

    // Linking North holes to North pot
    Hole* p = head_S->next;
    for (int i = 0; i < m_holes; i++) 
    {
        p->pot = head_N;
        p = p->next;
    }

    // Linking South holes to South pot
    p = head_N->next;
    for (int i = 0; i < m_holes; i++) 
    {
        p->pot = head_S;
        p = p->next;
    }
}
int Board::holes() const 
{
    return m_holes;
}
int Board::beans(Side s, int hole) const 
{
    if (s != NORTH && s != SOUTH) 
    {
        return -1;
    }

    if (hole < 0 || hole > m_holes) 
    {
        return -1;
    }

    if (hole == 0) {// pots case 
        if (s == NORTH) 
        {
            return head_N->beans;
        }
        else {
            return head_S->beans;
        }
    }

    Hole* p; // hole case 
    if (s == NORTH) 
    {
        p = head_S->next;
        for (int i = 1; i <= m_holes; i++)
        {
            if (p->id == hole)
            {
                return p->beans;
            }
            p = p->next;
        }
    }
    else 
    {
        p = head_N->next;
        for (int i = 1; i <= m_holes; i++)
        {
            if (p->id == hole)
            {
                return p->beans;
            }
            p = p->next;
        }
    }


    return p->beans;
}
int Board::beansInPlay(Side s) const 
{
    int sum = 0;
    Hole* p = nullptr;

    if (s == NORTH) 
    {
        p = head_S->next;  // Start from the first hole on the SOUTH side
        for (int i = 0; i < m_holes; i++) 
        {
            sum += p->beans;
            p = p->next;
        }
    }
    else if (s == SOUTH) 
    {
        p = head_N->next;  // Start from the first hole on the NORTH side
        for (int i = 0; i < m_holes; i++) 
        {
            sum += p->beans;
            p = p->next;
        }
    }

    return sum;
}
int Board::totalBeans() const
{
    int sum = 0;

    // Count beans in the NORTH side holes
    Hole* current = head_N->next;
    for (int i = 0; i < m_holes; i++)
    {
        sum += current->beans;
        current = current->next;
    }

    // Count beans in the SOUTH side holes
    current = head_S->next;
    for (int i = 0; i < m_holes; i++)
    {
        sum += current->beans;
        current = current->next;
    }

    // Add beans in the pots
    sum += head_N->beans;
    sum += head_S->beans;

    return sum;
}
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) 
{
    if (s == NORTH) 
    {
        Hole* temp = head_S->next;
        for (int i = 0; i < holes(); i++) 
        {
            if (temp->id == hole) {
                break;
            }
            temp = temp->next;
        }

        if (temp->beans == 0 || temp->id == 0 || hole < 0 || hole > holes()) 
        {
            return false;
        }

        int temp_beans = temp->beans;
        temp->beans = 0;
        temp = temp->next;

        for (int i = 0; i < temp_beans; i++) 
        {
            
            if (temp->id == 0 && s != temp->side) {
                temp = temp->next;
                i -= 1;
            }
            else 
            {
                temp->beans += 1;
                if (i != temp_beans - 1)
                {
                    temp = temp->next;
                }
            }
        }

        

        endSide = temp->side;
        endHole = temp->id;
        
        return true;
    }

    if (s == SOUTH) {
        Hole* temp = head_N->next;
        for (int i = 0; i < holes(); i++) 
        {
            
            if (temp->id == hole) {
                break;
            }
            temp = temp->next;
        }

        if (temp->beans == 0 || temp->id == 0 || hole < 0 || hole > holes()) 
        {
            return false;
        }

        int temp_beans = temp->beans;
        temp->beans = 0;
        temp = temp->next;

        for (int i = 0; i < temp_beans; i++) 
        {
            
            if (temp->id == 0 && s != temp->side) 
            {
                temp = temp->next;
                i -= 1;
            }
            else 
            {
                temp->beans += 1;
                if (i != temp_beans-1)
                {
                    temp = temp->next;
                }
                
            }
            
        }

        endSide = temp->side;
        endHole = temp->id;
        return true;
    }

    return false;
}
bool Board::moveToPot(Side s, int hole, Side potOwner) 
{
    if (hole <= 0 || hole > holes() || hole == 0)
    {
        return false;
    }
        

    Hole* temp = nullptr;
    if (s == NORTH)// checks if it is a N/S pot 
    {
        temp = head_S->next;
    }
    else if (s == SOUTH)
    {
        temp = head_N->next;
    }    
    else
    {
        return false;
    }

    while (temp != nullptr) 
    {
        if (temp->id == hole) 
        {
            break;
        }
        temp = temp->next;
    }

    if (temp == nullptr || temp->id == 0)
    {
        return false;
    }
        

    if (potOwner == NORTH)
    {
        head_N->beans += temp->beans;
    }
    else if (potOwner == SOUTH)
    {
        head_S->beans += temp->beans;
    }
    

    temp->beans = 0;
    return true;
}
bool Board::setBeans(Side s, int hole, int beans) 
{
    if (s != NORTH && s != SOUTH) {// changed -1 to false 
        return false;
    }

    if (hole < 0 || hole > m_holes) {
        return false;
    }

    if (hole == 0)// pot case 
    {
        Hole* p;
        if (s == NORTH) {
            p = head_N;
        }
        else
        {
            p = head_S;
        }

        p->beans = beans;
        return true;
    }

    Hole* p; // hole case 
    if (s == NORTH) {
        p = head_S->next;
        for (int i = 1; i <= m_holes; i++)
        {
            if (p->id == hole)
            {
                p->beans= beans;
                return true; 
            }
            p = p->next;
        }
    }
    else {
        p = head_N->next;
        for (int i = 1; i <= m_holes; i++)
        {
            if (p->id == hole)
            {
                p->beans = beans;
                return true;
            }
            p = p->next;
        }
    }

    return false;// added for control path, may be a bug
    
}
Board::Board(const Board& RHS)
{
    
    int nHoles = RHS.holes();
    int nInitialBeansPerHole = 0;


    // Initialize number of holes
    m_holes = nHoles;

    // Create the South Pot and the North holes
    head_S = new Hole;
    tail_N = head_S;

    head_S->beans = 0;
    head_S->id = 0;
    head_S->side = SOUTH;
    head_S->pot = nullptr;
    head_S->across = nullptr;

    for (int i = 0; i < nHoles; i++) {
        Hole* temp = new Hole;
        temp->beans = nInitialBeansPerHole;
        temp->side = NORTH;
        temp->id = nHoles - i;

        tail_N->next = temp;
        tail_N = temp;
    }

    // Create the North pot and South holes
    head_N = new Hole;
    tail_S = head_N;

    head_N->beans = 0;
    head_N->id = 0;
    head_N->side = NORTH;
    head_N->pot = nullptr;
    head_N->across = nullptr;

    for (int i = 1; i <= nHoles; i++) 
    {
        Hole* temp = new Hole;
        temp->beans = nInitialBeansPerHole;
        temp->side = SOUTH;
        temp->id = i;

        tail_S->next = temp;
        tail_S = temp;
    }

    // Link South pot to North last hole and North pot to South first hole
    tail_S->next = head_S;
    tail_N->next = head_N;

    // Link across holes
    Hole* temp_across1 = head_S->next;
    Hole* temp_across2 = head_N->next;

    for (int i = 1; i <= nHoles; i++) 
    {
        for (int j = 1; j <= nHoles; j++) 
        {
            if (temp_across2->id == temp_across1->id) 
            {
                temp_across2->across = temp_across1;
                temp_across2->across->across = temp_across2;
            }
            temp_across1 = temp_across1->next;
        }
    }

    // Linking North holes to North pot
    Hole* p = head_S->next;
    for (int i = 0; i < m_holes; i++) 
    {
        p->pot = head_N;
        p = p->next;
    }

    // Linking South holes to South pot
    p = head_N->next;
    for (int i = 0; i < m_holes; i++) 
    {
        p->pot = head_S;
        p = p->next;
    }

    for (int i = 0; i <= m_holes; i++)
    {
        setBeans(NORTH, i, RHS.beans(NORTH, i));
        setBeans(SOUTH, i, RHS.beans(SOUTH, i));
    }

    
}
Board::~Board()
{
    Hole* p_N = head_N;
    Hole* p_S = head_S;

    for (int i = 0; i <= holes(); i++)
    {
        
        Hole* temp1 = p_N;
        Hole* temp2 = p_S;

        p_N = p_N->next;
        p_S = p_S->next;

        delete temp1;
        delete temp2;
    }

}




/*void Board::print() const // deete this!
{
    int p_N = beans(NORTH, 0);
    int p_S = beans(SOUTH, 0);

    cout << "North" << endl;

    for (int i = 1; i <= holes(); i++)
    {
        
        cout << " " << beans(NORTH, i);

    }
    cout << endl;
    cout << p_N;
    for (int i = 1; i <= holes(); i++)
    {
        cout << "  ";
    }
    cout << p_S;
    cout << endl;
    for (int i = 1; i <= holes(); i++)
    {
        
        cout << " " << beans(SOUTH, i);
    }
    cout << endl;

    cout << "SOUTH" << endl;

    cout << endl;
}*/

/*int main()
{
    Board b(3, 0);

    b.setBeans(SOUTH, 1, 3);
    
    Side s;
    int e;
    
    b.sow(SOUTH, 1, s, e);

    assert(b.beans(SOUTH, 2) == 1 && b.beans(SOUTH, 3) == 1 && b.beans(SOUTH, 0) == 1 );

    b.print();
    
    
    
    
    //b.print();

    //cout << "end side: " << s << "NORTH is"<<NORTH<< "   end hole: " << e << endl;
    


    

    return 0;
}*/