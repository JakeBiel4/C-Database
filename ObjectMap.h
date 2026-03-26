#pragma once
#include"LinkedList.h"
#include"ListIterator.h"
#include"DataField.h"
#include"FieldData.h"
#include<string>
using std::string;
class ObjectMap {
public:
	LinkedList<DataField> fields;
	LinkedList<FieldData> values;
	FieldData* key = nullptr;
	string getFieldByName(string name);
};
string ObjectMap::getFieldByName(string name) {
	string data;
	ListIterator<FieldData> li(values);
	while (li.has()) {
		if (name == li.curr()->field.header) {
			data = li.curr()->data;
			break;
		}
		li.inc();
	}
	return data;
}
