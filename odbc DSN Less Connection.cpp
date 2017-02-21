#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <cstring>
using namespace std;

void PrintEmployees();
void PrintEmployees(char driver[]);
void ListDrivers(char driver[]);

void main()
{
	char ora_driver[1000] = {0};
	ListDrivers(ora_driver);
	PrintEmployees(ora_driver);

}
void ListDrivers(char ora_driver[])
{
	SQLHENV env;
	SQLCHAR attr[256];
	SQLCHAR driver[256];
	SQLSMALLINT driver_ret;
	SQLSMALLINT attr_ret;
	SQLUSMALLINT direction;
	SQLRETURN ret;
	bool found = false;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

	direction = SQL_FETCH_FIRST;
	while(SQL_SUCCEEDED(ret = SQLDrivers(env, direction, driver, sizeof(driver), &driver_ret, attr, sizeof(attr), &attr_ret)) && !found) 
	{
		direction = SQL_FETCH_NEXT;

		printf("%s - %s\n", driver, attr);

		if(strstr((char *)driver, "OraDb11g"))
			found = true;

		if (ret == SQL_SUCCESS_WITH_INFO) 
			printf("\tdata truncation\n");
	}
	strcpy(ora_driver, (char *)driver);
}
void PrintEmployees(char driver[])
{
	SQLHANDLE henv;
	SQLHANDLE hdbc;
	SQLHANDLE hstmt;
	SDWORD cbQual;
	char* query = "select NPC_Name from tablewise.NPC";
	char ename[100];
	SQLRETURN retcode;
	SQLCHAR OutConnStr[255];
	SQLCHAR InConnStr[512];
	//SQLCHAR driver[256];
	SQLSMALLINT OutConnStrLen;

	HWND desktopHandle = GetDesktopWindow();   // desktop's window handle

	// Building the connection string for a DSN-less connection  
	sprintf((char *)InConnStr, "driver={%s};uid=jose_moreno;pwd=shaedar2123", driver);
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

	// Set the ODBC version environment attribute
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0); 

		// Allocate connection handle
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
		{
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 

			// Set login timeout to 5 seconds
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
			{
				SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

				retcode = SQLDriverConnect( hdbc, desktopHandle, InConnStr, strlen((char*)InConnStr), OutConnStr, 255, &OutConnStrLen, SQL_DRIVER_NOPROMPT);

				// Allocate statement handle
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
				{               
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 

					// Process data
					SQLExecDirect(hstmt, (unsigned char *)query, SQL_NTS);
					SQLBindCol(hstmt, 1, SQL_CHAR, ename, 100, &cbQual);

					while(!SQLFetch(hstmt))
						cout << ename << endl;

					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
					{
						SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
					}

					SQLDisconnect(hdbc);
				}
				else
				{
					//Error Testing Example for Connection
					SQLINTEGER	 i = 0;
					SQLINTEGER	 native;
					SQLCHAR	 state[ 7 ];
					SQLCHAR	 text[256];
					SQLSMALLINT	 len;
					SQLRETURN	 ret;

					do
					{
						ret = SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++i, state, &native, text, sizeof(text), &len );
						if (SQL_SUCCEEDED(ret))
							printf("%s:%ld:%ld:%s\n", state, i, native, text);
					}
					while( ret == SQL_SUCCESS );

					SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
				}
			}
		}
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
}
void PrintCategories()
{
	SQLHANDLE henv;
	SQLHANDLE hdbc;
	SQLHANDLE hstmt;
	SDWORD cbQual;
	char* query = "select lower(ename) from emp";
	//char* query = "delete * from emp";
	char ename[100];

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	SQLConnect(hdbc, (unsigned char *)"Emps", SQL_NTS, 
		(unsigned char *)"scott", SQL_NTS,
		(unsigned char *)"scott", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLExecDirect(hstmt, (unsigned char *)query, SQL_NTS);
	SQLBindCol(hstmt, 1, SQL_CHAR, ename, 100, &cbQual);

	while(!SQLFetch(hstmt))
		cout << ename << endl;

	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_NULL_HANDLE, henv);
}
