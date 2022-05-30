#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t;

    // codigo
    tiempo tMayor;
    tiempo tMenor = obtenerTiempo(v[0]);
    tiempo tActual;
    for (int i= 0; i < v.size(); i ++){
        tActual = obtenerTiempo(v[i]);
        if (tActual > tMayor){
            tMayor = tActual;
        }
        if (tActual< tMenor){
            tMenor = tActual;
        }
    }
    t = tMayor - tMenor;
    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/

int tiempoMenor(viaje v, int j) {
    int tMenor = j;
    for (int i = j; i <  v.size() -1 ; i++){
        tiempo tActual = obtenerTiempo(v[i]);
        if (tActual< obtenerTiempo(v[tMenor])){
            tMenor = i;
        }
    }
    return tMenor;
}

viaje swap(int i, int j , viaje v){
    tuple<tiempo, gps> x = v[i];
    tuple<tiempo, gps> y = v[j];
    v[i] = y;
    v[j] = x;
    return v;
}

viaje ordenarPorTiempo(viaje v){
    for (int i = 0; i < v.size() -1 ; i++){
        int tMenor =  tiempoMenor(v, i);
        v = swap(i, tMenor,v);
    }
    return v;
}

distancia distanciaTotal(viaje v) {
    distancia d;
    // codigo
    viaje v0 = v;
    v0 = ordenarPorTiempo(v);
    for (int i = 1; i< v0.size(); i++){
        d = d + distEnKM(obtenerPosicion(v0[i]), obtenerPosicion(v0[i-1]));
    }

    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
int velocidad(tuple<tiempo, gps> p1, tuple<tiempo, gps> p2){
    int distancia = distEnKM(obtenerPosicion(p2), obtenerPosicion(p1));
    tiempo tmp = (obtenerTiempo(p2)- obtenerTiempo(p1)) / 3600;
    int vel = distancia / tmp;
    return  vel;

}

bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    // codigo
    viaje v0 = v;

    v0 = ordenarPorTiempo(v);

    for ( int i = 1; i <v.size() ; i++){
        int velocidadPorHora = velocidad(v0[i-1],v0[i]);
        if (velocidadPorHora > 80){
            resp = true;
        }
    }
    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    // codigo

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/


bool viajeEnFranja(viaje v,tiempo t0, tiempo tf){
    bool enFranja = false;
    for(int i = 0; i<v.size(); i++){
        tiempo tActual = obtenerTiempo(v[i]);
        if (tActual > t0 && tActual< tf){
            enFranja = true;
        }
    }
    return enFranja;
}


int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp  = 0;
    // codigo
    for(int i = 0; i<f.size(); i++){
        viaje v = f[i];
        if (viajeEnFranja(v, t0, tf)){
            resp = resp +1;
        }


    }
    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    // codigo

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp;
    // codigo

    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    return;
}

