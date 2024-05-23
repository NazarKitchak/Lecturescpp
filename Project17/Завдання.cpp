#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional> 

using namespace std;

class HashTable {
public:
    HashTable(size_t size) : table(size) {}

    void insert(const string& key, const string& value) {
        size_t hashValue = hashFunction(key);
        table[hashValue].push_back({ key, value });
    }

    bool search(const string& key, string& value) const {
        size_t hashValue = hashFunction(key);
        for (const auto& kvp : table[hashValue]) {
            if (kvp.first == key) {
                value = kvp.second;
                return true;
            }
        }
        return false;
    }

    bool remove(const string& key) {
        size_t hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        for (auto i = cell.begin(); i != cell.end(); i++) {
            if (i->first == key) {
                cell.erase(i);
                return true;
            }
        }
        return false;
    }

private:
    size_t hashFunction(const string& key) const {
        return std::hash<string>{}(key) % table.size();
    }

    vector<list<pair<string, string>>> table;
};

int main() {
    HashTable ht(10);

    ht.insert("name", "Alice");
    ht.insert("age", "30");
    ht.insert("city", "Wonderland");

    string value;
    if (ht.search("name", value)) {
        cout << "Знайдено: " << value << endl;
    }
    else {
        cout << "Не знайдено" << endl;
    }

    if (ht.remove("age")) {
        cout << "Видалено успішно" << endl;
    }
    else {
        cout << "Видалення не вдалося" << endl;
    }

    if (ht.search("age", value)) {
        cout << "Знайдено: " << value << endl;
    }
    else {
        cout << "Не знайдено" << endl;
    }

    return 0;
}
