#include <iostream>
#include <stdexcept>

class smart_array {
private:
    int* data;
    size_t size;
    size_t capacity;

public:
    smart_array(size_t capacity) : size(0), capacity(capacity) {
        data = new int[capacity];
    }

    ~smart_array() {
        delete[] data;
    }

    smart_array(const smart_array& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    smart_array& operator=(const smart_array& other) {
        if (this != &other) {
            delete[] data;

            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void add_element(int element) {
        if (size >= capacity) {
            capacity *= 2;
            int* new_data = new int[capacity];
            for (size_t i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[size] = element;
        size++;
    }

    int get_element(size_t index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Неверный индекс");
        }
        return data[index];
    }
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << arr.get_element(0) << std::endl;
        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
