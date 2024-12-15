#include <iostream>
#include <initializer_list>
#include <string>

namespace containers {

    template <typename T>
    class NameClass {
    public:
        struct Node {
            T value;

        private:
            Node* next;
            Node* prev;

            Node(const T& val, Node* nxt = nullptr, Node* prv = nullptr)
                : value(val), next(nxt), prev(prv) {}

            friend class NameClass<T>;
        };

        NameClass() : head(nullptr), tail(nullptr), size(0) {}

        NameClass(std::initializer_list<T> init_list) : NameClass() {
            for (const T& elem : init_list) {
                addToEnd(elem);
            }
        }

        NameClass(const NameClass& other) : NameClass() {
            Node* current = other.head;
            while (current) {
                addToEnd(current->value);
                current = current->next;
            }
        }

        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                while (current) {
                    addToEnd(current->value);
                    current = current->next;
                }
            }
            return *this;
        }

        NameClass(NameClass&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = other.tail = nullptr;
            other.size = 0;
        }

        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                size = other.size;

                other.head = other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        T& operator[](size_t index) {
            if (index >= size) throw std::out_of_range("Index out of range");
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        void addToPosition(const T& value, size_t pos) {
            if (pos > size) throw std::out_of_range("Position out of range");
            if (pos == size) {
                addToEnd(value);
            }
            else {
                Node* current = head;
                for (size_t i = 0; i < pos; ++i) {
                    current = current->next;
                }
                Node* new_node = new Node(value, current, current->prev);
                if (current->prev) current->prev->next = new_node;
                else head = new_node;
                current->prev = new_node;
                ++size;
            }
        }

        void removeFromEnd() {
            if (tail) {
                Node* temp = tail;
                tail = tail->prev;
                if (tail) tail->next = nullptr;
                else head = nullptr;
                delete temp;
                --size;
            }
        }

        void clear() {
            while (head) {
                removeFromEnd();
            }
        }

        Node* getHead() const { return head; }

        Node* getTail() const { return tail; }

        size_t getSize() const { return size; }

        Node* getNext(Node* node) const { return node ? node->next : nullptr; }

        Node* getPrev(Node* node) const { return node ? node->prev : nullptr; }

        ~NameClass() {
            clear();
        }

    private:
        Node* head;
        Node* tail;
        size_t size;

        void addToEnd(const T& value) {
            Node* new_node = new Node(value, nullptr, tail);
            if (tail) tail->next = new_node;
            else head = new_node;
            tail = new_node;
            ++size;
        }
    };

    template <typename T>
    class Set : public NameClass<T> {
    public:
        void insert(const T& value) {
            if (!contains(value)) {
                this->addToPosition(value, findInsertionPoint(value));
            }
        }

    private:
        bool contains(const T& value) {
            typename NameClass<T>::Node* current = this->getHead();
            while (current) {
                if (current->value == value) return true;
                current = this->getNext(current);
            }
            return false;
        }

        size_t findInsertionPoint(const T& value) {
            size_t pos = 0;
            typename NameClass<T>::Node* current = this->getHead();
            while (current && current->value < value) {
                current = this->getNext(current);
            }
            return pos;
        }
    };

}



int main() {
    containers::NameClass<int> intVec({ 1, 2, 3 });
    intVec.addToPosition(4, 2);
    std::cout << intVec[2] << std::endl;

    containers::Set<double> doubleSet;
    doubleSet.insert(3.14);
    doubleSet.insert(2.71);
    doubleSet.insert(3.14);

    return 0;
}
