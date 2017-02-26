#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <Character.h>
/*8888888888888888888888888888888888888
    Jose Moreno
    02/20/2017
    PC class implementation
888888888888888888888888888888888888888*/

class PlayerCharacter : public Character
{
    public:
        PlayerCharacter(int PID =0, string name = "", int posY = -1, int posX = -1, int mapID = -1, int strength = -1, int endurance = -1, int intelligence = -1);
        virtual ~PlayerCharacter();
        PlayerCharacter(const PlayerCharacter& other);
        PlayerCharacter& operator=(const PlayerCharacter& other);

        int GetPlayerID() { return i_playerID; }
        void SetPlayerID(int val) { i_playerID = val; }

    protected:
        int i_playerID;

    private:
};

#endif // PLAYERCHARACTER_H
