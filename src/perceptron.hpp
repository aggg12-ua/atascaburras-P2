#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP
#include <vector>
using namespace std;


class Perceptron {
private:
    vector<float> pesos;
    float bias;
    float tasa;

public:
    Perceptron(int numInputs, float tasa = 0.01);
    int predict(const vector<float>& inputs);
    void train(const vector<float>& inputs, int objetivo);
};

#endif
