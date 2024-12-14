#include "perceptron.hpp"
#include <numeric>  //libreria rara del inner_product
using namespace std;

Perceptron::Perceptron(int numInputs, float tasa)
    : tasa(tasa), bias(0.0f) {
    pesos.resize(numInputs, 0.0f);
}

int Perceptron::predict(const vector<float>& inputs) {
    //suma de entradas y pesos, añado sesgo (challenge 6)
    float sum=inner_product(pesos.begin(), pesos.end(), inputs.begin(), bias);

    if(sum >= 0.0f) {
        return 1;//si la prediccion es positiva
    } else{
        return 0;
    }
}


void Perceptron::train(const std::vector<float>& inputs, int objetivo) {
    int prediccion=predict(inputs);
    int error=objetivo-prediccion;

    for(size_t i=0;i<pesos.size();++i) {
        pesos[i]+=tasa * error * inputs[i];
    }
    bias+=tasa * error;
}
