#pragma once
#include"DataField.h"
#include<string>
using std::string;
class FieldData {
public:
	DataField field;
	string data;
	FieldData() = default;
	FieldData(DataField f, string o);
};
FieldData::FieldData(DataField f, string o) : field(f) {
	data = o;
}
