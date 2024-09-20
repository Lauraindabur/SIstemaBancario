#include <iostream>
#include <string>
using namespace std;

#include "Nodo.cpp"
#include "Cliente.cpp"

class List
{
private:
    Nodo *first;
    Nodo *last;
    int size;
    int turn;

public:
    List() : first(nullptr), last(nullptr), size(0), turn(0) {}

    void encolar(Cliente cliente)
    {
        this->turn++;
        Nodo *newNodo = new Nodo(cliente);
        if (last == nullptr)
        {
            first = newNodo;
            last = newNodo;
        }
        else
        {
            last->next = newNodo;
            last = newNodo;
        }
        this->size++;
    }

    void desencolar()
    {
        if (first != nullptr)
        {
            Nodo *tempNodo = first;
            first = first->next;
            delete tempNodo;

            if (first == nullptr)
            {
                last = nullptr;
            }
            this->size--;
        }
    }

    void pilar(Cliente cliente)
    {
        Nodo *newNodo = new Nodo(cliente);
        if (first == nullptr)
        {
            first = newNodo;
            last = newNodo;
        }
        else
        {
            newNodo->next = first;
            first = newNodo;
        }
        this->size++;
    }

    void desenpilar()
    {
        if (last != nullptr)
        {
            Nodo *tempNodo = last;
            last = last->next;
            delete tempNodo;
        }
    }

    int getSize() const { return size; }
    int getTurn() const { return turn; }
    Nodo *getFirst() { return first; }
};