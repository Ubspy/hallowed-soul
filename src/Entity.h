#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"

class Entity
{
    public:
        Entity();

        /** Getters and Setters **/
        const sf::Vector2<float>& getPosition() const;
        const sf::Vector2<float>& getVelocity() const;

        sf::Sprite& getSprite();

        const int& getWidth() const;
        const int& getHeight() const;

        /** Main function to update an entity **/
        // deltaTime is the time between the last frame and the current frame
        void update(float deltaTime);

        /** Interface methods with a default implementation, can be overridden, called from update() **/
        virtual void spawn(sf::Vector2<float> spawnLocation);
        virtual void kill();

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

        /** Interface methods that must be overridden **/
        /** Called once a frame from GameManager when each Entity is updated
         * @param deltaTime the time between the last frame and the current frame
         * 
         * Examples of thins to do in here:
         *  - Handle movement or change sprites based on input
         *  - Handle movement or change sprites based on AI
         *
         *  Examples of what NOT to do in here:
         *   - Check for collision
         *   - Draw a sprite using window.draw()
        **/
        virtual void onUpdate(float deltaTime, sf::Vector2<float> player) = 0;

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
         * @param hitEntity The entity being collided with. 
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
         *
         * Will be used for animation, the active sprite is the part of the texture we want to display
         * TODO: Sprite array?
         */
        sf::Sprite _sprite;
};
