#include <iostream>
#include <memory>

// Definición de la estructura del nodo
struct Node {
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

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

// Clase para la lista doblemente ligada
class DoublyLinkedList {
private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

public:
    // Constructor por defecto
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Función para añadir un nodo al inicio de la lista
    void push_front(int value) {
        auto new_node = std::make_shared<Node>(value);
        if (!head) {
            head = new_node;
            tail = new_node;
        }
        else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    // Función para imprimir la lista en sentido directo
    void print_forward() const {
        if (!head) {
            std::cout << "La lista está vacía." << std::endl;
            return;
        }
        std::shared_ptr<Node> current = head;
        std::cout << "Lista (adelante): ";
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

};

void mainDll(void) {
    DoublyLinkedList my_list;

    // Agregar nodos a la lista
    my_list.push_front(5);
    my_list.push_front(1);

    // Imprimir la lista
    //my_list.print_forward();
}