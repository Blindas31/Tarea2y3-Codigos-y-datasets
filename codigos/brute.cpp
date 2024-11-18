#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <chrono>
using namespace std;

// Tablas globales de costos
vector<int> costInsert(26); // Costos de inserción
vector<int> costDelete(26); // Costos de eliminación
vector<vector<int>> costReplace(26, vector<int>(26)); // Costos de sustitución entre letras
vector<vector<int>> costTranspose(26, vector<int>(26)); // Costos de transposición entre letras

// Función para cargar una tabla de costos unidimensional

void loadCostTable(const string& filename, vector<int>& table) {
    ifstream file(filename);
    for (int i = 0; i < 26; i++) {
        file >> table[i];
    }
    file.close();
}

// Función para cargar una tabla de costos bidimensional
void loadCostTable2D(const string& filename, vector<vector<int>>& table) {
    ifstream file(filename);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            file >> table[i][j];
        }
    }
    file.close();
}

// Funciones para obtener los costos específicos de cada operación
int getInsertCost(char c) {
    return costInsert[c - 'a'];
}

int getDeleteCost(char c) {
    return costDelete[c - 'a'];
}

int getReplaceCost(char a, char b) {
    return costReplace[a - 'a'][b - 'a'];
}

int getTransposeCost(char a, char b) {
    return costTranspose[a - 'a'][b - 'a'];
}

// Enfoque de fuerza bruta para calcular la distancia de Damerau-Levenshtein
int bruteForceDamerauLevenshtein(const string& str1, const string& str2, int i, int j) {
    // Caso base: si una de las cadenas está vacía
    if(i==0 && j==0) return 0;
    if (i == 0) return getInsertCost(str2[j - 1]) + bruteForceDamerauLevenshtein(str1,str2,i,j-1); // Solo inserciones
    if (j == 0) return getDeleteCost(str1[i - 1])+bruteForceDamerauLevenshtein(str1,str2,i-1,j); // Solo eliminaciones

    // Si los caracteres son iguales, pasamos al siguiente par de caracteres

    // Calculamos los costos de cada operación y seleccionamos el mínimo

    // Inserción
    int insertCost = getInsertCost(str2[j - 1]) + bruteForceDamerauLevenshtein(str1, str2, i, j - 1);

    // Eliminación
    int deleteCost = getDeleteCost(str1[i - 1]) + bruteForceDamerauLevenshtein(str1, str2, i - 1, j);

    // Sustitución
    int replaceCost = getReplaceCost(str1[i - 1], str2[j - 1]) + bruteForceDamerauLevenshtein(str1, str2, i - 1, j - 1);

    // Transposición (si los caracteres son adyacentes y en orden invertido)
    int transposeCost = INT_MAX;
    if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1]) {
        transposeCost = getTransposeCost(str1[i - 1], str1[i - 2]) + bruteForceDamerauLevenshtein(str1, str2, i - 2, j - 2);
    }
    // Si los caracteres son iguales, pasamos al siguiente par de caracteres
    if (str1[i - 1] == str2[j - 1]) {
        return bruteForceDamerauLevenshtein(str1, str2, i - 1, j - 1);
    }
    // Retornar el mínimo costo entre todas las operaciones
    return min({insertCost, deleteCost, replaceCost, transposeCost});
}

int main() {
    // Cargar las tablas de costos desde archivos
    loadCostTable("cost_insert.txt", costInsert);
    loadCostTable("cost_delete.txt", costDelete);
    loadCostTable2D("cost_replace.txt", costReplace);
    loadCostTable2D("cost_transpose.txt", costTranspose);

    // Prueba del algoritmo con las cadenas "acb" y "abc"
    string str1;
    string str2;
    std::ifstream inputFile("palabrassimilares3.txt");
    if (inputFile.is_open()) {
        // Leer la primera línea
        std::getline(inputFile, str1);
        std::getline(inputFile, str2);
        inputFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }
    //std::cout << "str1: " << str1 << std::endl;
    //std::cout << "str2: " << str2 << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    int distance = bruteForceDamerauLevenshtein(str1, str2, str1.length(), str2.length());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "La función tomó " << duration.count() << " ms en ejecutarse.\n";
    cout << "Damerau-Levenshtein Distance (Brute Force) with Custom Costs: " << distance << endl;

    return 0;
}
