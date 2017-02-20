#include "DB_Bridge.h"
#include <iostream>
//#include <string.h>>
DB_Bridge::DB_Bridge()
{
    Player * newPlayer = new Player(-1, "Jose@oit.edu", "salt", "hash");
    char query[1000] = "execute CreateUser ";

    //build command for creating user
    strcat(query, newPlayer->GetEmailAddress().c_str());
    strcat(query, ", ");
    strcat(query, newPlayer->GetSalt().c_str());
    strcat(query, ", ");
    strcat(query, newPlayer->GetHash().c_str());
    delete newPlayer;

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

					SQLExecDirect(h_Statement, (unsigned char *)query, SQL_NTS);

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
    char query[1000] = "execute CreateUser ";

    //build command for creating user
    strcat(query, newPlayer->GetEmailAddress().c_str());
    strcat(query, ", ");
    strcat(query, newPlayer->GetSalt().c_str());
    strcat(query, ", ");
    strcat(query, newPlayer->GetHash().c_str());

    //debug code
    std::cout << query << std::endl;

    //localRetcode = SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);
    //std::cout << localRetcode << std::endl;
    localRetcode = SQLExecDirect(h_Statement, (unsigned char *)query, SQL_NTS);
    std::cout << localRetcode << std::endl;

    return (int)localRetcode;
}
