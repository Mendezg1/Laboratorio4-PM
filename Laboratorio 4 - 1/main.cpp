#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

string nombres[] = { "Pastel de chocolate", "White Mocha", "Café Americano 8oz", "Latte 8oz", "Toffee Coffee", "Cappuccino 8oz", "S'mores Latte", "Café tostado molido"};
int julio[] = {300, 400, 1590, 200, 390, 1455, 800, 60};
int agosto[] = {250, 380, 800, 250, 600, 1200, 1540, 15};
double precio[] = {60, 32, 22, 24, 28, 24, 32, 60};
double costos[] = {20, 19.20, 13.20, 17.20, 20.10, 17.20, 23, 20};

struct DatosMes{
    double ventasTotales;
    double utilidad;
    double costos;
};

struct Producto{
    int vendido; //unidades
    double ventas; //dinero
    double utilidad;
};

DatosMes meses[2];
Producto productos[16];

void *analisisMes(void *index){
    long prod = (long)index;
    if (prod < 8){

        productos[prod].vendido = julio[prod];
        meses[0].ventasTotales += productos[prod].ventas = (double)julio[prod] * precio[prod];
        meses[0].utilidad += productos[prod].utilidad = productos[prod].ventas - (productos[prod].vendido * costos[prod]);

    }
    else{
        long posicion = prod - 8;
        productos[prod].vendido = agosto[posicion];
        meses[1].ventasTotales += productos[prod].ventas = (double)agosto[posicion] * precio[posicion];
        meses[1].utilidad += productos[prod].utilidad = productos[prod].ventas - (productos[prod].vendido * costos[posicion]);
    }

    pthread_exit(NULL);
}

int main() {
    meses[0].costos = 45640.00;
    meses[1].costos = 40590.00;

    pthread_t hilos[16];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(long i = 0; i < 16; i++){
        pthread_create(&hilos[i], &attr, analisisMes, (void *)i);
    }

    for(long i = 0; i < 16; i++){
        pthread_join(hilos[i], NULL);
    }

    meses[0].utilidad -= meses[0].costos;
    meses[1].utilidad -= meses[1].costos;

    cout << "REPORTE DEL MES DE JULIO (VENTAS / UTILIDAD)\n"<< endl;
    for(int i = 0; i < 8; i++){
        cout << nombres[i] << ": " << productos[i].ventas << " / " << productos[i].utilidad << endl;
    }

    cout << "VENTAS DEL MES: "<< meses[0].ventasTotales << endl;
    cout << "COSTOS VARIABLES: "<<meses[0].costos << endl;
    cout << "UTILIDAD DEL MES: "<< meses[0].utilidad << endl << endl;

    cout << "REPORTE DEL MES DE AGOSTO (VENTAS / UTILIDAD)\n"<< endl;
    for(int i = 8; i < 16; i++){
        cout << nombres[i - 8] << ": " << productos[i].ventas << " / " << productos[i].utilidad << endl;
    }

    cout << "VENTAS DEL MES: "<< meses[1].ventasTotales << endl;
    cout << "COSTOS VARIABLES: "<<meses[1].costos << endl;
    cout << "UTILIDAD DEL MES: "<< meses[1].utilidad << endl;

}
