/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 28 de junio de 2020, 22:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncAux.h"
#include "EstructuraAlum.h"
#include "estructuraCursos.h"
#include "estructuraEspeciali.h"
/*
 * 
 */
int main(int argc, char** argv) {

    
    struct Alumno alumnos[1000];
    struct Curso cursos[150];
    struct Especialidad especialidades[10];
    int contEsp, contAlum, contCurs;
    
    
    LeerEspecialidad(especialidades,&contEsp,"especialidades.csv");
    LeerCurso(cursos,&contCurs,"cursos.csv");
    
    ProcesarAlumnos(alumnos,&contAlum,cursos,contCurs,especialidades, contEsp);
    
    
    OrdenarPromedio(alumnos, contAlum);
    HallarOrdenMerito(alumnos, contAlum);
    OrdenarCodEspYCred(alumnos,contAlum);
    for(int i=0; i<contAlum; i++){
        printf("%s %30s %30s %.2lf %.2lf %10d %10d\n", alumnos[i].cod,alumnos[i].nombre,
                alumnos[i].espec,alumnos[i].numCredAprob,alumnos[i].prom, alumnos[i].ordenMerito,
                alumnos[i].estado);
    }
   
    ImprimirRep(alumnos,contAlum, especialidades,contEsp);
    
    return (EXIT_SUCCESS);
}

