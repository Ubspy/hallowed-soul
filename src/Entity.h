#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"

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

        /* Spawns the entity in the map. Can be overridden. */
        virtual void spawn(sf::Vector2i spawnLocation);

        /* Kills the entity. Can be overridden. */
        virtual void kill();

        /** Gets this Entity's Sprite. */ 
        sf::Sprite& getSprite();

        /** Called each game tick. Can be overridden */
        virtual void onUpdate();

        /** Called when the collision manager has detected a collision between
         * this entity and another entity.
         * 
         * Examples of things to do in here:
         *   - Update the velocity of the entity
         *   - Set the sprite to something different
         *     (or mark a state change of this Entity so that onDraw can set the sprite)
         * 
         * Examples of things to NOT do in here:
         *   - Draw your sprite to the window.draw()
         * 
         * @param hitEntity The entity being collided with. ONLY GUARANTEED TO BE VALID
         *   FOR THE LIFETIME OF THIS FUNCTION.
         */
        virtual void onCollision(Entity &hitEntity) = 0; 

        /** Called before the Entity is drawn to the screen.
         * 
         * Things to do in here:
         *   - Update the animation frame that your sprite is on
         *   - Change your sprite's position in the world using sprite.setPosition()
         * 
         * Things to NOT do in here (for now):
         *   - Actually draw your sprite to the window using the window.draw() method
         */
        virtual void onDraw();

    protected:
        // Vectors for position and velocity
        sf::Vector2<int> _position;
        sf::Vector2<int> _velocity;

        // Size of this entity
        int _width, _height;
        int _health;

        /** The texture that this entity uses.
         *
         * Could potentially be a spritesheet with multiple frames of an animation.
         * Or could be just one drawing.
         */
        sf::Texture _texture;

        /** The sprite that this entity uses.
         *
         * A sprite is a texture, plus information about which part of the
         * texture to use and where its origin is.
         */
        sf::Sprite _sprite;
};
