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

    SQLRETURN localRetcode;
    SQLINTEGER sqlInt;
    char insertUser[1000] = "INSERT INTO Users(UserEmail, UserSalt, UserHash) VALUES(";
    strcat(insertUser, "'");
    strcat(insertUser, email.c_str());
    strcat(insertUser, "','");
    strcat(insertUser, password.c_str());
    strcat(insertUser, "','");
    strcat(insertUser, password.c_str());
    strcat(insertUser, "')");

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)insertUser, SQL_NTS);

    if (localRetcode != SQL_SUCCESS && localRetcode != SQL_SUCCESS_WITH_INFO)
    {
        throw DatabaseCreateException();
    }
}

Account* Database::ReadAccount(std::string email)
{
    char SQL_Code[1000] = "select * from users where UserEmail =";

    SQLRETURN localRetcode;
    SQLINTEGER sqlInt;
    SDWORD sqlThing;

    strcat(SQL_Code, "'");
    strcat(SQL_Code, email.c_str());
    strcat(SQL_Code, "'");

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)SQL_Code, SQL_NTS);

    if (localRetcode == SQL_SUCCESS || localRetcode == SQL_SUCCESS_WITH_INFO)
    {
        unsigned int data_ID;
        char data_email[255];
        char data_salt[255];
        char data_hash[510];

        localRetcode = SQLFetch(h_Statement);
        if (localRetcode != SQL_SUCCESS && localRetcode != SQL_SUCCESS_WITH_INFO)
        {
            // Account does not exist.
            return nullptr;
        }

        SQLGetData(h_Statement, 1, SQL_INTEGER, &data_ID, sizeof(data_ID), &sqlInt );
        SQLGetData(h_Statement, 2, SQL_C_CHAR, &data_email, 255, &sqlThing );
        SQLGetData(h_Statement, 3, SQL_C_CHAR, &data_salt, 255, &sqlThing );
        SQLGetData(h_Statement, 4, SQL_C_CHAR, &data_hash, 510, &sqlThing );

        Account* account = new Account(data_ID, data_email, data_salt, data_hash);
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
}

void Database::UpdateAccount(Account* account)
{
    bool account_exists = (this->ReadAccount(account->GetEmail()) != nullptr);
    if (!account_exists) throw DataDoesNotExistException();

    // ToDo
}

void Database::DeleteAccount(Account* account)
{
    // ToDo
}
