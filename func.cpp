#include "func.h"
#include "list.h"
#include "neuron.h"
using namespace std;
/** @brief Make empty files with weight
 *  \param s Name of set of weight (can be only number)
**/
void make_null_wagi(string s){
    for(int i=0;i<25;i++){
        int j=i;string ss="";
        if(j==0)ss="0";
        while(j!=0){
            ss+=char(j%10+'0');
            j/=10;
        }
        ofstream fout("D:/wagi/wagi_"+s+ss);
        for(int i=0;i<25;i++)
        {
            fout<<0.0001<<endl;
        }
        fout.close();
    }
}
/** @brief Show in console array
 *  \param a Array that showed
**/
void show_array(char **&a){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}
/** @brief Make empty dynamic double dimention array nxn
 *  \param a Array
 *  \param n Size of array
**/
void make_null_array(char **&a,int n){
    a=new char*[n];
    for(int i=0;i<5;i++){
        a[i]=new char[n];
        for(int j=0;j<5;j++){
            a[i][j]='0';
        }
    }
}
/** @brief Make file with double dimention array(for dataset)
 *  \param a Array
 *  \param f1 Index in dataset
 *  \param n Size of array
**/
void make_dataset(char **a,int &f1,int n){
    string s="";
    int f2=f1;
    while(f2!=0){
        s+=f2%10+'0';
        f2/=10;
    }
    ofstream fout("D:/dataset/out"+s+".txt");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fout<<a[i][j]<<" ";
        }
        fout<<std::endl;
    }
    fout.close();
    f1++;
}
/** @brief Delete double dimention array
 *  \param a Array
 *  \param n Size of array
**/
void array_delete(char **&a,int n){
    for(int i=0;i<n;i++){
        delete a[i];
    }
}
/** @brief Сhanges data in array's
 *  \param a Array 1
 *  \param b Array 2
 *  \param n Size of array's
**/
void swop(char**&a,char**&b,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            swap(a[i][j],b[i][j]);
        }
    }
}
/** @brief Writes data from array a to b
 *  \param a Array 1
 *  \param b Array 2
 *  \param n Size of array's
**/
void equal(char**&a,char**&b,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=b[i][j];
        }
    }
}
/** @brief Learning 2 neural-net on dataset
 *  \param NN0 neural-net that game X
 *  \param NN1 neural-net that game O
 *  \param long_dataset Number of files in datset
 *  \param n Size of array's in dataset
**/
void learn_NN(NeuroNet *NN0,NeuroNet *NN1,int long_dataset,int n){
    char**a,**b;
    string s="";
    bool gamer=0,empty_array=0;
    int g=1,need[2];
    while(g!=0){
        s+=g%10+'0';
        g/=10;
    }
    ifstream fin("D:/dataset/out"+s+".txt");
    make_null_array(b,n);
    for(int l=0;l<n;l++){
        for(int k=0;k<n;k++){
            fin>>b[l][k];
        }
    }
    fin.close();
    for(int i=2;i<=long_dataset;i++){
        make_null_array(a,n);
        g=i;
        s="";
        while(g!=0){
            s+=g%10+'0';
            g/=10;
        }
        ifstream fin("D:/dataset/out"+s+".txt");
        for(int l=0;l<n;l++){
            for(int k=0;k<n;k++){
                fin>>a[l][k];
                //cout<<a[l][k]<<" ";
            }
            //cout<<endl;
        }
        fin.close();
        for(int l=0;l<n;l++){
            for(int k=0;k<n;k++){
                if(a[l][k]!='0'){
                    empty_array=1;k=n;l=n;
                }
            }
        }
        if(empty_array)
        {
            for(int l=0;l<n;l++){
                for(int k=0;k<n;k++){
                    if(b[l][k]=='0' && a[l][k]!='0'){
                        gamer=a[l][k]=='X';
                        need[0]=l;need[1]=k;l=n;k=n;
                    }
                }
            }
            if(gamer){
                NN0->data_in(b);
                NN0->Learning(need[0]*n+need[1],long_dataset/2);
            }
            else{
                NN1->data_in(b);
                NN1->Learning(need[0]*n+need[1],long_dataset/2);
            }
            swop(a,b,n);
            array_delete(a,n);
        }
    }
}
/** @brief Learning 2 neural-net by play one-to-one
 *  \param NN0 neural-net that game O
 *  \param NN1 neural-net that game X
 *  \param long_dataset Number of files in datset
 *  \param n Size of array's in dataset
**/
void learn_DNN(NeuroNet *NN0,NeuroNet *NN1,int number_learn,int n){
    char **a,**b,**c,player='X';
    int step;
    for(int o=0;o<number_learn;o++){
        make_null_array(a,n);
        make_null_array(b,n);
        make_null_array(c,n);
        while(win(c,n)=='0'){
            if(player=='X')
                step=NN1->work(c);
            else
                step=NN0->work(c);
            while(c[step/n][step%n]!='0'){
                if(player=='X'){
                    NN1->nonLearning(step);
                    step=NN1->work(c);
                }
                else
                {
                    NN0->nonLearning(step);
                    step=NN0->work(c);
                }
            }
            equal(a,b,n);
            equal(b,c,n);
            c[step/n][step%n]=player;
            if(player=='X')player='O';
            else player='X';
        }
        if(win(c,n)!='Y')
        {
            if(player=='X')
            {
                NN1->nonLearning(NN1->work(a));
            }
            else
            {
                NN0->nonLearning(NN0->work(a));
            }
        }

    }
}
/** @brief Check of winner tic-tac-toe
 *  \param b Array that copy of table tic-tac-toe
 *  \param n Size of array's in dataset
**/
char win(char **&b,int n){
    char t;
    int k=0;
    //vertical
    for(int j=0;j<n;j++){
        for(int l=0;l<n-3;l++){
            t=b[j][l];
            if(t!='0')
            {
                for(int i=l+1;i<n+l-1;i++){
                    if(b[j][i]==t){
                        k++;
                    }
                }
                if(k==3){
                    return t;
                }
            }
            k=0;
        }
    }
    //horizontal
    for(int j=0;j<n;j++){
        for(int l=0;l<n-3;l++){
            t=b[l][j];
            if(t!='0')
            {
                for(int i=l+1;i<n+l-1;i++){
                    if(b[i][j]==t){
                        k++;
                    }
                }
                if(k==3){
                    return t;
                }
            }
            k=0;
        }
    }
    //main diagonal
    for(int l=0;l<n-3;l++){
        t=b[l][l];
        if(t!='0')
        {
            for(int i=l+1;i<n-1+l;i++){
                if(t==b[i][i]){
                    k++;
                }
            }
            if(k==3){
                return t;
            }
        }
        k=0;
    }
    //upper and above main diagonal
    t=b[0][1];
    if(t!='0')
    {
        for(int i=0;i<n-1;i++){
            if(t==b[i][i+1]){
                k++;
            }
        }
        if(k==4 && t!='0'){
            return t;
        }
    }
    k=0;
    t=b[1][0];
    if(t!='0')
    {
        for(int i=0;i<n-1;i++){
            if(t==b[i+1][i]){
                k++;
            }
        }
        if(k==4){
            return t;
        }
    }
    k=0;
    //anti-diagonal
    for(int l=0;l<n-3;l++){
        t=b[l][n-l-1];
        if(t!='0')
        {
            for(int i=l+1;i<n+l-1;i++){
                if(t==b[i][n-i-1]){
                    k++;
                }
            }
            if(k==3){
                return t;
            }
        }
        k=0;
    }
    //above and upper anti-diagonal
    t=b[1][n-1];
    if(t!='0')
    {
        for(int i=2;i<n;i++){
            if(t==b[i][n-i]){
                k++;
            }
        }
        if(k==3){
            return t;
        }
    }
    k=0;
    t=b[0][n-2];
    if(t!='0')
    {
        for(int i=1;i<n-1;i++){
            if(t==b[i][n-i-2]){
                k++;
            }
        }
        if(k==3){
            return t;
        }
    }
    k=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(b[i][j]=='0')k++;
        }
    }
    if(k==0)return 'Y';
    return '0';
}
