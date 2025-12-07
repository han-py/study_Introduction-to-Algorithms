#include <iostream>
#include <stdexcept>

template<typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t size;

public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~CircularLinkedList() {
        clear();
    }
    
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        
        if (empty()) {
            head = tail = newNode;
            tail->next = head;
        } else {
            newNode->next = head;
            head = newNode;
            tail->next = head;
        }
        size++;
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        
        if (empty()) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
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
            tail->next = head;
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
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
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
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        
        if (nodeToDelete == tail) {
            tail = current;
        }
        
        delete nodeToDelete;
        
        if (head) {
            tail->next = head;
        }
        
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
        if (empty()) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        Node* current = head;
        std::cout << "Circular List: " << current->data << " -> ";
        current = current->next;
        
        while (current != head) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "(back to head)" << std::endl;
    }
};