#pragma once
#include"LinkedList.h"
#include"ListIterator.h"
#include"DataField.h"
#include"FieldData.h"
#include<string>
using std::string;
class DataObject {
public:
	LinkedList<DataField> fields;
	LinkedList<FieldData> values;
	FieldData* key = NULL;
	DataObject() = default;
	DataObject(LinkedList<DataField> f);
	void fill(LinkedList<string> f);
	string getFieldByName(string name);
};
DataObject::DataObject(LinkedList<DataField> f) : fields(f) {
	key = NULL;
}
void DataObject::fill(LinkedList<string> f) {
	for (int i = 0; i < f.size(); i++) {
		values.add(FieldData(fields.get(i), f.get(i)));
	}
	ListIterator<DataField> li(fields);
	while (li.has()) {
		if (li.curr()->key) {
			ListIterator<FieldData> lj(values);
			while (lj.has()) {
				if (li.curr()->header == li.curr()->header) {
					key = lj.curr();
					break;
				}
				lj.inc();
			}
			break;
		}
		li.inc();
	}
}
string DataObject::getFieldByName(string name) {
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
