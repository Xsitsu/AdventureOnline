#include "actor.hpp"

#include "map.hpp"

#include <iostream>

Actor::Actor() : actor_manager(nullptr), current_map(nullptr), map_position(0,0), direction(DIR_DOWN), has_nowall(false),
state(nullptr),health(10), max_health(10), strength(0), endurance(0)
{
    this->ChangeState(new ActorStateStand(this));
}

Actor::~Actor()
{

}

void Actor::SetActorManager(ActorManagerBase *manager)
{
    this->actor_manager = manager;
}

ActorManagerBase* Actor::GetActorManager() const
{
    return this->actor_manager;
}

void Actor::EnterMap(Map* map)
{
    if (!map->IsMapLoaded())
    {
        if (map->GetMapManager())
        {
            map->GetMapManager()->RequestMapLoad(map);
        }
    }

    std::list<Character*> char_list = map->GetCharacterList();
    std::list<Character*>::iterator iter;
    for (iter = char_list.begin(); iter != char_list.end(); ++iter)
    {
        Character *ch = *iter;
        Actor *chact = ch;

        if (chact != this && chact->GetActorManager())
        {
            chact->GetActorManager()->SignalMapEnter(chact, this);
        }
    }

    map->HandleActorEnter(this);
    this->current_map = map;
}

void Actor::ExitMap(Map* map)
{
    std::list<Character*> char_list = map->GetCharacterList();
    std::list<Character*>::iterator iter;
    for (iter = char_list.begin(); iter != char_list.end(); ++iter)
    {
        Character *ch = *iter;
        Actor *chact = ch;

        if (chact != this && chact->GetActorManager())
        {
            chact->GetActorManager()->SignalMapLeave(chact, this);
        }
    }

    map->HandleActorLeave(this);
    this->current_map = nullptr;
}

void Actor::Warp(Map* map, Vector2 coords)
{
    bool did_change_maps = (this->current_map != map);
    if (did_change_maps)
    {
        if (this->current_map)
        {
            this->ExitMap(this->current_map);
        }
        this->EnterMap(map);
    }

    this->map_position = coords;

    std::list<Character*> char_list = map->GetCharacterList();
    std::list<Character*>::iterator iter;
    for (iter = char_list.begin(); iter != char_list.end(); ++iter)
    {
        Character *ch = *iter;
        Actor *chact = ch;

        // Want to send to own character as well.
        //if (chact != this && chact->GetActorManager())
        if (chact->GetActorManager())
        {
            chact->GetActorManager()->SignalPosition(chact, this);
        }
    }

    if (this->GetActorManager())
    {
        for (iter = char_list.begin(); iter != char_list.end(); ++iter)
        {
            Character *ch = *iter;
            Actor *chact = ch;

            if (chact != this && chact->GetActorManager())
            {
                this->GetActorManager()->SignalMapEnter(this, chact);
            }
        }
    }

    this->ChangeState(new ActorStateStand(this));
}

void Actor::Turn(Actor::Direction direction)
{
    this->direction = direction;

    std::list<Character*> char_list = this->current_map->GetCharacterList();
    std::list<Character*>::iterator iter;
    for (iter = char_list.begin(); iter != char_list.end(); ++iter)
    {
        Character *ch = *iter;
        Actor *chact = ch;

        if (chact != this && chact->GetActorManager())
        {
            chact->GetActorManager()->SignalTurn(chact, this);
        }
    }

    this->ChangeState(new ActorStateTurn(this));
}

void Actor::Move(Vector2 coords)
{
    Vector2 diff = coords - this->map_position;
    bool can_move = false;
    if (diff == Vector2(1, 0) && this->direction == DIR_RIGHT)
    {
        can_move = true;
    }
    else if (diff == Vector2(-1, 0) && this->direction == DIR_LEFT)
    {
        can_move = true;
    }
    else if (diff == Vector2(0, 1) && this->direction == DIR_DOWN)
    {
        can_move = true;
    }
    else if (diff == Vector2(0, -1) && this->direction == DIR_UP)
    {
        can_move = true;
    }
    else
    {
        /*
        std::cout << "Bad try move: " << diff.x << "/" << diff.y << " :: ";
        if (this->direction == DIR_LEFT)
        {
            std::cout << "Left";
        }
        else if (this->direction == DIR_RIGHT)
        {
            std::cout << "Right";
        }
        else if (this->direction == DIR_UP)
        {
            std::cout << "Up";
        }
        else if (this->direction == DIR_DOWN)
        {
            std::cout << "Down";
        }

        std::cout << std::endl;
        */
    }

    if (!can_move)
    {
        // ToDo: Replace with something like an invalid movement exception.
        throw "BREAK";
    }

    if (this->has_nowall ||
        (this->current_map->CoordsAreInBounds(coords) && this->current_map->GetTile(coords).TileIsWalkable(this)))
    {
        this->map_position = coords;

        std::list<Character*> char_list = this->current_map->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = char_list.begin(); iter != char_list.end(); ++iter)
        {
            Character *ch = *iter;
            Actor *chact = ch;

            if (chact != this && chact->GetActorManager())
            {
                chact->GetActorManager()->SignalMove(chact, this);
            }
        }

        this->ChangeState(new ActorStateWalk(this));
    }
    else
    {
        // ToDo: Replace with valid exception.
        throw "BREAK";
    }

}

void Actor::Attack()
{
    std::list<Character*> char_list = this->current_map->GetCharacterList();
    std::list<Character*>::iterator iter;
    for (iter = char_list.begin(); iter != char_list.end(); ++iter)
    {
        Character *ch = *iter;
        Actor *chact = ch;

        if (chact != this && chact->GetActorManager())
        {
            chact->GetActorManager()->SignalAttack(chact, this);
        }
    }

    this->ChangeState(new ActorStateAttack(this));
}

void Actor::FeignAttack()
{
    this->ChangeState(new ActorStateFeignAttack(this));
}

void Actor::TakeDamage(unsigned short value)
{
    if (this->IsDead()) return;

    if (value < 0)
    {
        value = 0;
    }

    int hp = this->health;
    hp -= value;

    bool did_die = false;
    if (hp <= 0)
    {
        hp = 0;
        did_die = true;
        this->ChangeState(new ActorStateDead(this));
    }

    this->health = hp;

    std::list<Character*> char_list = this->current_map->GetCharacterList();
    std::list<Character*>::iterator iter;
    for (iter = char_list.begin(); iter != char_list.end(); ++iter)
    {
        Character *ch = *iter;
        Actor *chact = ch;

        if (chact->GetActorManager())
        {
            chact->GetActorManager()->SignalTakeDamage(chact, this, value);
            if (did_die && chact != this)
            {
                chact->GetActorManager()->SignalDied(chact, this);
            }
        }
    }
}

bool Actor::IsDead() const
{
    return (this->health < 1);
}

void Actor::SetHealth(unsigned short val)
{
    if (val > this->max_health)
    {
        val = this->max_health;
    }

    this->health = val;

    if (this->current_map)
    {
        std::list<Character*> char_list = this->current_map->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = char_list.begin(); iter != char_list.end(); ++iter)
        {
            Character *ch = *iter;
            Actor *chact = ch;

            if (chact->GetActorManager())
            {
                chact->GetActorManager()->SignalHealth(chact, this);
            }
        }
    }
}


Vector2 Actor::GetPosition() const
{
    return this->map_position;
}

Vector2 Actor::GetDirectionVector() const
{
    if (this->direction == DIR_UP)
    {
        return Vector2(0, -1);
    }
    else if (this->direction == DIR_DOWN)
    {
        return Vector2(0, 1);
    }
    else if (this->direction == DIR_LEFT)
    {
        return Vector2(-1, 0);
    }
    else if (this->direction == DIR_RIGHT)
    {
        return Vector2(1, 0);
    }
    else
    {
        return Vector2(0, 0);
    }
}

Actor::Direction Actor::GetDirection() const
{
    return this->direction;
}

void Actor::SetDirection(Direction direction)
{
    this->direction = direction;
}

bool Actor::GetHasNowall() const
{
    return this->has_nowall;
}

void Actor::SetHasNowall(bool val)
{
    this->has_nowall = val;
}

Map* Actor::GetMap() const
{
    return this->current_map;
}

void Actor::ChangeState(ActorStateBase* state)
{
    if (this->state)
    {
        this->state->Exit();
        delete this->state;
    }

    this->state = state;

    this->state->Enter();
}

void Actor::Update()
{
    this->state->Update();
}

bool Actor::CanMove()
{
    return this->state->CanMove();
}

bool Actor::CanAttack()
{
    return this->state->CanAttack();
}

bool Actor::IsStanding()
{
    return this->state->IsStanding();
}

bool Actor::IsMoving()
{
    return this->state->IsMoving();
}

bool Actor::IsAttacking()
{
    return this->state->IsAttacking();
}

bool Actor::IsDieing()
{
    return this->state->IsDieing();
}

double Actor::GetStatePercentDone()
{
    return this->state->GetPercentDone();
}
