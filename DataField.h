#pragma once
#include<string>
using std::string;
class DataField {
public:
	string header;
	bool key = NULL;
	int location = NULL;
	DataField() = default;
	DataField(string h, int l);
};
DataField::DataField(string h, int l) {
	header = h;
	location = l;
	key = false;
}

