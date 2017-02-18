#ifndef DB_BRIDGE_H
#define DB_BRIDGE_H

#include<windows.h>
#include<sql.h>
#include<sqlext.h>


class DB_Bridge
{
    public:
        DB_Bridge();
        ~DB_Bridge();
        SQLRETURN GetReturnCode();

    protected:
        SQLHANDLE h_Enviornment;
        SQLHANDLE h_DBC;
        SQLHANDLE h_Statement;
        SQLRETURN r_ReturnCode;

    private:
};

#endif // DB_BRIDGE_H
