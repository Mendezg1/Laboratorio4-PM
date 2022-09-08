#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace  std;

int silo, bodega;
pthread_mutex_t mutexFabrica;

void *procesoTostadora1(void *index){

    for ( int i = 0; i < 200; i++){
        pthread_mutex_lock(&mutexFabrica);
        silo++;
        cout << "<----| Tostadora 1 produjo 1 libra de café tostado |---->" << endl;
        cout << "<----| Libras de cafe en silo: "<< silo << " |---->" << endl;
        pthread_mutex_unlock(&mutexFabrica);
        sleep(1);
    }

}

void *procesoTostadora2(void *index){

    for ( int i = 0; i < 200; i++){
        pthread_mutex_lock(&mutexFabrica);
        silo++;
        cout << "<----| Tostadora 2 produjo 1 libra de café tostado |---->" << endl;
        cout << "<----| Libras de cafe en silo: "<< silo << " |---->" << endl;
        pthread_mutex_unlock(&mutexFabrica);
        sleep(1);
    }

}

void *procesoEmpacadora(void *index){

    while(bodega != 400){
        if(silo <= 5 || bodega >= 394{
            pthread_mutex_lock(&mutexFabrica);
            silo--;
            bodega++;
            cout << "<----| Empacadora produjo 1 libra de café |---->" << endl;
            cout << "<----| Libras de cafe en bodega: "<< bodega << " |---->" << endl;
            pthread_mutex_unlock(&mutexFabrica);
            sleep(1);
        }
    }

}



int main() {

    pthread_mutex_init(&mutexFabrica, NULL);
    pthread_t h1, h2, h3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&h1, &attr, procesoTostadora1, NULL);
    pthread_create(&h2, &attr, procesoTostadora2, NULL);
    pthread_create(&h3, &attr, procesoEmpacadora, NULL);

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(h3, NULL);

    pthread_mutex_destroy(&mutexFabrica);

}
