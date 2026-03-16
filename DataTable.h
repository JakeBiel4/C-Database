#pragma once
#include<string>
#include"LinkedList.h"
#include"ListIterator.h"
#include"TableHeader.h"
#include"DataObject.h"
#include"DataField.h"
#include<Windows.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<sql.h>
#include<cstring>
using std::string;
class DataTable {
private:
	string url;
	string tableName;
public:
	TableHeader header;
	LinkedList<DataObject> objects;
	DataTable(string u, string t);
	void setKey(string n);
	void fill();
    DataField* getKey();
};
DataTable::DataTable(string u, string t) : header(TableHeader(u, t)) {
	url = u;
	tableName = t;
}
void DataTable::setKey(string n) {
	header.setKey(n);
}
void DataTable::fill() {
    string keyName;
    ListIterator<DataField> li(header.fields);
    while (li.has()) {
        if (li.curr()->key) {
            keyName = li.curr()->header;
        }
        li.inc();
    }
    if (keyName.empty()) {
        header.fields.first()->data.key = true;
        keyName = header.fields.first()->data.header;
    }
    string driver ="Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + url + ";";
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    SQLDriverConnectA(dbc, NULL, (SQLCHAR*)driver.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    string query = "SELECT " + keyName + " FROM " + tableName;
    SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    LinkedList<string> keys;
    SQLCHAR buffer[256];
    SQLLEN indicator;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
        keys.add((string)((char*)buffer));
    }
    SQLFreeStmt(stmt, SQL_CLOSE);
    ListIterator<string> lj(keys);
    while (lj.has()) {
        LinkedList<string> fields;
        string get = "SELECT * FROM [" + tableName + "] WHERE [" + keyName + "] = " + *lj.curr();
        SQLFreeStmt(stmt, SQL_CLOSE);
        SQLExecDirectA(stmt, (SQLCHAR*)get.c_str(), SQL_NTS);
        SQLSMALLINT colCount;
        SQLNumResultCols(stmt, &colCount);
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            for (int i = 1; i <= colCount; i++) {
                SQLCHAR buff[256];
                SQLLEN indc;
                SQLGetData(stmt, i, SQL_C_CHAR, buff, sizeof(buff), &indc);
                if (indc != SQL_NULL_DATA) {
                    fields.add(string((char*)buff));
                }
            }
        }
        SQLFreeStmt(stmt, SQL_CLOSE);
        DataObject dO(header.fields);
        dO.fill(fields);
        objects.add(dO);
        lj.inc();
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
}
DataField* DataTable::getKey() {
    return header.getKey();
}
