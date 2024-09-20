#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string converString(string timeString)
{
    string subString = timeString.substr(11, 8);
    return subString;
}

int main()
{
    // Obtener la hora actual
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convertir a un formato legible
    std::string timeString = std::ctime(&currentTime);

    // Guardar la hora en un archivo
    std::ofstream outFile("current_time.txt");
    if (outFile.is_open())
    {
        outFile << "Hora actual: " << timeString;
        outFile.close();
        std::cout << "Hora guardada en current_time.txt" << std::endl;
        std::cout << timeString << std::endl;
        string result = converString(timeString);
        std::cout << result << std::endl;
    }
    else
    {
        std::cerr << "No se puede abrir el archivo" << std::endl;
    }

    return 0;
}