#include "Player.h"
#include "VectorUtil.h"
#include <cmath>
#include <iostream>

Player::Player(std::vector<Entity*> *entityVec) : Entity(entityVec)
{
    // Initialize movement vector to <0, 0>
    this->_moveVec = sf::Vector2<float>(0, 0);
    this->_dodgeVec = sf::Vector2<float>(0, 0);
    
    this->_lastAttackTime = 0;
    setTexture("assets/textures/player.png");

    _isRed = false;
    _redTime = 0;

    srand(time(0));
}

// Pure virtual function from the Entity class
void Player::onUpdate(float deltaTime)
{
    // updating red at the start
    _redTime -= deltaTime;
    if(_redTime <= 0)
    {
        _isRed = false;
    }

    // At this point, we want to slow down if we are not currently moving 
    // We want to individually check each movement axis to see if we need to slow them
    this->_velocity.x = this->checkDeadMoveAxis(this->_velocity.x, this->_moveVec.x,
            (VectorUtil::getVectorMagnitude(this->_velocity) > this->_moveSpeed) ? 
            (this->_dodgeFriction * this->_friction) : this->_friction, deltaTime);
    this->_velocity.y = this->checkDeadMoveAxis(this->_velocity.y, this->_moveVec.y,
            (VectorUtil::getVectorMagnitude(this->_velocity) > this->_moveSpeed) ? 
            (this->_dodgeFriction * this->_friction) : this->_friction, deltaTime);

    // If there is movement on both axes, then we want to do something special
    if(this->_moveVec.x != 0 && this->_moveVec.y != 0)
    {
        // We want to get the magnitude of the moveVector to make sure we're not moving
        // more when moving diagonally vs laterally
        sf::Vector2<float> moveVecUnit = VectorUtil::getUnitVector(this->_moveVec);  

        // Set the current velocity to the movement vector
        // We want to multiply by the private move speed var so we don't move at
        // a snail's pace, this can be edited for better feeling movement before compile
        this->_velocity.x = (abs(this->_velocity.x + moveVecUnit.x * this->_friction *
            deltaTime)) > this->_moveSpeed ? (this->_velocity.x < 0 ? -this->_moveSpeed :
            this->_moveSpeed) : this->_velocity.x + moveVecUnit.x * this->_friction * deltaTime;       

        this->_velocity.y = (abs(this->_velocity.y + moveVecUnit.y * this->_friction * 
            deltaTime)) > this->_moveSpeed ? (this->_velocity.y < 0 ? -this->_moveSpeed :
            this->_moveSpeed) : this->_velocity.y + moveVecUnit.y * this->_friction * deltaTime;
    }  
 
    if(this->_dodgeVec.x != 0 || this->_dodgeVec.y != 0)
    {
        // TODO: There needs to be a better way to call this function
        this->_dodgeVec.x = this->checkDeadMoveAxis(this->_dodgeVec.x, 0, this->_dodgeFriction,
                deltaTime);
        this->_dodgeVec.y = this->checkDeadMoveAxis(this->_dodgeVec.y, 0, this->_dodgeFriction,
                deltaTime);

        this->_velocity += this->_dodgeVec;
    } 

    // Only if the current move vector is non zero
    if(this->_moveVec.x != 0 || this->_moveVec.y != 0)
    {
        // Set previous move vector for dodging
        this->_lastMoveVec = this->_moveVec;
    }

    // Update time since last attack
    this->_lastAttackTime += deltaTime;

    // Reset the movement vector to <0, 0>
    this->_moveVec = sf::Vector2<float>(0, 0);
}

void Player::onDraw()
{
    switch (_currentMoveState)
    {
        case MoveState::Moving:
        {
            std::cout << "Current state: Moving\n";
            break;
        }
        case MoveState::Attacking:
        {
            std::cout << "Current state: Attacking\n";
            break;
        }
        case MoveState::AttackTriggered:
        {
            std::cout << "Current state: AttackTriggered\n";
            break;
        }
        case MoveState::Dodging:
        {
            std::cout << "Current state: Dodging\n";
            break;
        }
    }
    std::cout << "row: " << animationData.currentFrame.y << " col: " << animationData.currentFrame.x << "\n";
}

EntityType Player::getEntityType()
{
    return EntityType::PLAYER;
}

float Player::checkDeadMoveAxis(float velAxis, float moveAxis, float friction, float deltaTime)
{
    if(moveAxis == 0) 
    {
        // We want to decrease the x and y components of velocity by the friction each frame
        if(abs(velAxis) - friction * deltaTime >= this->_deadZone)
        {
            return velAxis + (velAxis > 0 ? -friction : friction) * deltaTime;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        // I'm sorry, this is so fucking gross
        // TODO: Fix this mess
        return (abs(velAxis + moveAxis * this->_friction * deltaTime)) >
            this->_moveSpeed / VectorUtil::getVectorMagnitude(this->_moveVec) ?
            (velAxis < 0 ? -this->_moveSpeed : this->_moveSpeed) /
            VectorUtil::getVectorMagnitude(this->_moveVec) :
            velAxis + moveAxis * this->_friction * deltaTime;
    }
}

void Player::onCollision(Entity &hitEntity)
{

}

void Player::moveInDirection(sf::Vector2<float> moveDir)
{
    // We want to round the product of the given moveDir
    this->_moveVec += moveDir;

    // We also want to tell the player it was given input, as to now slow its input down
    // this->_currentMoveState = MoveState::Moving;
}

void Player::dodgeInDirection(sf::Vector2<float> dodgeDir)
{
    // We don't want to dodge if the velocity is near zero
    if(VectorUtil::getVectorMagnitude(this->_velocity) > this->_deadZone)
    {
        // The first thing we want to do is set the dodge vector now
        // We need to get the dodge vector from the last frame since dodge is processed before
        // the moveVec is set
        this->_dodgeVec = VectorUtil::getUnitVector(this->_lastMoveVec) * this->_dodgeSpeed;

        // When we dodge, we want to set the state of movement to dodging 
        // this->_currentMoveState = MoveState::Dodging;
    }
}

void Player::spawn(sf::Vector2<float> spawnLocation)
{
    this->_position = spawnLocation;
}

void Player::attack()
{
    _currentMoveState = AttackTriggered;
    Entity* hitEntity = this->rayCast(this->_lastMoveVec * this->_attackRange);

    if(hitEntity == nullptr)
    {
        printf("NULLPTR\n");
    }
    else if(hitEntity->getEntityType() == EntityType::ENEMY)
    {
        printf("HITHITHIT\n");
    }

    if(this->_lastAttackTime >= this->_attackTime && hitEntity != nullptr)
    {
        hitEntity->doDamage((rand()%12)+(rand()%12)+12);

        // Reset time since last attack
        this->_lastAttackTime = 0;
    }
}

void Player::counter()
{
    
}

bool Player::isDodging()
{
    return this->_currentMoveState == MoveState::Dodging;
}

bool Player::isRed()
{
    return _isRed;
}

void Player::doDamage(int damage)
{
    this->_health -= damage;
    _redTime = 0.5;
    _isRed = true;
}

const sf::Vector2<float>& Player::getLastMoveDirection() const
{
    return this->_lastMoveVec;
}

float Player::getAttackRange() const
{
    // We want to return the attack range plus the distance from the center of the 
    // player sprite to the edge, this is because if we ever change the size of the
    // sprite the attack range should be adjusted accordingly
    return this->_attackRange + this->_width / 2.0f;
}
