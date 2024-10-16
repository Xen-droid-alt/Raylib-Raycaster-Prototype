#include "Global.h"
#include "Entity.h"

baseEntity::baseEntity(Vector2 position, float angle) : position(position), angle(angle)
{
    
}

void baseEntity::Update()
{
    // Entity Update
}

void baseEntity::Draw()
{
    // Draw Entity
}

player::player(Vector2 pos, float angle) : baseEntity{ pos, angle } 
{

}

void player::Update()
{
    
}

void player::Draw()
{
    DrawRectangleV(
        { position.x - 5, position.y - 5 },
        { playerSize, playerSize },
        BLUE
    );     //This is our player...
}

item::item(Vector2 pos) : baseEntity{ pos, angle }
{

}

void item::Update()
{

}

void item::Draw()
{
    DrawRectangleV(
        { position.x - 5, position.y -5 },
        { itemSize, itemSize },
        GREEN
    );
}

enemy::enemy(Vector2 pos, float angle) : baseEntity{ pos, angle }
{

}

void enemy::Update()
{

}

void enemy::Draw()
{
    DrawRectangleV(
        { position.x - 10, position.y - 10},
        { enemySize, enemySize },
        RED
    );
}