#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <math.h>

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

// O(n) recorre todos los elementos para asegurarse de tener el mayor y el menor.
// // n = |v|

/************++*********************** EJERCICIO distanciaTotal ************++*********************/

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

// es O(n^2 + n), ordena el vector y despues lo recorre, pertenece a O(n^2).
// n = |v|
/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/


bool excesoDeVelocidad(viaje v) {
    bool resp = false;


    v = ordenarPorTiempo(v);
    int i = 0;
    while(i < v.size() && velocidad(v[i-1],v[i]) < 80){
        i++;
    }
    return i != v.size();
}


// es O(n^2 + n), ordena el vector y despues lo recorre, pertenece a O(n^2).


/************************************ EJERCICIO recorridoNoCubierto
 * *******************************/

vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    // codigo

    for (int i = 0; i < r.size(); i++){
        if (!puntoCubiertoViaje(r[i],v,u))
        {
            resp.push_back(r[i]);
        }
    }
    return resp;
}

/***************************************** EJERCICIO flota ***************************************/



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

// Sea n = |f| y m = elementos de un vector cualquiera dentro de f.
// En el peor caso la complejidad es O(n * m) recorre todos los elementos de f y los elementos dentro de ellos.
/************************************** EJERCICIO construirGrilla *******************************/




grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};

    double altoCelda = (get<0>(esq1) - get<0>(esq2))/n;
    double anchoCelda = (get<1>(esq2) - get<1>(esq1))/m;

    // i fila, j columna
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {

            tuple<gps,gps,nombre> elem = make_tuple(esqSuperior(altoCelda,
                                                                anchoCelda,j,
                                                                i,esq1,
                                                                n,m),
                                                    esqInferior(altoCelda,
                                                                anchoCelda,j,
                                                                i,esq2,
                                                                n,m), make_tuple(i,j));
            resp.push_back(elem);

        }

    }
    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int saltos = 0;
    v=ordenarPorTiempo(v);
    for (int i = 0; i < v.size()-1; ++i) {
        bool sonSaltoConsecutivo = sonSalto(obtenerPosicion(v[i]),obtenerPosicion(v[i+1])
                                            ,g);
        if(sonSaltoConsecutivo)saltos+=1;
    }

    return saltos;
}

// Ordenar es O(n^2) + iterar n-1*sonSaltoConsecutivo que es O(n) = O(n^2)

/************************************* EJERCICIO corregirViaje ******************************/

bool noEsError (tiempo t, vector<tiempo> errores){
    int i=0;
    while (i< errores.size() && t != errores[i]){
        i ++;
    }
    return i == errores.size();
}

double latitudCorrecta(tuple<tiempo, gps> p1, tuple<tiempo, gps> p2,tuple<tiempo, gps> corregir){
    float lat ;
    lat = ((obtenerLatitud(obtenerPosicion(p2)) - obtenerLatitud(obtenerPosicion(p1))) *
           (obtenerTiempo(corregir)- obtenerTiempo(p1))) /
          (obtenerTiempo(p2) - obtenerTiempo(p1)) + obtenerLatitud(obtenerPosicion(p1));
    return  lat;

}

float longitudCorrecta(tuple<tiempo, gps> p1, tuple<tiempo, gps> p2,tuple<tiempo, gps> corregir){
    float lat ;
    lat = ((obtenerLongitud(obtenerPosicion(p2)) - obtenerLongitud(obtenerPosicion(p1))) *
           (obtenerTiempo(corregir)- obtenerTiempo(p1))) /
                  (obtenerTiempo(p2) - obtenerTiempo(p1)) + obtenerLongitud(obtenerPosicion(p1));
    return  lat;

}



viaje masCercanos(viaje v, tiempo t,vector<tiempo> errores){
    tuple<tiempo, gps> puntoMasCerca ;
    tuple<tiempo, gps> puntoCerca ;
    viaje puntoMasCercanos;
    for (int i = 0; i< v.size();i++){
        if (abs(obtenerTiempo(v[i])- t) < abs(obtenerTiempo(puntoMasCerca)-t) &&
        noEsError(obtenerTiempo(v[i]), errores)){
            puntoMasCerca = v[i];
        }
    }
    puntoMasCercanos.push_back(puntoMasCerca);
    for (int i = 0; i< v.size();i++){
        if (v[i] != puntoMasCerca && abs(obtenerTiempo(v[i])- t) < abs(obtenerTiempo(puntoCerca)-t) &&
             noEsError(obtenerTiempo(v[i]), errores)){
            puntoCerca = v[i];
        }
    }
    puntoMasCercanos.push_back(puntoCerca);
    return puntoMasCercanos;
}


gps corregirError (viaje v, tiempo error,vector<tiempo> errores ){
    int i= 0;
    while (i<v.size() && obtenerTiempo(v[i]) != error){i++;}
    viaje puntosCercanos = masCercanos(v, obtenerTiempo(v[i]), errores);
    double latitud = latitudCorrecta(puntosCercanos[0],puntosCercanos[1], v[i]);
    double  longitud = longitudCorrecta(puntosCercanos[0],puntosCercanos[1], v[i]);
    gps corregido = obtenerPosicion(v[i]);
    get<0>(corregido) = latitud;
    get<1>(corregido) = longitud;
    return  corregido;
}


void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig
    for (int i=0 ; i < errores.size();i++){
        gps corregido = corregirError(v, errores[i], errores);
        for (int j = 0; j< v.size(); j++ ){
            if(obtenerTiempo(v[j])== errores[i]){
                get<1>(v[j]) = corregido;
            }
        }
    }

}

