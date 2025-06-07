#include <iostream>
using namespace std;

enum status {codeError, ok};

class VectorShort {
    short *V;
    int size;
    static int count;
    status state;
    public:
    VectorShort() : V(new short[1]{0}), size(1), state(ok) {};
    VectorShort(int c) {
        if (c <= 0) {
            V = nullptr;
            size = 0;
            state = codeError;
        }
        else {
            V = new short[c]; state = ok;
        }
        count ++;
    }
    VectorShort(int c, const short *v) {
        if (c <= 0) {
            V = nullptr;
            size = 0;
            state = codeError;
        }
        else {
            size = c;
            V = new short[size];
            for (int i = 0; i < size; i++) {
                V[i] = v[i];
            }
            state = ok;
        }
        count++;
    }
    VectorShort(const VectorShort& v) {
        size = v.size;
        state = v.state;
        V = new short[size];
        for (int i = 0; i < size; i++) {
            V[i] = v.V[i];
        }
        count ++;
    }
    ~VectorShort() {
        if (V != nullptr) {
            delete[] V;
        }
        count --;
    }
    VectorShort& operator=(const VectorShort& v) {
        if (this != &v) {
            delete[] V;
            size = v.size;
            state = v.state;
            V = new short[size];
            for (int i = 0; i < size; i++) {
                V[i] = v.V[i];
            }
        }
        count ++;
        return *this;
    }

    VectorShort& operator++() {
        if (state == ok) {
            for (int i = 0; i < size; i++) {
                V[i]++;
            }
        } else {
            cerr << "Error in vector operation" << endl; exit(1);
        }
        return *this;
    }
    VectorShort operator++(int) {
        VectorShort temp(*this);
        ++(*this);
        return temp;
    }
    VectorShort& operator--() {
        if (state == ok) {
            for (int i = 0; i < size; i++) {
                V[i]--;
            }
        } else {
            cerr << "Error in vector operation" << endl; exit(1);
        }
        return *this;
    }
    VectorShort operator--(int) {
        VectorShort temp(*this);
        --(*this);
        return temp;
    }
    bool operator!() {
        if (state == ok) {
            return size == 0;
        } else {
            cerr << "Error in vector operation" << endl; exit(1);
        }
    }
    VectorShort operator~() {
        VectorShort result(*this);
        for (int i = 0; i < size; i++) {
            result.V[i] = ~V[i];
        }
        return result;
    }
    VectorShort operator-() {
        if (state != ok) {
            cerr << "Error in vector operation" << endl;
            exit(1);
        }
        VectorShort result(*this); // копіюємо
        for (int i = 0; i < size; i++) {
            result.V[i] = -V[i];   // змінюємо знак
        }
        return result;
    }
    VectorShort& operator+=(const VectorShort& s) {
        if (this != &s) {
            size = size + s.size;
            short* newV = new short[size];

            for (int i = 0; i < size - s.size; i++) {
                newV[i] = V[i];
            }

            for (int i = 0; i < s.size; i++) {
                newV[i + size - s.size] = V[i + size - s.size] + s.V[i];
            }

            delete[] V;
            V = newV;
        }
        return *this;
    }
    VectorShort& operator-=(const VectorShort& s) {
        if (this != &s) {
            int minSize = min(size, s.size);

            short* newV = new short[minSize];

            for (int i = 0; i < minSize; i++) {
                newV[i] = V[i] - s.V[i];
            }

            size = minSize;

            delete[] V;
            V = newV;
        }
        return *this;
    }
    VectorShort& operator*=(double num) {
        if (state == ok) {
            for (int i = 0; i < size; i++) {
                V[i] = V[i] * num;
            }
            return *this;
        }
    }
    VectorShort& operator/=(short num) {
        if (state == ok) {
            for (int i = 0; i < size; i++) {
                V[i] = V[i] / num;
            }
            return *this;
        }
    }
    VectorShort& operator%=(short num) {
        if (state == ok) {
            for (int i = 0; i < size; i++) {
                V[i] = V[i] % num;
            }
            return *this;
        }
    }
    VectorShort& operator|=(const VectorShort& v) {
        if (state == ok) {
            int minSize = min(size, v.size);
            short* newV = new short[minSize];
            for (int i = 0; i < minSize; i++) {
                newV[i] = V[i] | v.V[i];
            }
            delete[] V;
            V = newV;
        }
        return *this;
    }
    VectorShort& operator^=(const VectorShort& v) {
        if (state == ok) {
            int minSize = min(size, v.size);
            short* newV = new short[minSize];
            for (int i = 0; i < minSize; i++) {
                newV[i] = V[i] ^ v.V[i];
            }
            delete[] V;
            V = newV;
        }
        return *this;
    }
    VectorShort& operator&=(const VectorShort& v) {
        if (state == ok) {
            int minSize = min(size, v.size);
            short* newV = new short[minSize];
            for (int i = 0; i < minSize; i++) {
                newV[i] = V[i] & v.V[i];
            }
            delete[] V;
            V = newV;
        }
        return *this;
    }
    VectorShort operator+(const VectorShort& v) const {
        int minSize = min(size, v.size);
        VectorShort result(minSize);

        for (int i = 0; i < minSize; i++) {
            result.V[i] = V[i] + v.V[i];
        }

        if (state == codeError || v.state == codeError) {
            result.state = codeError;
        } else {
            result.state = ok;
        }
        count ++;
        return result;
    }
    VectorShort operator-(const VectorShort& v) const {
        int minSize = min(size, v.size);
        VectorShort result(minSize);

        for (int i = 0; i < minSize; i++) {
            result.V[i] = V[i] - v.V[i];
        }

        if (state == codeError || v.state == codeError) {
            result.state = codeError;
        } else {
            result.state = ok;
        }
        count ++;
        return result;
    }
    VectorShort operator*(double num) const {
        if (state == ok) {
            VectorShort result(size);
            for (int i = 0; i < size; i++) {
                result.V[i] = V[i] * num;
            }
            count ++;
            return result;
        }
    }
    VectorShort operator/(double num) const {
        if (state == ok || num != 0) {
            VectorShort result(size);
            for (int i = 0; i < size; i++) {
                result.V[i] = V[i] / num;
            }
            count ++;
            return result;
        }
    }
    VectorShort operator%(short num) const {
        if (state == ok || num != 0) {
            VectorShort result(size);
            for (int i = 0; i < size; i++) {
                result.V[i] = V[i] % num;
            }
            count ++;
            return result;
        }
    }
    VectorShort operator|(const VectorShort& v) const {
        int minSize = min(size, v.size);
        VectorShort result(minSize);

        for (int i = 0; i < minSize; i++) {
            result.V[i] = V[i] | v.V[i];
        }

        if (state == codeError || v.state == codeError) {
            result.state = codeError;
        } else {
            result.state = ok;
        }
        count ++;
        return result;
    }
    VectorShort operator^(const VectorShort& v) const {
        int minSize = min(size, v.size);
        VectorShort result(minSize);

        for (int i = 0; i < minSize; i++) {
            result.V[i] = V[i] ^ v.V[i];
        }

        if (state == codeError || v.state == codeError) {
            result.state = codeError;
        } else {
            result.state = ok;
        }
        count ++;
        return result;
    }
    VectorShort operator&(const VectorShort& v) const {
        int minSize = min(size, v.size);
        VectorShort result(minSize);

        for (int i = 0; i < minSize; i++) {
            result.V[i] = V[i] & v.V[i];
        }

        if (state == codeError || v.state == codeError) {
            result.state = codeError;
        } else {
            result.state = ok;
        }
        count ++;
        return result;
    }
    friend istream& operator>>(istream& is, VectorShort& v){
        int newSize;
    is >> newSize;
    cout << "Read size: " << newSize << endl;

    delete[] v.V;
    v.size = newSize;
    v.V = new short[newSize];

    for (int i = 0; i < newSize; i++) {
        is >> v.V[i];
        cout << "Read element " << i << ": " << v.V[i] << endl;
    }

    v.state = ok;
    return is;
}
friend ostream& operator<<(ostream& os, const VectorShort& v) {
        os << v.size << "\n";
        for (int i = 0; i < v.size; i++) {
            os << v.V[i] << " ";
        }
        return os;
    }
    bool operator==(const VectorShort& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (V[i] != other.V[i]) return false;
        }
        return true;
    }

    bool operator!=(const VectorShort& other) const {
        return !(*this == other);
    }
    short& operator[](int index) {
        if (index >= 0 && index < size) {
            return V[index];
        } else {
            state = codeError;
            return V[size - 1]; // останній елемент
        }
    }
    void operator()(const VectorShort& other) {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) {
            V[i] += other.V[i]; // або будь-яка інша дія
        }
    }
    bool operator>(const VectorShort& other) const {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) {
            if (V[i] <= other.V[i]) return false;
        }
        return true;
    }

    bool operator>=(const VectorShort& other) const {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) {
            if (V[i] < other.V[i]) return false;
        }
        return true;
    }

    bool operator<(const VectorShort& other) const {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) {
            if (V[i] >= other.V[i]) return false;
        }
        return true;
    }

    bool operator<=(const VectorShort& other) const {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) {
            if (V[i] > other.V[i]) return false;
        }
        return true;
    }
    };
void* operator new(size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) {
    free(ptr);
}




int VectorShort::count = 0;

int main(){
    // Створення вектора на 5 елементів
    short arr[] = {1, 2, 3, 4, 5};
    VectorShort v1(5, arr);

    // Вивід вектора
    cout << "v1: " << v1 << endl;

    // Префіксний інкремент
    ++v1;
    cout << "v1 after ++: " << v1 << endl;

    // Унарний мінус
    VectorShort neg = -v1;
    cout << "unar -v1: " << neg << endl;

    // Побітове НЕ
    VectorShort bitNot = ~v1;
    cout << "bite ~v1: " << bitNot << endl;

    // Копіювання
    VectorShort v2 = v1;
    cout << "v2 (copy of v1): " << v2 << endl;

    v2 += v1;
    cout << "v2 after v2 += v1: " << v2 << endl;

    cout << "v2[2] = " << v2[2] << endl;

    v2(7);
    cout << "v2 after changing size to 7: " << v2 << endl;

    VectorShort v3;
    cout << "Enter size for v3: ";
    cin >> v3;
    cout << "v3: " << v3 << endl;
    return 0;
}
