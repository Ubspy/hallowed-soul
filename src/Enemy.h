#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
    private:
        int health;
        int locationX;
        int locationY;
        int ammo;
        bool isAlive;
        
    public:
        Enemy();

        void spawn(int x, int y);
        void attack();
        void takeDamage(int damage);
        int getHealth();
        int getLocationX();
        int getLocationY();
        int getAmmo();
        bool getIsAlive();
        void kill();

        ~Enemy();
};

#endif