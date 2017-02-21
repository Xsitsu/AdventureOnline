#include "DB_Bridge.h"
#include <iostream>
#include <stdio.h>

DB_Bridge::DB_Bridge()
{
	SQLCHAR OutConnStr[255];
	SQLCHAR InConnStr[512] = "driver={ODBC Driver 13 for SQL Server};Server=aura.students.cset.oit.edu;Database=AdventureOnline;uid=AdventureOnline_rw;pwd=Pa$$W0rd_0K@y";
	//SQLCHAR driver[256];
	SQLSMALLINT OutConnStrLen;

	HWND desktopHandle = GetDesktopWindow();   // desktop's window handle

											   // Building the connection string for a DSN-less connection
	//sprintf((char *)InConnStr, "driver={ODBC Driver 13 for SQL Server}; Server=aura.students.cset.oit.edu;Database=AdventureOnline;uid=AdventureOnline_rw;pwd=Pa$$W0rd_0K@y", driver);
	//cout << InConnStr << endl;
	r_ReturnCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Enviornment);

	// Set the ODBC version environment attribute
	if (r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)
	{
		r_ReturnCode = SQLSetEnvAttr(h_Enviornment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);

		// Allocate connection handle
		if (r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)
		{
			r_ReturnCode = SQLAllocHandle(SQL_HANDLE_DBC, h_Enviornment, &h_DBC);

			// Set login timeout to 5 seconds
			if (r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)
			{
				SQLSetConnectAttr(h_DBC, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

				r_ReturnCode = SQLDriverConnect(h_DBC, desktopHandle, InConnStr, strlen((char*)InConnStr), OutConnStr, 255, &OutConnStrLen, SQL_DRIVER_NOPROMPT);

				// Allocate statement handle
				if (r_ReturnCode == SQL_SUCCESS || r_ReturnCode == SQL_SUCCESS_WITH_INFO)
				{
					r_ReturnCode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);


					//SQLDisconnect(h_DBC);
				}
				else
				{
					//Error Testing Example for Connection
					SQLINTEGER	 i = 0;
					SQLINTEGER	 native;
					SQLCHAR	 state[7];
					SQLCHAR	 text[256];
					SQLSMALLINT	 len;
					SQLRETURN	 ret;

					do
					{
						ret = SQLGetDiagRec(SQL_HANDLE_DBC, h_DBC, ++i, state, &native, text, sizeof(text), &len);
						//if (SQL_SUCCEEDED(ret))
							//cout << state << ' ' << i << ' ' << native << ' ' << text << endl;//printf("%s:%ld:%ld:%s\n", state, i, native, text);
					} while (ret == SQL_SUCCESS);

					//SQLFreeHandle(SQL_HANDLE_DBC, h_DBC);
				}
			}
		}
		//SQLFreeHandle(SQL_HANDLE_ENV, h_Enviornment);
	}
}

DB_Bridge::~DB_Bridge()
{
    SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
    SQLDisconnect(h_DBC);
    SQLFreeHandle(SQL_HANDLE_DBC, h_DBC);
    SQLFreeHandle(SQL_HANDLE_ENV, h_Enviornment);
    //dtor
}

SQLRETURN DB_Bridge::GetReturnCode()
{
    return r_ReturnCode;
}

int DB_Bridge::CreatePlayer(Player * newPlayer)
{
    SQLRETURN localRetcode;
    SQLINTEGER sqlInt;
    int localID = 0;
    char getID[1000] = "select userid from users where UserEmail =";
    char insertUser[1000] = "INSERT INTO Users(UserEmail, UserSalt, UserHash) VALUES(";

    //build command for creating user
    strcat(insertUser, "'");
    strcat(insertUser, newPlayer->GetEmailAddress().c_str());
    strcat(insertUser, "','");
    strcat(insertUser, newPlayer->GetSalt().c_str());
    strcat(insertUser, "','");
    strcat(insertUser, newPlayer->GetHash().c_str());
    strcat(insertUser, "')");

    //build command to get UserID
    strcat(getID, "'");
    strcat(getID, newPlayer->GetEmailAddress().c_str());
    strcat(getID, "'");
    //debug code
    std::cout << insertUser << std::endl << getID << std::endl;

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    //std::cout << localRetcode << std::endl;
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)insertUser, SQL_NTS);
    std::cout << localRetcode << std::endl;

    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)getID, SQL_NTS);
    SQLFetch(h_Statement);
    SQLGetData(h_Statement, 1, SQL_INTEGER, &localID, sizeof(localID), &sqlInt );
    newPlayer->SetID(localID);

    return (int)localRetcode;
}

Player DB_Bridge::ReadPlayer( string eMail)
{

    char getUser[1000] = "select * from users where UserEmail =";
    int localID;
    char localEmail[255];
    char localSalt[255];
    char localHash[510];
    SQLRETURN localRetcode;
    SQLINTEGER sqlInt;
    SDWORD sqlThing;

    strcat(getUser, "'");
    strcat(getUser, eMail.c_str());
    strcat(getUser, "'");

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)getUser, SQL_NTS);
    SQLFetch(h_Statement);
    SQLGetData(h_Statement, 1, SQL_INTEGER, &localID, sizeof(localID), &sqlInt );
    SQLGetData(h_Statement, 2, SQL_C_CHAR, &localEmail, 255, &sqlThing );
    SQLGetData(h_Statement, 3, SQL_C_CHAR, &localSalt, 255, &sqlThing );
    SQLGetData(h_Statement, 4, SQL_C_CHAR, &localHash, 510, &sqlThing );

    return Player(localID, localEmail , localSalt, localHash);
}

int DB_Bridge::UpdatePlayer(Player * morphling)
{
    SQLRETURN localRetcode;
    char updatePlayer[1000] = "UPDATE Users SET UserEmail =";
    char ita[1000];

    std::cout << "ID : " << ita << std::endl;

    //build command
    snprintf(ita, 1000, "%d",morphling->GetID());
    strcat(updatePlayer, "'");
    strcat(updatePlayer, morphling->GetEmailAddress().c_str());
    strcat(updatePlayer, "', UserSalt = '");
    strcat(updatePlayer, morphling->GetSalt().c_str());
    strcat(updatePlayer, "', UserHash = '");
    strcat(updatePlayer, morphling->GetHash().c_str());
    strcat(updatePlayer, "' WHERE Users.UserID =");
    strcat(updatePlayer, ita);

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)updatePlayer, SQL_NTS);
    std::cout << localRetcode << std::endl;

    return (int)localRetcode;
}

int DB_Bridge::DeletePlayer(Player* oldbie)
{
    SQLRETURN localRetcode;
    char deletePlayer[1000] = "DELETE FROM Users WHERE UserID =";
    char localID[100];

    //build command
    snprintf(localID, 100, "%d", oldbie->GetID());
    strcat(deletePlayer, localID);

    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)deletePlayer, SQL_NTS);

    return (int)localRetcode;
}

int DB_Bridge::CreatePlayerCharacter(PlayerCharacter * newChar)
{
    SQLRETURN localRetcode;
    SQLINTEGER sqlInt;
    int localID = 0;
    char itoa[100];
    char insertChar[1000] = "INSERT INTO PlayerChar(CharName, UserID, Position_X, Position_Y, MapID) OUTPUT Inserted.CharID VALUES(";

    //build command for creating user
    strcat(insertChar, "'");
    strcat(insertChar, newChar->GetName().c_str());
    strcat(insertChar, "',");

    snprintf(itoa, 100, "%d", newChar->GetPlayerID());
    strcat(insertChar, itoa);
    strcat(insertChar, ",");

    snprintf(itoa, 100, "%d", newChar->GetPosX());
    strcat(insertChar, itoa);
    strcat(insertChar, ",");

    snprintf(itoa, 100, "%d", newChar->GetPosY());
    strcat(insertChar, itoa);
    strcat(insertChar, ",");

    snprintf(itoa, 100, "%d", newChar->GetMap());
    strcat(insertChar, itoa);
    strcat(insertChar, ")");


    localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    //std::cout << localRetcode << std::endl;
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)insertChar, SQL_NTS);
    std::cout << "CharacterCreation Code: " << localRetcode << std::endl;

    SQLFetch(h_Statement);
    SQLGetData(h_Statement, 1, SQL_INTEGER, &localID, sizeof(localID), &sqlInt );
    newChar->SetID(localID);

    //setting strength
    localID = GetStatID("strength");
    SetCharStat(localID, newChar->GetID(), newChar->GetStr());

    //setting endurance
    localID = GetStatID("endurance");
    SetCharStat(localID, newChar->GetID(), newChar->GetEnd());

    //setting intelligence
    localID = GetStatID("intelligence");
    SetCharStat(localID, newChar->GetID(), newChar->GetEnd());

    return (int)localRetcode;
}

int DB_Bridge::GetStatID(string name)
{
    int localID;
    char findStat[1000] = "SELECT statID FROM STATS WHERE statName =";
    SQLINTEGER sqlInt;

    strcat(findStat, " '");
    strcat(findStat, name.c_str());
    strcat(findStat, "'");

    SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    SQLExecDirect(h_Statement, (unsigned char*)findStat, SQL_NTS);

    SQLFetch(h_Statement);
    SQLGetData(h_Statement, 1, SQL_INTEGER, &localID, sizeof(localID), &sqlInt);

    return localID;
}

void DB_Bridge::SetCharStat(int StatID, int CharID, int StatValue)
{

}
