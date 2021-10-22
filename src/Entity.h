#include "SFML/System/Vector2.hpp"

class Entity
{
    public:
        Entity();

        sf::Vector2<int> getPosition();
        sf::Vector2<int> getVelocity();

        int getWidth();
        int getHeight();

        // Main function to update an entity
        void update();

        // Pure virtual functions needs to be overriden
        virtual void onCollision(Entity* hitEntity) = 0; 
        virtual void onUpdate() = 0;

        // Virtual functions for basic entity actions that can be overridden
        virtual void spawn(sf::Vector2<int> spawnLocation);
        virtual void kill();
        virtual void onDraw();

    protected:
        // Vectors for position and velocity
        sf::Vector2<int> _position;
        sf::Vector2<int> _velocity;

        // Size of this entity
        int _width, _height;
        int _health;
};
