#pragma once
#include<string>
#include"LinkedList.h"
#include"DataField.h"
#include"ListIterator.h"
#include<iostream>
#include<string>
#include<Windows.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<sql.h>
#include<cstring>
using std::string;
class TableHeader {   
public:
    LinkedList<DataField> fields;
	TableHeader(string url, string table);
	void setKey(string name);
    DataField* getKey();
};
TableHeader::TableHeader(string url, string table) {
    string driver ="Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + url + ";";
    string query = "SELECT * FROM " + table;
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    SQLDriverConnectA(dbc, NULL, (SQLCHAR*)driver.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    SQLSMALLINT numCols;
    SQLNumResultCols(stmt, &numCols);
    for (SQLSMALLINT i = 1; i <= numCols; i++) {
        SQLCHAR colName[256];
        SQLSMALLINT nameLen, dataType, decimalDigits, nullable;
        SQLULEN colSize;
        SQLDescribeColA(stmt, i, colName, sizeof(colName), &nameLen, &dataType, &colSize, &decimalDigits, &nullable);
        fields.add(DataField((string)((char*)colName), i));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
}
void TableHeader::setKey(string name) {
    ListIterator<DataField> li(fields);
    while (li.has()) {
        if (li.curr()->header == name) {
            li.curr()->key = true;
        }
        li.inc();
    }
}
DataField* TableHeader::getKey() {
    ListIterator<DataField> li(fields);
    while (li.has()) {
        if (li.curr()->key) {
            return li.curr();
        }
        li.inc();
    }
    return NULL;
}


