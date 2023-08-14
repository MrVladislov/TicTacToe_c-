#ifndef LIST_H
#define LIST_H
#include <fstream>
using namespace std;
class Neuron;
class NeuronIn;
class NeuroNet;
/** @brief Bidirectional list of weights
*/
class listW
{
private:
    double w;
public:
    listW *prev;
    listW *next;
    listW();
    void unfill(double *&deltawagi,string name,listW *&nowL,int longNN);
    double returnw();
    void filling(listW *&nowL,int longW,string name);
    void goFront(listW *&nowL);
    void goBack(listW *&nowL);
    void Delete(listW *&nowL);
    void Refill(listW *&nowL,int longW,string name);
};
/** @brief Bidirectional list of input neuron
*/
class listNIn
{
private:
    NeuronIn *intN;
public:
    listNIn *prev;
    listNIn *next;
    listNIn();
    void create(int longNIn,listNIn *&nowL);
    void filling(listNIn *&nowL,int longIn,char **b);
    void Delete(listNIn *&nowL);
    void goFront(listNIn *&nowL);
    void goBack(listNIn *&nowL);
    int returnN();
};
/** @brief Bidirectional list of neuron
*/
class listN
{
private:
    Neuron *n;
public:
    listN *prev;
    listN *next;
    listN();
    void change_wagi(double *&deltawagi,string name,int longNN);
    double return_sum(int longNN,listNIn *&lin);
    void create(listN *&nowL,int longW,string layer);
    void goFront(listN *&nowL);
    void goBack(listN *&nowL);
    int OutData(listN *&nowL,int longW,listNIn *&lin);
    void Delete(listN *&nowL);
};


#endif // LIST_H
