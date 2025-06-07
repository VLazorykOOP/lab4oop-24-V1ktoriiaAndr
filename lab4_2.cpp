#include <iostream>
#include <string>
#include <vector>
using namespace std;

int CodeError = 0;

class Domen_name {
public:
    string name;
    Domen_name(const string& n = "") : name(n) {}
};

class Ip_adress {
public:
    string address;
    Ip_adress(const string& a = "") : address(a) {}
};

class AssocArray {
public:
    class Pair {
    public:
        Domen_name domain;
        Ip_adress ip;

        Pair(const string& d = "", const string& i = "") : domain(d), ip(i) {}

        friend ostream& operator<<(ostream& out, const Pair& entry);
        friend istream& operator>>(istream& in, Pair& entry);
    };

    vector<Pair> entries;

    void add(const string& domain, const string& ip) {
        entries.emplace_back(domain, ip);
    }

    void createSet(int n) {
        for (int i = 0; i < n; ++i) {
            Pair p;
            cout << "Insert domain and IP [" << i + 1 << "]: ";
            cin >> p;
            entries.push_back(p);
        }
    }

    Pair operator[](const string& domain) {
        for (auto& entry : entries) {
            if (entry.domain.name == domain) {
                CodeError = 0;
                return entry;
            }
        }
        CodeError = 1;
        return Pair();
    }

    Pair operator()(const string& domain) {
        return (*this)[domain];
    }

    void printAll() {
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
    }
};

ostream& operator<<(ostream& out, const AssocArray::Pair& entry) {
    out << entry.domain.name << " -> " << entry.ip.address;
    return out;
} 

istream& operator>>(istream& in, AssocArray::Pair& entry) {
    in >> entry.domain.name >> entry.ip.address;
    return in;
}

int main() {
    AssocArray dns;

    dns.createSet(3);

    cout << "\nAll data:\n";
    dns.printAll();

    string query;
    cout << "\nInsert domain for search: ";
    cin >> query;

    auto found = dns[query];

    if (CodeError == 0)
        cout << "Found: " << found << endl;
    else
        cout << "Domain not found!" << endl;

    return 0;
}
