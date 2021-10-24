#include "TestEntity.h"
#include "Entity.h"

TestEntity::TestEntity()
{
    _texture.loadFromFile("assets/textures/test.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
    _velocity = {5, 1};
}