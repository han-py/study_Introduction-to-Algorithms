#include <iostream>
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    
    void pop_front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        size--;
    }
    
    void pop_back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        size--;
    }
    
    T& front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }
    
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }
    
    T& back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }
    
    const T& back() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }
    
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            push_front(value);
            return;
        }
        
        if (index == size) {
            push_back(value);
            return;
        }
        
        Node* current;
        if (index < size / 2) {
            // Traverse from head
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            // Traverse from tail
            current = tail;
            for (size_t i = size - 1; i > index; --i) {
                current = current->prev;
            }
        }
        
        Node* newNode = new Node(value);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }
    
    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            pop_front();
            return;
        }
        
        if (index == size - 1) {
            pop_back();
            return;
        }
        
        Node* current;
        if (index < size / 2) {
            // Traverse from head
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            // Traverse from tail
            current = tail;
            for (size_t i = size - 1; i > index; --i) {
                current = current->prev;
            }
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }
    
    bool empty() const {
        return head == nullptr;
    }
    
    size_t getSize() const {
        return size;
    }
    
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    
    void print() const {
        Node* current = head;
        std::cout << "List: nullptr";
        while (current != nullptr) {
            std::cout << " <-> " << current->data;
            current = current->next;
        }
        std::cout << " <-> nullptr" << std::endl;
    }
    
    void printReverse() const {
        Node* current = tail;
        std::cout << "Reverse List: nullptr";
        while (current != nullptr) {
            std::cout << " <-> " << current->data;
            current = current->prev;
        }
        std::cout << " <-> nullptr" << std::endl;
    }
};