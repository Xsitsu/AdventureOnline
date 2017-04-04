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
    if ( sqlite3_bind_text(ppStmt, 1, email.c_str(), email.size(), nullptr))   std::cout << "Error binding email" << std::endl;
    if ( sqlite3_bind_text(ppStmt, 2, password.c_str(), password.size(), nullptr))   std::cout << "Error binding salt" << std::endl;
    if ( sqlite3_bind_text(ppStmt, 3, password.c_str(), password.size(), nullptr))   std::cout << "Error binding hash" << std::endl;
    if ( sqlite3_step(ppStmt)) std::cout << "Error executing statement" << std::endl;

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
        account = new Account(sqlite3_column_bytes(ppStmt, 0), reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 1)), reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 2)), reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 3)));
        std::cout << account->GetAccountId() << " email: " << account->GetEmail() << " salt: " << account->GetSalt() << " hash: " << account->GetHash() << std::endl;
    }

    sqlite3_finalize(ppStmt);
    return account;
}

void Database::UpdateAccount(Account* account)
{
    if( ReadAccount(account->GetEmail())) throw DatabaseDataDoesNotExistException();

    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "UPDATE Users SET UserEmail = ?, UserSalt = ?, UserHash = ? WHERE rowid = ?";

    if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_text(ppStmt, 1, account->GetEmail().c_str(), account->GetEmail().size(), nullptr))   std::cout << "Error binding email" << std::endl;
    if ( sqlite3_bind_text(ppStmt, 2, account->GetSalt().c_str(), account->GetSalt().size(), nullptr))   std::cout << "Error binding salt" << std::endl;
    if ( sqlite3_bind_text(ppStmt, 3, account->GetHash().c_str(), account->GetHash().size(), nullptr))   std::cout << "Error binding hash" << std::endl;
    if ( sqlite3_bind_int(ppStmt, 4, account->GetAccountId())) std::cout << "Error binding account ID" << std::endl;

    if ( sqlite3_step(ppStmt)) std::cout << "Error executing statement" << std::endl;
    sqlite3_finalize(ppStmt);
}

void Database::DeleteAccount(Account* account)
{
    // ToDo
}

vector<int> Database::ReadPlayerCharacters (int playerID)
{
    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "SELECT PlayerChar.CharID FROM PlayerChar WHERE UserID = ?;";
    vector<int> characters;

    if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();
    if ( sqlite3_bind_int(ppStmt, 1, playerID)) std::cout << "Error binding account ID" << std::endl;

    while (!sqlite3_step(ppStmt))
    {
        characters.push_back(sqlite3_column_bytes(ppStmt, 1));
    }

    sqlite3_finalize(ppStmt);
    if(characters.empty())
    {
        throw DatabaseReadException();
    }
    return characters;
//    char SQL_Code[1000] = "{CALL ReadUserCharacters(?) }";
//    SQLLEN cBind = SQL_NTS;
//    SQLLEN cBind2 = SQL_NTS;
//    char email_str[255];
//    int emailLen = email.size();
//    strcpy(email_str, email.c_str());
//    vector<int> characters;
//
//    SQLRETURN localRetcode;
////    SQLINTEGER sqlInt;
////    SDWORD sqlThing;
//
//    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
//
//    localRetcode = SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, emailLen, 0, email_str, emailLen, &cBind);
//
//    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, SQL_NTS);
//
//    if (localRetcode == SQL_SUCCESS || localRetcode == SQL_SUCCESS_WITH_INFO)
//    {
//        int data_ID;
//        SQLBindCol(h_Statement, 1, SQL_INTEGER, &data_ID, 1, &cBind2);
//
//
//        while(!SQLFetch(h_Statement))
//        {
//            characters.push_back(data_ID);
//        }
//        SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
//        return characters;
//    }
//    else
//    {
//        SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
//        throw DatabaseReadException();
//    }

}

Character * Database::ReadCharacterInfo( int ID)
{
    Character * player_character = new Character();
    sqlite3_stmt * ppStmt = nullptr;
    const char sql_statement[] = "SELECT rowid, * FROM PlayerChar WHERE CharID = ?;";
    sqlite3_stmt * ppStmt2 = nullptr;
    const char sql_statement2[] = "SELECT CharStats.StatValue FROM CharStats WHERE CharID = ?;";

    if ( sqlite3_prepare_v2(db,sql_statement2, sizeof(sql_statement2), &ppStmt2, nullptr))      throw DatabaseException();
    if ( sqlite3_prepare_v2(db,sql_statement, sizeof(sql_statement), &ppStmt, nullptr))      throw DatabaseException();

    if ( sqlite3_step(ppStmt)) std::cout << "Error executing statement" << std::endl;
    else
    {
        player_character->SetCharacterId(ID);
        player_character->SetName(reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 2)));
        player_character->Warp(nullptr, Vector2(sqlite3_column_bytes(ppStmt, 4), sqlite3_column_bytes(ppStmt, 5)));
    }

    if ( sqlite3_step(ppStmt2)) std::cout << "Error executing statement" << std::endl;
    else
    {
        player_character->SetStrength(sqlite3_column_bytes(ppStmt, 1));
    }
    if ( sqlite3_step(ppStmt2)) std::cout << "Error executing statement2" << std::endl;
    else
    {
        player_character->SetEndurance(sqlite3_column_bytes(ppStmt, 1));
    }
    if ( sqlite3_step(ppStmt2)) std::cout << "Error executing statement2" << std::endl;
    else
    {
        player_character->SetGender(static_cast<Character::Gender>(sqlite3_column_bytes(ppStmt, 1)));
    }
    if ( sqlite3_step(ppStmt2)) std::cout << "Error executing statement2" << std::endl;
    else
    {
        player_character->SetSkin(static_cast<Character::Skin>(sqlite3_column_bytes(ppStmt, 1)));
    }
    if ( sqlite3_step(ppStmt2)) std::cout << "Error executing statement2" << std::endl;
    else
    {
        player_character->SetMaxHealth(sqlite3_column_bytes(ppStmt, 1));
    }
    if ( sqlite3_step(ppStmt2)) std::cout << "Error executing statement2" << std::endl;
    else
    {
        player_character->SetHealth(sqlite3_column_bytes(ppStmt, 1));
    }

    sqlite3_finalize(ppStmt);
    sqlite3_finalize(ppStmt2);

    return player_character;
//    char SQL_Code[100] = "{CALL ReadCharacterInfo(?) }";
//    Character * player_character = new Character();
//    int stats[7];
//    char name[255];
//    SQLLEN cBind = SQL_NTS;
//    SQLINTEGER sqlInt[7];
//    SDWORD sqlThing;
//    stats[6] = ID;
//
//    SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
//    SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_INTEGER, 1, 0, &stats[6], 1, &cBind);
//    SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, SQL_NTS);
//
//    SQLFetch(h_Statement);
//    SQLGetData(h_Statement, 2, SQL_C_CHAR, &name, 255, &sqlThing );
//    SQLGetData(h_Statement, 4, SQL_C_LONG, &stats[0], 1, &sqlInt[0] );
//    SQLGetData(h_Statement, 5, SQL_C_LONG, &stats[1], 1, &sqlInt[1] );
//
//
//    player_character->SetName(name);
//    player_character->Warp(nullptr, Vector2(stats[0], stats[1]));
//
//
//    if(SQLMoreResults(h_Statement) != SQL_NO_DATA)
//    {
//        SQLFetch(h_Statement);
//        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[2], 1, &sqlInt[2] );
//        player_character->SetStrength(stats[2]);
//
//        SQLFetch(h_Statement);
//        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[3], 1, &sqlInt[3] );
//        player_character->SetEndurance(stats[3]);
//
//        SQLFetch(h_Statement);
//        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[4], 1, &sqlInt[3] );
//        player_character->SetGender(static_cast<Character::Gender>(stats[4]));
//
//        SQLFetch(h_Statement);
//        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[5], 1, &sqlInt[3] );
//        player_character->SetSkin(static_cast<Character::Skin>(stats[5]));
//
//        SQLFetch(h_Statement);
//        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[6], 1, &sqlInt[3] );
//        player_character->SetMaxHealth(stats[6]);
//
//        SQLFetch(h_Statement);
//        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[7], 1, &sqlInt[3] );
//        player_character->SetHealth(stats[7]);
//    }
//    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
//
//    return player_character;
}
