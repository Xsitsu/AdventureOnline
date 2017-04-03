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



    SQLCHAR OutConnStr[255];
	SQLCHAR InConnStr[512] = "driver={ODBC Driver 13 for SQL Server};Server=aura.students.cset.oit.edu;Database=AdventureOnline;uid=AdventureOnline_rw;pwd=Pa$$W0rd_0K@y";
	SQLSMALLINT OutConnStrLen;

	HWND desktopHandle = GetDesktopWindow();   // desktop's window handle


	r_ReturnCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Environment);
	if (!(r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)) throw DatabaseConnectionFailedException();


	r_ReturnCode = SQLSetEnvAttr(h_Environment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	if (!(r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)) throw DatabaseConnectionFailedException();


    r_ReturnCode = SQLAllocHandle(SQL_HANDLE_DBC, h_Environment, &h_DBC);
    if (!(r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)) throw DatabaseConnectionFailedException();


    SQLSetConnectAttr(h_DBC, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
    r_ReturnCode = SQLDriverConnect(h_DBC, desktopHandle, InConnStr, strlen((char*)InConnStr), OutConnStr, 255, &OutConnStrLen, SQL_DRIVER_NOPROMPT);
	if (!(r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)) throw DatabaseConnectionFailedException();


	r_ReturnCode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);



    this->is_connected = true;
}

void Database::Disconnect()
{
    if (!this->IsConnected()) throw DatabaseNotConnectedException();

    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
    SQLDisconnect(h_DBC);
    SQLFreeHandle(SQL_HANDLE_DBC, h_DBC);
    SQLFreeHandle(SQL_HANDLE_ENV, h_Environment);

    this->is_connected = false;
}

void Database::CreateAccount(std::string email, std::string password)
{
    bool account_exists = (this->ReadAccount(email) != nullptr);
    if (account_exists) throw DatabaseDataAlreadyExistsException();

    char email_str[255];
    char salt_str[255];
    char hash_str[255];

    SQLLEN caBind = SQL_NTS;
    SQLLEN caBind2 = SQL_NTS;
    SQLLEN caBind3 = SQL_NTS;

    int caemailLen = email.size();
    int casaltLen = password.size();
    int cahashLen = password.size();// + email.size();

    strcpy( email_str, email.c_str() );
    strcpy( salt_str, password.c_str() );           //needs to be replaced with salt string
    //strcpy( hash_str, email.c_str() );              //needs to be replaced with hash string
    strcpy( hash_str, password.c_str() );

    SQLRETURN localRetcode;

    char insertUser[1000] = "{ CALL CreateUser( ?, ? , ?) }";


    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

    SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, caemailLen, 0, email_str, caemailLen, &caBind); // bind email

    SQLBindParameter(h_Statement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, casaltLen, 0, salt_str, casaltLen, &caBind2); // bind salt

    SQLBindParameter(h_Statement, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, cahashLen, 0, hash_str, cahashLen, &caBind3); // bind hash

    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)insertUser, SQL_NTS);

    if (localRetcode != SQL_SUCCESS && localRetcode != SQL_SUCCESS_WITH_INFO)
    {
        throw DatabaseCreateException();
    }
    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
}

Account* Database::ReadAccount(std::string email)
{
    char SQL_Code[1000] = "{CALL ReadUserInfo(?) }";
    SQLLEN cBind = SQL_NTS;
    char email_str[255];
    int emailLen = email.size();
    strcpy(email_str, email.c_str());

    SQLRETURN localRetcode;
    SQLINTEGER sqlInt;
    SDWORD sqlThing;

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

    localRetcode = SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, emailLen, 0, email_str, emailLen, &cBind);

    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, SQL_NTS);

    if (localRetcode == SQL_SUCCESS || localRetcode == SQL_SUCCESS_WITH_INFO)
    {
        unsigned int data_ID;
        //char data_email[255];
        char data_salt[255];
        char data_hash[510];

        localRetcode = SQLFetch(h_Statement);
        if (localRetcode != SQL_SUCCESS && localRetcode != SQL_SUCCESS_WITH_INFO)
        {
            // Account does not exist.
            return nullptr;
        }

        SQLGetData(h_Statement, 1, SQL_INTEGER, &data_ID, sizeof(data_ID), &sqlInt );
        //SQLGetData(h_Statement, 2, SQL_C_CHAR, &data_email, 255, &sqlThing );
        SQLGetData(h_Statement, 2, SQL_C_CHAR, &data_salt, 255, &sqlThing );
        SQLGetData(h_Statement, 3, SQL_C_CHAR, &data_hash, 510, &sqlThing );

        Account* account = new Account(data_ID, email, data_salt, data_hash);
        SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
        return account;
    }
    else if (localRetcode == SQL_NO_DATA)
    {
        // Account does not exist.
        return nullptr;
    }
    else
    {
        throw DatabaseReadException();
    }
    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
}

void Database::UpdateAccount(Account* account)
{
    bool account_exists = (this->ReadAccount(account->GetEmail()) != nullptr);
    if (!account_exists) throw DatabaseDataDoesNotExistException();

    char email_str[255];
    char salt_str[255];
    char hash_str[255];
    int id = account->GetAccountId();

    SQLLEN cBind = SQL_NTS;
    SQLLEN cBind2 = SQL_NTS;
    SQLLEN cBind3 = SQL_NTS;
    SQLLEN cBind4 = SQL_NTS;

    int emailLen = account->GetEmail().size();
    int saltLen = account->GetSalt().size();
    int hashLen = account->GetHash().size();

    strcpy( email_str, account->GetEmail().c_str() );
    strcpy( salt_str, account->GetSalt().c_str() );
    strcpy( hash_str, account->GetHash().c_str() );

    char SQL_Code[1000] = "{CALL UpdateUser(?, ?, ?, ?) }"; //setup command


    SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);//alloc handle

    SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, &cBind); //bind ID

    SQLBindParameter(h_Statement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, emailLen, 0, email_str, emailLen, &cBind2); // bind email

    SQLBindParameter(h_Statement, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, saltLen, 0, salt_str, saltLen, &cBind3); // bind salt

    SQLBindParameter(h_Statement, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, hashLen, 0, hash_str, hashLen, &cBind4); // bind hash

    SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, strlen(SQL_Code));

    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
}

void Database::DeleteAccount(Account* account)
{
    // ToDo
}

vector<int> Database::ReadPlayerCharacters (std::string email)
{
    char SQL_Code[1000] = "{CALL ReadUserCharacters(?) }";
    SQLLEN cBind = SQL_NTS;
    SQLLEN cBind2 = SQL_NTS;
    char email_str[255];
    int emailLen = email.size();
    strcpy(email_str, email.c_str());
    vector<int> characters;

    SQLRETURN localRetcode;
//    SQLINTEGER sqlInt;
//    SDWORD sqlThing;

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

    localRetcode = SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, emailLen, 0, email_str, emailLen, &cBind);

    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, SQL_NTS);

    if (localRetcode == SQL_SUCCESS || localRetcode == SQL_SUCCESS_WITH_INFO)
    {
        int data_ID;
        SQLBindCol(h_Statement, 1, SQL_INTEGER, &data_ID, 1, &cBind2);


        while(!SQLFetch(h_Statement))
        {
            characters.push_back(data_ID);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
        return characters;
    }
    else
    {
        SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
        throw DatabaseReadException();
    }

}

Character * Database::ReadCharacterInfo( int ID)
{
    char SQL_Code[100] = "{CALL ReadCharacterInfo(?) }";
    Character * player_character = new Character();
    int stats[7];
    char name[255];
    SQLLEN cBind = SQL_NTS;
    SQLINTEGER sqlInt[7];
    SDWORD sqlThing;
    stats[6] = ID;

    SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    SQLBindParameter(h_Statement, 1, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_INTEGER, 1, 0, &stats[6], 1, &cBind);
    SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, SQL_NTS);

    SQLFetch(h_Statement);
    SQLGetData(h_Statement, 2, SQL_C_CHAR, &name, 255, &sqlThing );
    SQLGetData(h_Statement, 4, SQL_C_LONG, &stats[0], 1, &sqlInt[0] );
    SQLGetData(h_Statement, 5, SQL_C_LONG, &stats[1], 1, &sqlInt[1] );


    player_character->SetName(name);
    player_character->Warp(nullptr, Vector2(stats[0], stats[1]));


    if(SQLMoreResults(h_Statement) != SQL_NO_DATA)
    {
        SQLFetch(h_Statement);
        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[2], 1, &sqlInt[2] );
        player_character->SetStrength(stats[2]);

        SQLFetch(h_Statement);
        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[3], 1, &sqlInt[3] );
        player_character->SetEndurance(stats[3]);

        SQLFetch(h_Statement);
        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[4], 1, &sqlInt[3] );
        player_character->SetGender(static_cast<Character::Gender>(stats[4]));

        SQLFetch(h_Statement);
        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[5], 1, &sqlInt[3] );
        player_character->SetSkin(static_cast<Character::Skin>(stats[5]));

        SQLFetch(h_Statement);
        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[6], 1, &sqlInt[3] );
        player_character->SetMaxHealth(stats[6]);

        SQLFetch(h_Statement);
        SQLGetData(h_Statement, 3, SQL_C_SHORT, &stats[7], 1, &sqlInt[3] );
        player_character->SetHealth(stats[7]);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);

    return player_character;
}