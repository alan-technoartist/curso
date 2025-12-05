#include <iostream>
#include <memory>

// Estructura del nodo de la lista
struct Node {
    int data;
    std::unique_ptr<Node> next;

    // Constructor para inicializar el nodo
    Node(int value) {
        data = value;
        next = nullptr;
        std::cout << "Nodo con valor " << data << " creado." << std::endl;

    }
    ~Node() {
        std::cout << "Nodo con valor " << data << " destruido." << std::endl;
    }
};

// Clase para la lista ligada
class LinkedList {
private:
    std::unique_ptr<Node> head;

public:
    // Constructor por defecto
    LinkedList() {
        head = nullptr;
    }

    // Función para añadir un nuevo nodo al inicio
    void add_front(int value) {
        auto new_node = std::make_unique<Node>(value);
        if (head) {
            new_node->next = std::move(head);
        }
        head = std::move(new_node);
    }

    // Función para imprimir los elementos de la lista
    void print_list() const {
        Node* current = head.get();
        std::cout << "Lista: ";
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next.get();
        }
        std::cout << "nullptr" << std::endl;
    }
};

void mainSll(void) {
 

}