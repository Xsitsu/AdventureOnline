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
    if ( sqlite3_step(ppStmt)) throw DatabaseException();

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
    if ( rc == 0 || rc == 100 )
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

    if ( sqlite3_step(ppStmt)) throw DatabaseException();
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


    while (sqlite3_step(ppStmt) != 101)
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

    if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_int(ppStmt, 1, ID)) throw DatabaseException();

    rc = sqlite3_step(ppStmt);
    if (  rc != 100 ) throw DatabaseReadException();
    else
    {
        player_character->SetCharacterId(sqlite3_column_int(ppStmt,0));
        player_character->SetName(reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 1)));
        player_character->Warp(nullptr, Vector2(sqlite3_column_int(ppStmt, 3), sqlite3_column_int(ppStmt, 4)));
    }
    sqlite3_finalize(ppStmt);

    if ( sqlite3_prepare_v2(db,sql_statement2, sizeof(sql_statement2), &ppStmt2, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_int(ppStmt2, 1, ID)) throw DatabaseException();
    rc = sqlite3_step(ppStmt2);
    if ( rc!= 100 ) throw DatabaseReadException();
    else
    {
        player_character->SetStrength(sqlite3_column_int(ppStmt2, 0));
    }
    if ( sqlite3_step(ppStmt2) != 100) throw DatabaseReadException();
    else
    {
        player_character->SetEndurance(sqlite3_column_int(ppStmt2, 0));
    }
    if ( sqlite3_step(ppStmt2)!= 100) throw DatabaseReadException();
    else
    {
        player_character->SetGender(static_cast<Character::Gender>(sqlite3_column_int(ppStmt2, 0)));
    }
    if ( sqlite3_step(ppStmt2)!= 100) throw DatabaseReadException();
    else
    {
        player_character->SetSkin(static_cast<Character::Skin>(sqlite3_column_int(ppStmt2, 0)));
    }
    if ( sqlite3_step(ppStmt2)!= 100) throw DatabaseReadException();
    else
    {
        player_character->SetMaxHealth(sqlite3_column_int(ppStmt2, 0));
    }
    if ( sqlite3_step(ppStmt2)!= 100) throw DatabaseReadException();
    else
    {
        player_character->SetHealth(sqlite3_column_int(ppStmt2, 0));
    }


    sqlite3_finalize(ppStmt2);

    return player_character;
}
