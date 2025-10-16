#include "HashTable.h"
#include <vector>

struct HashNode {
    std::string label;
    int value;
};
int capacity = 1;
int size = 2;
int used = 0;
std::vector<HashNode> table;

int CalcHash(std::string s)
{
    int sum = 0;
    for (auto c : s)
    {
        sum += c;
    }
    return sum;
}

HashTable::HashTable()
{
    table.resize(size);
    for (int i = 0; i < size; i++) {
        table[i].label = "";
        table[i].value = 0;
    }
}

HashTable::~HashTable()
{
}

int HashToKey(int hash, std::vector<HashNode>& t, std::string name)
{
    int key = hash % size;
    while (t[key].label != "" && t[key].label != name) {
        key = (key + 1) % size;
    }
    return key;
}

void HashTable::Set(std::string name, int value)
{
    int hash = CalcHash(name);
    int key = HashToKey(hash, table, name);
    table[key].value = value;
    if (table[key].label == "") {
        table[key].label = name;
        used++;
        if (used > capacity) {
            int t = capacity;
            capacity = size;
            size = t+size; // フィボナッチ数列で進める
            std::vector<HashNode> tb2; // 新しく領域を用意
            tb2.resize(size);
            for (auto d : table) { // Hashテーブル組みなおし
                if (d.label != "") {
                    //tb2に移動
                    int hash = CalcHash(d.label);
                    int key = HashToKey(hash, tb2, d.label);
                    tb2[key] = d;
                }
            }
            table.resize(size);
            for (int i = 0; i < size; i++) { // テーブルを書き戻す
                table[i] = tb2[i];
            }
            tb2.clear();
        }
    }
}

int HashTable::Get(std::string name)
{
    int hash = CalcHash(name);
    int key = hash % size;
    while (table[key].label != "" && table[key].label != name) {
        key = (key + 1) % size;
    }
    if (table[key].label == "")
        return 0;
    return table[key].value;
}
