#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
/*88888888888888888888888888888888888888888888888888888888888888888
8
8       Jose Moreno
8       02/20/2017
8       Character Interface class
8
8
*888888888888888888888888888888888888888888888888888888888888888888*/
#include <string>
using std::string;
class Character
{
public:
    Character(){ i_ID = -1; }
    virtual ~Character(){}
    virtual int GetID() { return i_ID; }
    virtual void SetID(int val) { i_ID = val; }
    virtual string GetName(){ return s_Name; }
    virtual void SetName( string val ) { s_Name = val; }
    virtual int GetPosY() { return i_posY; }
    virtual void SetPosY( int val ) { i_posY = val; }
    virtual int GetPosX() { return i_posX; }
    virtual void SetPosX( int val ) { i_posX = val; }
    virtual int GetMap() { return i_map; }
    virtual void SetMap( int val ) { i_map = val; }
    virtual int GetStr() { return i_str; }
    virtual void SetStr(int val) { i_str = val; }
    virtual int GetEnd() { return i_end; }
    virtual void SetEnd(int val) { i_end = val; }
    virtual int GetInt() { return i_int; }
    virtual void SetInt( int val ) { i_int = val; }
protected:
    int i_ID;
    string s_Name;
    int i_posY;
    int i_posX;
    int i_map;
    int i_str;
    int i_end;
    int i_int;
};


#endif // CHARACTER_H_INCLUDED
