#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "neuron.h"
#include "list.h"
#include "func.h"
#include <fstream>
#include <iostream>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const int n=5;
    QPushButton* buts[5][5];
    buts[0][0] = ui->But1;
    buts[1][0] = ui->But2;
    buts[2][0] = ui->But3;
    buts[3][0] = ui->But4;
    buts[4][0] = ui->But5;
    buts[0][1] = ui->But6;
    buts[1][1] = ui->But7;
    buts[2][1] = ui->But8;
    buts[3][1] = ui->But9;
    buts[4][1] = ui->But10;
    buts[0][2] = ui->But11;
    buts[1][2] = ui->But12;
    buts[2][2] = ui->But13;
    buts[3][2] = ui->But14;
    buts[4][2] = ui->But15;
    buts[0][3] = ui->But16;
    buts[1][3] = ui->But17;
    buts[2][3] = ui->But18;
    buts[3][3] = ui->But19;
    buts[4][3] = ui->But20;
    buts[0][4] = ui->But21;
    buts[1][4] = ui->But22;
    buts[2][4] = ui->But23;
    buts[3][4] = ui->But24;
    buts[4][4] = ui->But25;
    for (int i = 0; i < n; i++)
        for(int j=0;j<n;j++){
            connect(buts[0][0], &QPushButton::clicked, this,[=](){
                MainWindow::handleButton(i,j);
            });
        }
//    make_null_wagi("0");
//    make_null_wagi("1");
//    char **b;
//    make_null_array(b,n);
    NeuroNet *biba=new NeuroNet(5,0),*boba=new NeuroNet(5,1);
    //learn_DNN(boba,biba,100,n);
    delete biba;
    delete boba;

}

MainWindow::~MainWindow()
{
    delete ui;
}
char player;
const int n=5;
char **b;
bool start=0;
int a=0,g=0;
NeuroNet *biba=new NeuroNet(5,0);
NeuroNet *boba=new NeuroNet(5,1);

void MainWindow::handleButton(int i,int j)
{
    QPushButton* but = qobject_cast<QPushButton*>(sender());
    QPushButton* (**buts)=new QPushButton**[5];
    for(int k=0;k<n;k++){
        buts[k]=new QPushButton*[5];
        for(int l=0;l<n;l++)
            buts[k][l]=*(&but+i*5+j);
    }
    if(b[j][i]=='0' && start==1){
        switch (a) {
            case 0:
                buts[i][j]->setText("X");
                b[j][i]='X';
                a=1;
                break;
            case 1:
                buts[i][j]->setText("O");
                b[j][i]='O';
                a=0;
                break;
        }
        winner();
        int nnstep;
        switch (a) {
        case 0:
            nnstep=biba->work(b);
            buts[nnstep/n][nnstep%n]->setText("X");
            a=1;
            break;
        case 1:
            nnstep=boba->work(b);
            buts[nnstep/n][nnstep%n]->setText("O");
            a=0;
            break;
        }
        winner();
    }



}

void MainWindow::on_Start_clicked()
{
    if(g!=0){
        array_delete(b,n);
        ui->Start->setText("Reset game");
    }
    else g++;
    make_null_array(b,n);
    ui->Win->setText("");
    ui->But25->setText("");
    ui->But24->setText("");
    ui->But23->setText("");
    ui->But22->setText("");
    ui->But21->setText("");
    ui->But20->setText("");
    ui->But19->setText("");
    ui->But18->setText("");
    ui->But17->setText("");
    ui->But16->setText("");
    ui->But15->setText("");
    ui->But14->setText("");
    ui->But13->setText("");
    ui->But12->setText("");
    ui->But11->setText("");
    ui->But10->setText("");
    ui->But9->setText("");
    ui->But8->setText("");
    ui->But7->setText("");
    ui->But6->setText("");
    ui->But5->setText("");
    ui->But4->setText("");
    ui->But3->setText("");
    ui->But2->setText("");
    ui->But1->setText("");
    start=1;
    player=a;
    //make_dataset(b,g,n);
}

void MainWindow::winner(){
    QString t=" ";
    int k=0;
    //vertical
    for(int j=0;j<n;j++){
        for(int l=0;l<n-3;l++){
            t[0]=b[j][l];
            if(t[0]!='0')
            {
                for(int i=l+1;i<n+l-1;i++){
                    if(b[j][i]==t[0]){
                        k++;
                    }
                }
                if(k==3){
                    ui->Win->setText("Winner "+t);
                    start=0;
                    break;
                }
            }
            k=0;
        }
    }
    //horizontal
    for(int j=0;j<n;j++){
        for(int l=0;l<n-3;l++){
            t[0]=b[l][j];
            if(t[0]!='0')
            {
                for(int i=l+1;i<n+l-1;i++){
                    if(b[i][j]==t[0]){
                        k++;
                    }
                }
                if(k==3){
                    ui->Win->setText("Winner "+t);
                    start=0;
                    break;
                }
            }
            k=0;
        }
    }
    //main diagonal
    if(start){
        for(int l=0;l<n-3;l++){
            t[0]=b[l][l];
            if(t[0]!='0')
            {
                for(int i=l+1;i<n-1+l;i++){
                    if(t[0]==b[i][i]){
                        k++;
                    }
                }
                if(k==3){
                    ui->Win->setText("Winner "+t);
                    start=0;
                    break;
                }
            }
            k=0;
        }
    }
    //upper and above main diagonal
    if(start){
        t=b[0][1];
        if(t[0]!='0')
        {
            for(int i=0;i<n-1;i++){
                if(t==b[i][i+1]){
                    k++;
                }
            }
            if(k==4 && t[0]!='0'){
                ui->Win->setText("Winner "+t);
                start=0;
            }
        }
        k=0;
    }
    if(start){
        t=b[1][0];
        if(t[0]!='0')
        {
            for(int i=0;i<n-1;i++){
                if(t==b[i+1][i]){
                    k++;
                }
            }
            if(k==4){
                ui->Win->setText("Winner "+t);
                start=0;
            }
        }
        k=0;
    }
    //anti-diagonal
    if(start){
        for(int l=0;l<n-3;l++){
            t[0]=b[l][n-l-1];
            if(t[0]!='0')
            {
                for(int i=l+1;i<n+l-1;i++){
                    if(t[0]==b[i][n-i-1]){
                        k++;
                    }
                }
                if(k==3){
                    ui->Win->setText("Winner "+t);
                    start=0;
                    break;
                }
            }
            k=0;
        }
    }
    //above and upper anti-diagonal
    if(start){
        t=b[1][n-1];
        if(t[0]!='0')
        {
            for(int i=2;i<n;i++){
                if(t==b[i][n-i]){
                    k++;
                }
            }
            if(k==3){
                ui->Win->setText("Winner "+t);
                start=0;
            }
        }
        k=0;
    }
    if(start){
        t=b[0][n-2];
        if(t[0]!='0')
        {
            for(int i=1;i<n-1;i++){
                if(t==b[i][n-i-2]){
                    k++;
                }
            }
            if(k==3){
                if(t=='X')
                ui->Win->setText("Winner "+t);
                start=0;
            }
        }
        k=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(b[i][j]=='0')k++;
        }
    }
    if(k==0){
        ui->Win->setText("Draw");
        start=0;
    }
    //make_dataset(b,g,n);

}
