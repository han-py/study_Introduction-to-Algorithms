#include <iostream>
#include <stdexcept>

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    size_t size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}
    
    ~SinglyLinkedList() {
        clear();
    }
    
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    void pop_front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
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
    
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            push_front(value);
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
        delete nodeToDelete;
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
        std::cout << "List: ";
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};