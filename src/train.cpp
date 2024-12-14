#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "perceptron.hpp"
using namespace std;

int main() {
    ifstream dataFile("data/game_data.csv");
    if (!dataFile.is_open()) {
        cerr << "Error al abrir el archivo de datos." << endl;
        return 1;
    }

    string line;
    getline(dataFile, line);// es para pasar d la cabecera

    vector<vector<float>> inputs;
    vector<int> targets;

    while (getline(dataFile, line)) {
        stringstream ss(line);
        vector<float> input(3);  // pos jugador, enemigo eje x y ememigo eje y
        int action;

        ss >> input[0];
        ss.ignore(1);
        ss >> input[0];//pos jugador
        ss.ignore(1);
        ss >> input[1];//eje x enemigo
        ss.ignore(1);
        ss >> input[2];//eje y enemigo
        ss.ignore(1);
        ss >> action;

        inputs.push_back(input);
        targets.push_back(action);
    }

    dataFile.close();

    Perceptron perceptron(3);
    for (size_t momento=0;momento<100;++momento){
        for(size_t i=0;i<inputs.size();++i) {
            perceptron.train(inputs[i],targets[i]);
        }
    }

    cout<<"Entrenamiento completado."<<endl;
    return 0;
}
