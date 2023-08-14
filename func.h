#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "neuron.h"


void make_null_wagi(string s);
void show_array(char **&a);
void make_null_array(char **&a,int n);
void make_dataset(char **a,int &f1,int n);
void array_delete(char **&a,int n);
void learn_NN(NeuroNet *NN0,NeuroNet *NN1,int long_dataset,int n);
void swop(char**&a,char**&b,int n);
void equal(char**&a,char**&b,int n);
void learn_DNN(NeuroNet *NN0,NeuroNet *NN1,int long_dataset,int n);
char win(char **&a,int n);
#endif // FUNC_H
