/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstructuraAlum.h
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 29 de junio de 2020, 8:47
 */

#ifndef ESTRUCTURAALUM_H
#define ESTRUCTURAALUM_H

struct Alumno{
    char *cod;
    char *nombre;
    char* espec;
    double prom;
    double numCredAprob;
    int estado;
    int ordenMerito;
};


#endif /* ESTRUCTURAALUM_H */

