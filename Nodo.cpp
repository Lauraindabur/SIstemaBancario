#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "Cliente.cpp"

class Nodo
{
public:
    Cliente cliente;
    Nodo *next;

    Nodo(Cliente cliente) : cliente(cliente), next(nullptr) {}
};