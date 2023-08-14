#ifndef NEURON_H
#define NEURON_H
#include <string>
#include <cmath>
using namespace std;
class listW;
class listN;
class listNIn;
/** @brief Neuron
*/
class Neuron
{
private:
    listW *W;
    string name;
    double v;
public:
    void unfill(double *&deltawagi,string name,int longNN);
    Neuron(string nam,int longW);
    double sumN(listNIn *inp,int longNN);
    void Delete(Neuron *n);
};
/** @brief Input neuron
*/
class NeuronIn
{
private:
    int in;
public:
    int returnin();
    NeuronIn();
    void dataIn(int a);
};
/** @brief Neural-net
*/
class NeuroNet
{
private:
    listNIn *inN;
    listN *N;
    int longNN;
    int layer;
    int output;
public:
    NeuroNet(int scale,int lay=1);
    int work(char **b);
    ~NeuroNet();
    void Learning(int need,int long_of_dataset);
    void nonLearning(int step);
    void data_in(char **b);
};

#endif // NEURON_H
