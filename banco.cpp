#include <iostream>
#include <string>
#include <cstdlib> // Para rand() y srand()
#include <cctype>  // Use std::isdigit
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>    //Para capturar el tiempo
#include <ctime>     // Para capturlar el tiempo
#include <numeric>   // Para iota
#include <random>    // Para random_device
#include <algorithm> // Para shuffle
#include <thread>
using namespace std;

// Include class
#include "Cliente.cpp"
#include "Nodo.cpp"
#include "List.cpp"

// Metodo para obtener el tiempo
string getTime()
{
    this_thread::sleep_for(chrono::milliseconds(1000)); // Espera que el hilo finalice para "dormir" por 200 milisegundo.
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::string timeString = std::ctime(&currentTime);
    string subString = timeString.substr(11, 8); // Separa solo la hora del tiempo total tomando.
    return subString;
};

// Método para obtener el número random
int chooseList(const string &userActive)
{
    random_device dev;  // crea un objeto random_device para formar una semilla aleatoria
    mt19937 rng(dev()); // Inicializa el generador de números aleatorios Mersenne Twister

    // Vector que contiene los nuermos 1-4
    vector<int> selectedNumbers;

    // Asignar numeros dependiendo si es cliente activo o no
    if (userActive == "Si")
    {
        selectedNumbers = {1, 2, 3}; // Options for active
    }
    else
    {
        selectedNumbers = {3, 4}; // Opciones for no active
    }

    // Define las distribuciones para los numeros random    Define distributions for random numbers
    uniform_int_distribution<std::mt19937::result_type> distSi(1, 3); // Distribucion uniforme entre   1 y 3 para “si”
    uniform_int_distribution<std::mt19937::result_type> distNo(3, 4); // Distribucion uniforme  entre 3 y 4 para “no”

    // Añadir números aleatorios hasta completar un intervalo de 5
    while (selectedNumbers.size() < 5)
    {
        int randomNum = (userActive == "Si") ? distSi(rng) : distNo(rng); // Elegir un numero random segun el estado del liente
        selectedNumbers.push_back(randomNum);                             // Añadir el número aleatorio al vector
    }

    // mezcla los números seleccionados
    shuffle(selectedNumbers.begin(), selectedNumbers.end(), rng);

    // Elegir el primer número de la lista mezclada
    int randomNumber = selectedNumbers.front();

    return randomNumber;
}

// Método para agregar a lista correspondiente según número random
List addList(List list, Cliente client, string letter)
{
    string turn = letter + "-" + to_string(list.getTurn()); // Une el turno de la lista con la letra que la representa para lograr el código alfanumerico de la transacción
    client.setTurn(turn);                                   // Le asigna el turno al cliente cambiando el valor del atributo
    client.setTimeStart(getTime());                         // Llama el metodo getTime, en este caso de entrada y lo asigna en cliente cambiando el valor del atributo
    list.encolar(client);                                   // Agrega a la lista el cliente en forma de cola
    cout << "Cliente en lista de espera..." << endl;
    return list;
}

// Método para realizar acción de transacción
List transactionCompleted(List list, List listOut)
{
    if (list.getSize() != 0) // Verifica que la lista no este vacia
    {
        Nodo *temp = list.getFirst();
        temp->cliente.setTimeEnd(getTime()); // Accede a través de temp a cliente para cambiarle el valor del atributo de tiempo finalizado que obtiene tras llamar la función getTime
        listOut.pilar(temp->cliente);        // Agrega a la lista de salida el cliente que finalizo la transacción en forma de pila
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Atendiendo cliente..." << endl;
    }
    else
    {
        cout << "No hay clientes para transaccionar." << endl;
    }
    return listOut;
};

Cliente getRandomClient(Cliente matrix[25][10])
{
    vector<int> uniqueNumbers(250);                      // Crear un vector con números únicos del 0 al 249
    iota(uniqueNumbers.begin(), uniqueNumbers.end(), 0); //    LLenar el vector con numeros sequenciales usando iota

    random_device rd; // Inicia el dispositivo random para generar nuevos valores

    mt19937 g(rd()); // Iniciar  the Mersenne Twister generator

    shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), g); // Revuelve los números en el vector para desordenarlos

    int randomIndex = uniqueNumbers[0]; // Toma el primer índice random después de mezclar
    int row = randomIndex / 10;         // ubica la fila dividiendo por 10
    int column = randomIndex % 10;      // Ubica la columna tomando el residuo al dividir  por 10

    Cliente selectedClient = matrix[row][column]; // Selecciona el cliente de la matriz en esa fila y columna

    return selectedClient; // Devuelve el cliente seleccionado
}

int main()
{
    // Definición de variables
    srand(static_cast<unsigned int>(time(0)));
    const int totalClients = 250;
    Cliente matrix[25][10]{};
    List listA;
    List listB;
    List listC;
    List listD;
    List listOut;

    // Lee el archivo clientes.txt, separa por lineas, comas y ordena los datos en el inventario
    std::ifstream file("./txtFiles/clientes.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    else
    {
        string line, arrayTokens[4]{}, token;
        int row = 0, column = 0, index = 0;
        while (getline(file, line) && row < 50)
        {
            stringstream ss(line);
            string token;

            while (getline(ss, token, ',') && index < 4)
            {
                arrayTokens[index] = token;
                index++;
            }

            // Tras obtener los valores de cada atributo los cambia
            matrix[row][column].setName(arrayTokens[0]);
            matrix[row][column].setLastName(arrayTokens[1]);
            matrix[row][column].setId(arrayTokens[2]);
            matrix[row][column].setActive(arrayTokens[3]);

            column++;
            index = 0;

            if (column >= 10)
            {
                row++;
                column = 0;
            }
        }
    }

    file.close();

    int i = 0, j = 0;
    while (j < 250)
    {
        while (i < 5)
        {
            Cliente selectedClient = getRandomClient(matrix);        // Selecciona un cliente random
            int randomList = chooseList(selectedClient.getActive()); // Decide que transacción realizará el cliente tras llamar la funcion chooseList
            // Agregara a la lista correspondiente al valor del número random el cliente seleccionado
            if (randomList == 1)
            {
                listD = addList(listD, selectedClient, "D");
            }
            else if (randomList == 2)
            {
                listB = addList(listB, selectedClient, "B");
            }
            else if (randomList == 3)
            {
                listA = addList(listA, selectedClient, "A");
            }
            else if (randomList == 4)
            {
                listC = addList(listC, selectedClient, "C");
            }
            i++;
        }

        // Tras ingresar 5 clientes completa una transacción para cada lista
        listOut = transactionCompleted(listA, listOut);
        listA.desencolar();
        listOut = transactionCompleted(listB, listOut);
        listB.desencolar();
        listOut = transactionCompleted(listC, listOut);
        listC.desencolar();
        listOut = transactionCompleted(listD, listOut);
        listD.desencolar();
        // Modifica contadores
        j = j + 5;
        i = 0;
    };

    // Escribe los clientes que se encuentran en la lista de salidada en el archivo outClientes.txt con sus datos actualizados y tiempo finalizado
    std::ofstream outFile("./txtFiles/outClientes.txt");
    if (outFile.is_open())
    {
        Nodo *actual = listOut.getFirst();
        while (actual != nullptr)
        {
            outFile << actual->cliente.printInformation() << endl;
            actual = actual->next;
        }
        delete actual;
    }
    else
    {
        cout << "No se puede abrir el archivo" << endl;
    };

    return 0;
}