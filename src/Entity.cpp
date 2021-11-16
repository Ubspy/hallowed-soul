#include "Entity.h"
#include "GameManager.h"

Entity::Entity(std::vector<Entity*> *entityVec)
{
    // Initialize position and velocity to have a position of <0, 0>
    _position = sf::Vector2<float>(0, 0);
    _velocity = sf::Vector2<float>(0, 0);
 
    // Initialize entity with 0 size, and default health of 100
    _width = 0;
    _height = 0;
    _health = 100;

    // Entity starts as alive
    this->_isAlive = true;

    // Set entity array
    this->_entityVec = entityVec;
}

const sf::Vector2<float>& Entity::getPosition() const
{
    return this->_position;
}

sf::Vector2<float> Entity::getCetnerPosition() const
{
    return sf::Vector2<float>(this->_position.x + this->_width,
            this->_position.y + this->_height);
}

const sf::Vector2<float>& Entity::getVelocity() const
{
    return this->_velocity;
}

const int& Entity::getWidth() const
{
    return this->_width;
}

const int& Entity::getHeight() const
{
    return this->_height;
}

const int& Entity::getHealth() const
{
    return this->_health;
}

void Entity::update(float deltaTime)
{
    // When we update a frame we want to do a few things
    // First we want to check for the health to see if this entity is dead
    if(_health <= 0)
    {
        this->kill();
    }

    // Then we want to update the entity
    this->onUpdate(deltaTime);

    // After the update, we want to update the entity's position based off of it's velocity
    this->_position += this->_velocity * deltaTime;
    if(_position.x<0){_position.x=0;}
    if(_position.x>1450){_position.x=1450;}
    if(_position.y<0){_position.y=0;}
    if(_position.y>1050){_position.y=1050;}

    // The below '/' was added by Diesel, he's a good boy
    // Finally, we draw the entity  /
    this->onDraw();
}

void Entity::doDamage(int damage)
{
    this->_health -= damage;
}

bool Entity::isAlive()
{
    return this->_isAlive;
}

void Entity::kill()
{
    _isAlive = false;
}

void Entity::spawn(sf::Vector2<float> spawnLocation)
{

}

const sf::Sprite& Entity::getSprite() const
{
    return _sprite;
}

void Entity::setTexture(std::string path)
{
    // Load texture in from file
    // TODO: Does this need to by dynamic?
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    //_sprite.setOrigin((int)(_texture.getSize().x / 2), (int)(_texture.getSize().y / 2));

    // Set width and height from the sprite
    this->_width = _texture.getSize().x;
    this->_height = _texture.getSize().y;
}

void Entity::onDraw()
{
    // Default behavior is to just set the sprite's position I guess
    _sprite.setPosition(_position);
}

void Entity::onCollision(Entity &hitEntity)
{

}

Entity* Entity::rayCast(const sf::Vector2<float> &ray)
{
    // Let's get the center point for the source
    sf::Vector2<float> sourceCenter(this->_position.x + this->_width / 2.0,
        this->_position.y + this->_height / 2.0);

/*
#if DEBUG
    // Draw the ray cast line if DEBUG mode is on 
    sf::Vertex line[2];

    line[0].position = sourceCenter;
    line[0].color = sf::Color::Blue;
    line[1].position = sourceCenter + ray;
    line[1].color = sf::Color::Blue;

    this->_debugLines.push_back(line[0]);
    this->_debugLines.push_back(line[1]);
#endif
*/

    for(int i = 0; i < this->_entityVec->size(); i++)
    {
        Entity* currentEntity = this->_entityVec->at(i);

        //printf("%i\n", i); 

        // Skip entity if it's the same as this one
        if(this == currentEntity)
        {
            //printf("SAME ENTITY\n");
            continue;
        }

        // Skip this loop is enemy is dead
        if(!currentEntity->isAlive())
            continue;
    
        //printf("Source: x: %f, y: %f\n", sourceCenter.x, sourceCenter.y);
        //printf("Player: x: %f, y: %f, w: %i, h: %i\n",
        //        currentEntity->getPosition().x, currentEntity->getPosition().y,
        //       currentEntity->getWidth(), currentEntity->getHeight());
        //printf("Ray: x: %f, y: %f\n", ray.x, ray.y);

        // There are four lines to check for intersection here, so we need to check all of them
        // First is the left-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEntity->getPosition().x, (currentEntity->getPosition().y + currentEntity->getHeight()),
                    currentEntity->getPosition().x, currentEntity->getPosition().y))
        {
            /*
            #if DEBUG
                 sf::Vertex line[2];

                 line[0].position = sf::Vector2<float>(currentEntity->getPosition().x,
                         currentEntity->getPosition().y + currentEntity->getHeight());
                 line[0].color = sf::Color::Red;
                 line[1].position = currentEntity->getPosition();
                 line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif
            */

            return currentEntity;
        }

        // Then check the top-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEntity->getPosition().x, currentEntity->getPosition().y,
                    (currentEntity->getPosition().x + currentEntity->getWidth()), currentEntity->getPosition().y))
        {
            /*
            #if DEBUG
                sf::Vertex line[2];

                line[0].position = currentEntity->getPosition();
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2<float>(currentEntity->getPosition().x + currentEntity->getWidth(),
                         currentEntity->getPosition().y);
                line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif
            */

            return currentEntity;
        }

        // Then check the right-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    (currentEntity->getPosition().x + currentEntity->getWidth()), currentEntity->getPosition().y,
                    (currentEntity->getPosition().x + currentEntity->getWidth()), (currentEntity->getPosition().y + currentEntity->getHeight())))
        {
            /*
            #if DEBUG
                sf::Vertex line[2];

                line[0].position = sf::Vector2<float>(currentEntity->getPosition().x + currentEntity->getWidth(),
                         currentEntity->getPosition().y); 
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2<float>(currentEntity->getPosition().x + currentEntity->getWidth(),
                         currentEntity->getPosition().y + currentEntity->getHeight());
                line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif
            */

            return currentEntity;
        }
        
        // Lastly, the bottom-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEntity->getPosition().x, (currentEntity->getPosition().y + currentEntity->getHeight()),
                    (currentEntity->getPosition().x + currentEntity->getWidth()), (currentEntity->getPosition().y + currentEntity->getHeight())))
        {
            /*
            #if DEBUG
                sf::Vertex line[2];

                line[0].position = sf::Vector2<float>(currentEntity->getPosition().x,
                         currentEntity->getPosition().y + currentEntity->getHeight()); 
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2<float>(currentEntity->getPosition().x + currentEntity->getWidth(),
                         currentEntity->getPosition().y + currentEntity->getHeight());
                line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif
            */

            return currentEntity;
        }
    }

    return nullptr;
}

bool Entity::linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    // If the lines intersect, then the intersection point on the x-axis Ix has to be in between x1 and x2, and x3 and x4
    // If point Ix lies outside of either range, then it is not part of one segment, and then isn't on the intersection
    // We want to make sure this interval can exist
    // For the smaller point, we need the max from either interval, but we want the smallest of those two maxes
    // this will be the largest point on the lower interval, the next one will be the smallest point on the larger interval
    if(std::min(std::max(x1, x2), std::max(x3, x4)) < std::max(std::min(x3, x4), std::min(x1, x2)))
    {
        // If the furthest point on line 1 doesn't even reach the min on line two, then this interval doesn't exist
        // Here we want to say they don't interesct
        return false;
    }

    // If both lines are vertival, they only intersect if they're the same value
    if(x1 == x2 && x3 == x4)
    {
        return x1 == x4;
    }

    // To avoid a divide by zero, check for same x values, we can also use an easier algorithm if this is the case
    if(x1 == x2)
    {
        // All we need to do is see if the other line crosses the X point from the vertical line
        // Get the slope
        float slope = (y4 - y3) / (x4 - x3); 

        // We can solve for the intercept, so let's find that
        float intercept = y3 - slope * x3;

        // Find the Y point
        float intersectY = slope * x1 + intercept;

        // Now we can see if Y lies in the Y range 
        return intersectY < std::max(y1, y2) && intersectY > std::min(y1, y2);
    }
    else if(x3 == x4)
    {
        // This is the same idea as x1 == x2, just swap the values around
        float slope = (y2 - y1) / (x2 - x1);
        float intercept = y1 - slope * x1;
        float intersectY = slope * x3 + intercept;
         
        return intersectY < std::max(y3, y4) && intersectY > std::min(y3, y4);
    }

    // Now we want to calculate the slopes of both lines
    // If the two X values are the same, then set the slope to the maximum possible value
    // TODO: Maybe bad for performance to use the max number, idk how floating point math works
    float slope1 = (y2 - y1) / (x2 - x1);
    float slope2 = (y4 - y3) / (x4 - x3);

    // One thing to check here is if the lines are parallel, because if they are then they won't intersect, we check another line
    if(slope1 == slope2)
    {
        return false;
    }

    // Using y = m*x + b, we can solve for b and find the intersepts for line 1 and 2
    float b1 = y1 - slope1 * x1;
    float b2 = y3 - slope2 * x3;

    // We now have the equations for both lines, and we can find their intersect point by setting them equal
    // Iy = m1 * Ix + b1, Iy = m2 * Ix + b2, for some point (Ix, Iy), we can solve for Ix and get it's value 
    // There is no divide by zero here since we checked before if slope1 and slope 2 are the same
    float intersectX = (b2 - b1) / (slope1 - slope2); 

    // Finally, we need to see if this intersectX is in the range we talked about at the top of this function
    // If our intersectX is out of these ranges, there is no intersection on the limited segments
    // If not, then there is an intersection
    return !(intersectX < std::min({x1, x2, x3, x4}) || intersectX > std::max({x1, x2, x3, x4}));
}
