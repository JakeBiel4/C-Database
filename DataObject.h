#pragma once
#include"LinkedList.h"
#include"ListIterator.h"
#include"DataField.h"
#include"FieldData.h"
#include"ObjectMap.h"
#include<string>
using std::string;
class DataObject : public ObjectMap {
public:
	DataObject() = default;
	DataObject(LinkedList<DataField> f);
	void fill(LinkedList<string> f);
};
DataObject::DataObject(LinkedList<DataField> f) {
	fields = f;
	key = nullptr;
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
