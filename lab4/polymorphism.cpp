#include <iostream>

using namespace std;

class Enemy {
    protected: 
        int aPower; 
    public: 
        void setAttackPower(int a)
        {
            this->aPower = a; 
        }
        virtual void attack(){
            cout << "im a ! " << endl;
        }
};

class Ninja : public Enemy
{
    public:
        void attack()
        {
            cout << "Ninja inflicted " << aPower << " damage." << endl;
        }
};
class Monster : public Enemy
{
    public:
        void attack()
        {
            cout << "The monster has smacked you for " << aPower << " damage! Run!" << endl;
        }
};


int main ()
{
    Ninja n; 
    Monster m;
    Enemy *enemy1 = &n; 
    Enemy *enemy2 = &m; 
    enemy1->setAttackPower(29); 
    
    n.attack(); 
    n.setAttackPower(0); 
    n.attack(); 
    m.setAttackPower(50); 
    m.attack(); 
    Enemy e; 
    enemy1->attack(); 
    enemy2->attack(); 

    e.attack(); 
    return 0;
}