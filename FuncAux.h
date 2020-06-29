/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.h
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 28 de junio de 2020, 22:35
 */

#ifndef FUNCAUX_H
#define FUNCAUX_H
#include "estructuraEspeciali.h"
#include "estructuraCursos.h"
#include "EstructuraAlum.h"

void LeerEspecialidad(struct Especialidad* ,int*, char* );
void LeerCurso(struct Curso* ,int *,char* );
FILE* abrirArch(const char* , const char* );
void leerCad(char* , int , FILE*);
int buscarEsp(char* , struct Especialidad*, int );
int buscarCurs(char* ,struct Curso *,int );
void sacaPalabras(char* ,char** ,int*,char );
char* leerCadExact(FILE*);
void ProcesarAlumnos(struct Alumno *,int*,struct Curso* ,
                    int ,struct Especialidad *, int );
void intercambiarEstruc(struct Alumno *, int  , int );
void OrdenarPromedio(struct Alumno *,int );
void imprimirLin(FILE* ,char, int );
void ImprimirRep(struct Alumno* ,int , struct Especialidad*, int );
void HallarOrdenMerito(struct Alumno *, int );
void OrdenarCodEspYCred(struct Alumno *, int );


#endif /* FUNCAUX_H */

