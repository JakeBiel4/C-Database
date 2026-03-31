#pragma once
#include"DataTable.h"
#include"DataObject.h"
#include"LinkedList.h"
#include"ListIterator.h"
#include<string>
using std::string;
class Table {
private:
	DataTable table;
public:
	Table(string path, string name, string key);
	DataObject* getByName(string name);
	DataTable* getTable();
};
Table::Table(string path, string name, string key) : table(DataTable(path, name)){
	table.setKey(key);
	table.fill();
}
DataObject* Table::getByName(string name) {
	ListIterator<DataObject> li(table.objects);
	while (li.has()) {
		if (li.curr()->getFieldByName("Name") == name) {
			return li.curr();
		}
		li.inc();
	}
	return nullptr;
}
DataTable* Table::getTable() {
	return &table;
}
