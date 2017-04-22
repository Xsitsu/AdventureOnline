#include "database.hpp"

#include <iostream>

Database::Database() : is_connected(false)
{

}

Database::~Database()
{
    if (this->IsConnected())
    {
        this->Disconnect();
    }
}

void Database::Connect()
{
    if (this->IsConnected()) throw DatabaseAlreadyConnectedException();

    char filepath[] = "AO.db";

    rc = sqlite3_open(filepath, &db);
    if(rc)
    {
        sqlite3_close(db);
        this->is_connected = false;
        throw DatabaseConnectionFailedException();
    }
    this->is_connected = true;
}

void Database::Disconnect()
{
    if (!this->IsConnected()) throw DatabaseNotConnectedException();

    sqlite3_close(db);

    this->is_connected = false;
}

void Database::CreateAccount(std::string email, std::string password)
{
    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "insert into users values(?, ?, ?);";

    if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 1, email.c_str(), email.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 2, password.c_str(), password.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 3, password.c_str(), password.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_step(ppStmt) != SQLITE_DONE) throw DatabaseException();

    sqlite3_finalize(ppStmt);
}

Account* Database::ReadAccount(std::string email)
{
    Account * account = nullptr;
    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "select rowid, * from users where useremail = ?;";

    if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 1, email.c_str(), email.size(), nullptr))   std::cout << "Error binding email" << std::endl;
    rc = sqlite3_step(ppStmt);
    if ( rc == SQLITE_OK || rc == SQLITE_ROW )
    {
        account = new Account(sqlite3_column_int(ppStmt, 0), reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 1)), reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 2)), reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 3)));
    }

    sqlite3_finalize(ppStmt);
    return account;
}

void Database::UpdateAccount(Account* account)
{
    if( ReadAccount(account->GetEmail())) throw DatabaseDataDoesNotExistException();

    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "UPDATE Users SET UserEmail = ?, UserSalt = ?, UserHash = ? WHERE rowid = ?";

    if ( sqlite3_prepare_v2(db, sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 1, account->GetEmail().c_str(), account->GetEmail().size(), nullptr))   throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 2, account->GetSalt().c_str(), account->GetSalt().size(), nullptr))   throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 3, account->GetHash().c_str(), account->GetHash().size(), nullptr))   throw DatabaseException();
    if ( sqlite3_bind_int(ppStmt, 4, account->GetAccountId())) throw DatabaseException();

    if ( sqlite3_step(ppStmt) != SQLITE_DONE) throw DatabaseException();
    sqlite3_finalize(ppStmt);
}

void Database::DeleteAccount(Account* account)
{
    // ToDo
}

vector<int> Database::ReadPlayerCharacters (std::string email)
{
    sqlite3_stmt * ppStmt = nullptr;
    sqlite3_stmt * Stmt2 = nullptr;
    const char sql_statement[] = "SELECT rowid FROM PlayerChar WHERE UserID = ?;";
    const char sql_statement2[] = "SELECT rowid FROM users WHERE UserEmail = ?;";
    int playerID = 0;
    vector<int> characters;

    if ( sqlite3_prepare_v2(db, sql_statement2, sizeof(sql_statement2), &Stmt2, nullptr) )      throw DatabaseException();
    if ( sqlite3_bind_text(Stmt2, 1, email.c_str(), email.size(), nullptr))   throw DatabaseException();

    rc = sqlite3_step(Stmt2);
    playerID = sqlite3_column_int(Stmt2, 0);
    sqlite3_finalize(Stmt2);

    if ( sqlite3_prepare_v2(db, sql_statement, sizeof(sql_statement), &ppStmt, nullptr) )      throw DatabaseException();
    if ( sqlite3_bind_int(ppStmt, 1, playerID)) throw DatabaseException();


    while (sqlite3_step(ppStmt) != SQLITE_DONE)
    {
        characters.push_back(sqlite3_column_int(ppStmt, 0));
    }

    sqlite3_finalize(ppStmt);

    return characters;

}

Character * Database::ReadCharacterInfo( int ID)
{
    Character * player_character = new Character();
    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "SELECT rowid, * FROM PlayerChar WHERE rowid = ?;";
    sqlite3_stmt * ppStmt2 = nullptr;
    const char sql_statement2[] = "SELECT CharStats.StatValue FROM CharStats WHERE CharID = ?;";

    try
    {
        if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
        if ( sqlite3_bind_int(ppStmt, 1, ID)) throw DatabaseException();

        rc = sqlite3_step(ppStmt);
        if (  rc != SQLITE_ROW ) throw DatabaseReadException();
        else
        {
            player_character->SetCharacterId(sqlite3_column_int(ppStmt,0));
            player_character->SetName(reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 1)));
            player_character->Warp(nullptr, Vector2(sqlite3_column_int(ppStmt, 2), sqlite3_column_int(ppStmt, 3)));
        }
        sqlite3_finalize(ppStmt);
        ppStmt = nullptr;

        if ( sqlite3_prepare_v2(db,sql_statement2, sizeof(sql_statement2), &ppStmt2, nullptr))      throw DatabaseException();
        if ( sqlite3_bind_int(ppStmt2, 1, ID)) throw DatabaseException();
        rc = sqlite3_step(ppStmt2);
        if ( rc!= SQLITE_ROW ) throw DatabaseReadException();
        else
        {
            player_character->SetStrength(sqlite3_column_int(ppStmt2, 0));
        }
        if ( sqlite3_step(ppStmt2) != SQLITE_ROW) throw DatabaseReadException();
        else
        {
            player_character->SetEndurance(sqlite3_column_int(ppStmt2, 0));
        }
        if ( sqlite3_step(ppStmt2)!= SQLITE_ROW) throw DatabaseReadException();
        else
        {
            player_character->SetGender(static_cast<Character::Gender>(sqlite3_column_int(ppStmt2, 0)));
        }
        if ( sqlite3_step(ppStmt2)!= SQLITE_ROW) throw DatabaseReadException();
        else
        {
            player_character->SetSkin(static_cast<Character::Skin>(sqlite3_column_int(ppStmt2, 0)));
        }
        if ( sqlite3_step(ppStmt2)!= SQLITE_ROW) throw DatabaseReadException();
        else
        {
            player_character->SetMaxHealth(sqlite3_column_int(ppStmt2, 0));
        }
        if ( sqlite3_step(ppStmt2)!= SQLITE_ROW) throw DatabaseReadException();
        else
        {
            player_character->SetHealth(sqlite3_column_int(ppStmt2, 0));
        }


        sqlite3_finalize(ppStmt2);
        ppStmt2 = nullptr;
    }
    catch( DatabaseException& problem)
    {
        delete player_character;
        if(ppStmt)
        {
            sqlite3_finalize(ppStmt);
        }
        if(ppStmt2)
        {
            sqlite3_finalize(ppStmt2);
        }
        throw problem;
    }

    return player_character;
}

void Database::CreateCharacter(int accID, Character * toon)
{
    if(toon)
    {
        sqlite3_stmt * statement = nullptr;
        const char characterInsert[] = "INSERT INTO playerchar VALUES( ?, ?, ?, ?, ?)";
        int mapID = 0;
        int posX = toon->GetPosition().x;
        int posY = toon->GetPosition().y;
        int charID = 0;

        if ( sqlite3_prepare_v2(db,characterInsert, sizeof(characterInsert), &statement, nullptr))      throw DatabaseException();
        if ( sqlite3_bind_text(statement, 1, toon->GetName().c_str(), toon->GetName().size(), nullptr))   throw DatabaseException();
        if ( sqlite3_bind_int(statement, 2, accID)) throw DatabaseException();
        if ( sqlite3_bind_int(statement, 3, posX)) throw DatabaseException();
        if ( sqlite3_bind_int(statement, 4, posY)) throw DatabaseException();
        if ( sqlite3_bind_int(statement, 5, mapID)) throw DatabaseException();
        rc = sqlite3_step(statement);
        if ( rc != SQLITE_DONE ) throw DatabaseException();

        charID = sqlite3_last_insert_rowid(db);
        sqlite3_finalize(statement);

        AddCharacterStat(charID, "strength", toon->GetStrength() );
        AddCharacterStat(charID, "endurance", toon->GetEndurance());
        AddCharacterStat(charID, "gender", static_cast<int>(toon->GetGender()));
        AddCharacterStat(charID, "skin", static_cast<int>(toon->GetSkin()));
        AddCharacterStat(charID, "maxhp", toon->GetMaxHealth());
        AddCharacterStat(charID, "hitpoints", toon->GetHealth());
        AddCharacterStat(charID, "hair", static_cast<int>(toon->GetHair()));
        AddCharacterStat(charID, "haircolor", static_cast<int>(toon->GetHairColor()));
    }
}

void Database::AddCharacterStat(int charID, std::string statname, int statValue)
{
    int statID = GetStatID(statname);
    sqlite3_stmt * statement = nullptr;
    const char statInsert[] = "INSERT INTO CharStats VALUES( ?, ?, ?)";

    if ( sqlite3_prepare_v2(db,statInsert, sizeof(statInsert), &statement, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_int(statement, 1, charID)) throw DatabaseException();
    if ( sqlite3_bind_int(statement, 2, statID)) throw DatabaseException();
    if ( sqlite3_bind_int(statement, 3, statValue)) throw DatabaseException();
    if ( sqlite3_step(statement) != SQLITE_DONE) throw DatabaseException();
    //to do
}

int Database::GetStatID(std::string name)
{
    sqlite3_stmt * statement = nullptr;
    const char getStatID[] = "SELECT rowid FROM stat WHERE statname = ?";
    int statID = 0;

    if ( sqlite3_prepare_v2(db,getStatID, sizeof(getStatID), &statement, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_text(statement, 1, name.c_str(), name.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_step(statement) != SQLITE_ROW) throw DatabaseException();
    statID = sqlite3_column_int(statement,0);

    sqlite3_finalize(statement);
    return statID;
}

bool Database::CharacterExists(std::string name)
{
    sqlite3_stmt * statement = nullptr;
    const char getcharacterid[] = "SELECT rowid FROM playerchar WHERE charname = ?";
    if ( sqlite3_prepare_v2(db,getcharacterid, sizeof(getcharacterid), &statement, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_text(statement, 1, name.c_str(), name.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_step(statement) != SQLITE_ROW) return false;
    return true;
}

void Database::DeleteCharacter(std::string name)
{
    sqlite3_stmt * statement = nullptr;
    const char getcharacterid[] = "SELECT rowid FROM playerchar WHERE charname = ?";
    const char deletecharacter[] = "DELETE FROM playerchar WHERE charname = ?";
    const char deletecharacterstats[] = "DELETE FROM charstats WHERE charid = ?";
    int charID = 0;

    if ( sqlite3_prepare_v2(db,getcharacterid, sizeof(getcharacterid), &statement, nullptr))    throw DatabaseException();
    if ( sqlite3_bind_text(statement, 1, name.c_str(), name.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_step(statement) != SQLITE_ROW) throw DatabaseException();
    charID = sqlite3_column_int(statement,0);
    sqlite3_finalize(statement);

    if ( sqlite3_prepare_v2(db,deletecharacter, sizeof(deletecharacter), &statement, nullptr))  throw DatabaseException();
    if ( sqlite3_bind_text(statement, 1, name.c_str(), name.size(), nullptr))   throw DatabaseException();
    if ( sqlite3_step(statement) != SQLITE_DONE)    throw DatabaseException();
    sqlite3_finalize(statement);

    if ( sqlite3_prepare_v2(db,deletecharacterstats, sizeof(deletecharacterstats), &statement, nullptr) )   throw DatabaseException();
    if ( sqlite3_bind_int(statement, 1, charID) )   throw DatabaseException();
    if ( sqlite3_step(statement) != SQLITE_DONE )   throw DatabaseException();
    sqlite3_finalize(statement);
}
