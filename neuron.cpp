#include "neuron.h"
#include "list.h"
#include <iostream>
using namespace std;

Neuron::Neuron(string nam,int longW){
    name=nam;
    W=new listW();
    W->filling(W,longW,name);
}
double Neuron::sumN(listNIn *inp,int longNN){
    v=0;
    W->goFront(W);
    inp->goFront(inp);
    for(int i=0;i<longNN;i++){
        v+=W->returnw()*inp->returnN();
        if(W->next!=NULL)
        W=W->next;
        if(inp->next!=NULL)
        inp=inp->next;
    }
    return v;
}
void Neuron::Delete(Neuron *n){
    n->W->Delete(n->W);
    delete n;
}
int NeuronIn::returnin(){
    return in;
}
NeuronIn::NeuronIn(){
    in=0;
}
void NeuronIn::dataIn(int a){
    //cout<<"it work"<<endl;
    in=a;
}
/** @brief Create new neural-net
 *  \param lay Name of neural-net(only number)
 *  \param scale Size of neural-net
**/
NeuroNet::NeuroNet(int scale,int lay){
    //cout<<"it work";
    longNN=scale;
    layer=lay;
    inN=new listNIn();
    N=new listN();
    string s="";
    s+=(char)(layer+'0');
    inN->create(longNN*longNN,inN);
    N->create(N,longNN*longNN,s);
}
/** @brief Give a step of neural-net
 *  \param b Double dimention array with "screen" of table
**/
int NeuroNet::work(char **b){
    //cout<<"it work";
    inN->goFront(inN);
    inN->filling(inN,longNN,b);
    N->goFront(N);
    inN->goFront(inN);
    int output=N->OutData(N,longNN*longNN,inN);
    return output;
}
/** @brief Put "screen" of table (for learning)
 *  \param b Double dimention array with "screen" of table
**/
void NeuroNet::data_in(char **b){
    inN->goFront(inN);
    inN->filling(inN,longNN,b);
}
/** @brief Learning of neural-net
 *  \param need Step that neural-net must make
 *  \param long_of_dataset Number of step's in dataset
**/
void NeuroNet::Learning(int need,int long_of_dataset){
    double *deltawagi=new double[longNN*longNN];
    for(int i=0;i<longNN*longNN;i++)deltawagi[i]=0;
    int needI=0,in;
    double out=0;
    string s="",ss="";
    s+=(char)(layer+'0');
    N->goFront(N);
    for(int i=0;i<longNN*longNN;i++){
        inN->goFront(inN);
        if(need==i)needI=1;
        else needI=0;
        double suma=-N->return_sum(longNN*longNN,inN);
        out=1/(1+exp(suma));
        inN->goFront(inN);
        for(int j=0;j<longNN*longNN;j++){
        in=inN->returnN();
        deltawagi[j]=out*(1-out)*(out-needI)*in/long_of_dataset;
        if(inN->next!=NULL)
            inN=inN->next;
        }
        int l=i;
        ss="";
        if(l==0)ss="0";
        while(l!=0){
            ss+=char(l%10+'0');
            l/=10;
        }
        N->change_wagi(deltawagi,s+ss,longNN*longNN);
        if(N->next!=NULL)
        N=N->next;
    }
}
/** @brief Learning of neural-net
 *  \param step Step that neural-net musn't make
**/
void NeuroNet::nonLearning(int step){
    inN->goFront(inN);
    N->goFront(N);
    string s="";
    int a=longNN*longNN;
    s+=(char)(layer+'0');
    double *deltawagi=new double[a];
    for(int i=0;i<step;i++){
        N=N->next;
    }
    double suma=-N->return_sum(longNN*longNN,inN);
    double out=1/(1+exp(suma));
    inN->goFront(inN);
    for(int j=0;j<longNN*longNN;j++){
        deltawagi[j]=0;
        deltawagi[j]=out*(1-out)*out*inN->returnN()/100;
        if(inN->next!=NULL)
        inN=inN->next;
    }
    string ss="";
    if(step==0)ss="0";
    while(step!=0){
        ss+=char(step%10+'0');
        step/=10;
    }
    N->change_wagi(deltawagi,s+ss,longNN*longNN);
}
void Neuron::unfill(double *&deltawagi,string name,int longNN){
    W->unfill(deltawagi,name,W,longNN);
    W->Refill(W,longNN,name);
}
NeuroNet::~NeuroNet(){
    inN->Delete(inN);
    N->Delete(N);
}
