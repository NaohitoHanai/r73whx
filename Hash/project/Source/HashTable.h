#pragma once
#include <string>

class HashTable {
public:
	HashTable();
	~HashTable();
	void Set(std::string name, int value);
	int Get(std::string name);
};