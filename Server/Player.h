#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using std::string;

class Player
{
    public:
        Player(int, string , string , string);
        virtual ~Player();
        Player(const Player& other);
        Player& operator=(const Player& other);

        string GetEmailAddress() { return s_emailAddress; }
        void SetEmailAddress(string val) { s_emailAddress = val; }
        string GetSalt() { return s_salt; }
        void SetSalt(string val) { s_salt = val; }
        string GetHash() { return s_hash; }
        void SetHash(string val) { s_hash = val; }
        int GetID() { return i_ID; }
        void SetID( int val ) { i_ID = val; }

    protected:

    private:
        int    i_ID;
        string s_emailAddress;
        string s_salt;
        string s_hash;
};

#endif // PLAYER_H
