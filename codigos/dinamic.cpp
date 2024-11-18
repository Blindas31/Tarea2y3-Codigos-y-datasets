#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
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

// Algoritmo de Damerau-Levenshtein con costos desde tablas
int Damerau_Levenshtein_distance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> d(m + 1, vector<int>(n + 1, 0));

    // Inicialización de la primera fila y columna
    for (int i = 0; i <= m; i++) {
        d[i][0] = i * getDeleteCost(str1[i - 1]);
    }
    for (int j = 0; j <= n; j++) {
        d[0][j] = j * getInsertCost(str2[j - 1]);
    }

    // Llenado de la matriz con costos
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : getReplaceCost(str1[i - 1], str2[j - 1]);
            
            d[i][j] = min({
                d[i - 1][j] + getDeleteCost(str1[i - 1]),   // Eliminación
                d[i][j - 1] + getInsertCost(str2[j - 1]),   // Inserción
                d[i - 1][j - 1] + cost                       // Sustitución
            });

            // Verificar y aplicar transposición
            if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1]) {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + getTransposeCost(str1[i - 1], str1[i - 2]));
            }
        }
    }

    return d[m][n];
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
    std::ifstream inputFile("palabrassimilares8.txt");
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
    int distance = Damerau_Levenshtein_distance(str1, str2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "La función tomó " << duration.count() << " ms en ejecutarse.\n";
    cout << "Damerau-Levenshtein Distance with Custom Costs: " << distance << endl;

    return 0;
}
