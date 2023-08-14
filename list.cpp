#include "list.h"
#include "neuron.h"
#include <cmath>
#include <iostream>
using namespace std;
/** @brief Delete list
 *  \param listW List that delete
**/
void listW::Delete(listW *&nowL){
    nowL->goFront(nowL);
    while(nowL->next!=NULL){
        listW *temp1=nowL;
        nowL=nowL->next;
        delete temp1;
    }
    delete nowL;
}

/** @brief Delete list
 *  \param listNIn List that delete
**/
void listNIn::Delete(listNIn *&nowL){
    nowL->goFront(nowL);
    while(nowL->next!=NULL){
        listNIn *temp1=nowL;
        nowL=nowL->next;
        delete temp1;
    }
    delete nowL;
}

/** @brief Go to front of list
 *  \param listW List in which moves
**/
void listW::goFront(listW *&nowL){\
    while(nowL->prev!=NULL)
    nowL=nowL->prev;
}
/** @brief Go to back of list
 *  \param listW List in which moves
**/
void listW::goBack(listW *&nowL){
    while(nowL->next!=NULL)
    nowL=nowL->next;
}
/** @brief Go to front of list
 *  \param listN List in which moves
**/
void listN::goFront(listN *&nowL){
    while(nowL->prev!=NULL)
    nowL=nowL->prev;
}
/** @brief Go to back of list
 *  \param listN List in which moves
**/
void listN::goBack(listN *&nowL){
    while(nowL->next!=NULL)
    nowL=nowL->next;
}
/** @brief Go to front of list
 *  \param listNIn List in which moves
**/
void listNIn::goFront(listNIn *&nowL){
    while(nowL->prev!=NULL)
    nowL=nowL->prev;
}
/** @brief Go to back of list
 *  \param listNIn List in which moves
**/
void listNIn::goBack(listNIn *&nowL){
    while(nowL->next!=NULL)
    nowL=nowL->next;
}
/** @brief Give data stored in list
**/
double listW::returnw(){
    return w;
}
listW::listW(){
}
/** @brief Fill list
 *  \param listW List which  filling
 *  \param longW Lenght of list
 *  \param name Name of file from which fill
**/
void listW::filling(listW *&nowL,int longW,string name){
    //cout<<name<<endl;
    ifstream fin("D:/wagi/wagi_"+name);
    double w_temp;
    nowL->prev=NULL;
    for(int i=1;i<longW;i++)
    {
        fin>>w_temp;
        nowL->w=w_temp;
        listW *temp=new listW();
        nowL->next=temp;
        temp->prev=nowL;
        temp->next=NULL;
        nowL=temp;
    }
    fin>>w_temp;
    nowL->w=w_temp;
    nowL->next=NULL;
    fin.close();
}
/** @brief Create list and fill her
 *  \param listN First list
 *  \param longW Lenght of list
 *  \param lay Name of file from which fill
**/
void listN::create(listN *&nowL,int longW,string lay){
    nowL->prev=NULL;
    string s=lay;
    nowL->n=new Neuron(s+'0',longW);
    for(int i=1;i<longW;i++){
        int j=i;string ss="";
        while(j!=0){
            ss+=char(j%10+'0');
            j/=10;
        }
        listN *temp=new listN();
        nowL->next=temp;
        temp->prev=nowL;
        nowL=temp;
        nowL->n=new Neuron(s+ss,longW);
    }
    nowL->next=NULL;
}
listN::listN(){
}
/** @brief Give back maximum activated sum
 *  \param listN List
 *  \param longW Lenght of list
 *  \param listNIn List with input data
**/
int listN::OutData(listN *&nowL,int longW,listNIn *&lin){
    nowL->goFront(nowL);
    lin->goFront(lin);
    double a,max=-10;
    int j=0;
    for(int i=0;i<longW;i++){
        a=1/(1+exp(-nowL->n->sumN(lin,longW)));
        if(a>max){
            max=a;
            j=i;
        }
        if(lin->next!=NULL)
        lin=lin->next;
        if(nowL->next!=NULL)
        nowL=nowL->next;
    }
    return j;
}

/** @brief Delete list
 *  \param listN List that delete
**/
void listN::Delete(listN *&nowL){
    nowL->goFront(nowL);
    listN *temp1=nowL->next;
    delete nowL;
    while(temp1->next!=NULL){
        nowL=temp1;
        nowL->n->Delete(nowL->n);
        temp1=temp1->next;
        delete nowL;
    }
    delete temp1;
}
int listNIn::returnN(){
    return intN->returnin();
}
listNIn::listNIn(){
}
/** @brief Create list
 *  \param listN First list
 *  \param longNIn Lenght of list
**/
void listNIn::create(int longNIn,listNIn *&nowL){
    nowL->prev=NULL;
    nowL->intN=new NeuronIn();
    for(int i=1;i<longNIn;i++){
        listNIn *temp=new listNIn();
        temp->intN=new NeuronIn();
        nowL->next=temp;
        temp->prev=nowL;
        nowL=temp;
    }
    nowL->next=NULL;
}
/** @brief Fill list
 *  \param listNIn List
 *  \param b Double dimention array with input data
 *  \param longIn Lenght of list
**/
void listNIn::filling(listNIn *&nowL,int longIn,char **b){
    for (int i = 0; i < longIn; i++) {
        for(int j=0;j<longIn;j++){
            nowL->intN->dataIn((int)b[i][j]);
            if(nowL->next!=NULL)
            nowL=nowL->next;
        }
    }
}
/** @brief Refill list
 *  \param listW List
 *  \param name Name of file from which is filled
 *  \param longW Lenght of list
**/
void listW::Refill(listW *&nowL,int longW,string name){
    nowL->goFront(nowL);
    ifstream fin("D:/wagi/wagi_" + name);
    double w_temp;
    for(int i=0;i<longW;i++)
    {
        fin>>w_temp;
        nowL->w=w_temp;
        if(nowL->next!=NULL)
        nowL=nowL->next;
    }
    fin.close();
}
/** @brief Give a sum on neuron
 *  \param listNIn List with input data
 *  \param longNN Lenght of list
**/
double listN::return_sum(int longNN,listNIn *&inN){
    return n->sumN(inN,longNN);
}
/** @brief Change value of weight
 *  \param deltawagi Array with value of change
 *  \param name Name of file in which is saved weight's
 *  \param longNN Lenght of list
**/
void listN::change_wagi(double *&deltawagi,string name,int longNN){
    n->unfill(deltawagi,name,longNN);
}
void listW::unfill(double *&deltawagi,string name,listW *&nowL,int longNN){
    nowL->goFront(nowL);
    ofstream fout("D:/wagi/wagi_"+name);
    for(int i=0;i<longNN;i++){
        fout<<nowL->w-deltawagi[i]<<endl;
        if(nowL->next!=NULL)
            nowL=nowL->next;
    }
    fout.close();
}
