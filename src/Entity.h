#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"

class Entity
{
    public:
        Entity();

        /// Getters and Setters
        /**
         * @brief Getter for entity position
         *
         * @return Entity's position 
         */
        const sf::Vector2<float>& getPosition() const;

        
        /**
         * @brief Getter for entity velocity
         *
         * @return Entity's velocity 
         */
        const sf::Vector2<float>& getVelocity() const;


        /**
         * @brief Getter for entity active sprite
         *
         * @return Sprite to render to window for this entity 
         */
        const sf::Sprite& getSprite() const;


        /**
         * @brief Getter for entity width
         *
         * @return Width of entity 
         */
        const int& getWidth() const;


        /**
         * @brief Getter for entity height
         *
         * @return Height of entity 
         */
        const int& getHeight() const;

        /// Main function to update an entity 

        /**
         * @brief Called from GameManager, will update the entity based off user input
         *
         * @param deltaTime the time between this update and the previous update
         */
        void update(float deltaTime);

        /// Interface methods with a default implementation, can be overridden

        /**
         * @brief Spawns the entity in at a given location
         *
         * @param spawnLocation The location to spawn the entity at
         */
        virtual void spawn(sf::Vector2<float> spawnLocation);

        /**
         * @brief Kills the entity, stops it from being rendered on the scene
         *  and affecting collisions
         */
        virtual void kill();

        /**
         * @brief Called from update, change the active sprite to draw to the scene, and 
         *  set up current sprite for rendering 
         */
        virtual void onDraw();

        /// Interface methods that must be overridden 
        
        /**
         * @brief Called from update, the overridable function for specific entities
         *  to change their members based off user input
         *
         * @param deltaTime The time between this update and the last one
         */
        virtual void onUpdate(float deltaTime) = 0;
        
        /**
         * @brief Called from the game manager after a collision with another entity
         *
         * @param hitEntity The other entity this one collider with
         */
        virtual void onCollision(Entity &hitEntity) = 0;  

    protected:
        // Vectors for position and velocity
        sf::Vector2<float> _position;
        sf::Vector2<float> _velocity;

        // Size of this entity
        int _width, _height;

        // Health of this entity
        int _health;

        // The texture that this entity uses
        // Could potentially be a spritesheet with multiple frames of an animation, 
        // or could be just one drawing
        
        sf::Texture _texture;

        // The sprite that this entity uses.
        // Will be used for animation, the active sprite is the part of the texture
        // we want to display
        // TODO: Sprite array?
        sf::Sprite _sprite;
};
