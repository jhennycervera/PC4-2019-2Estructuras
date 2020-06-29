/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//Author: Jhenny Cervera Vargas(20182841)     

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncAux.h"
#define MAX_CAR 100

void LeerEspecialidad(struct Especialidad* especialidades,int*contEsp, char* nombrArch){
    FILE*archEsp;
    archEsp=abrirArch(nombrArch,"r");
    int numPal; 
    char *pal[3], *pt;
    (*contEsp)=0;
    while(1){
        pt=leerCadExact(archEsp);
        if(pt==NULL) break;
        sacaPalabras(pt, pal,&numPal, ',');
        especialidades[*contEsp].cod=pal[0];
        especialidades[*contEsp].nombre=pal[1];
        especialidades[*contEsp].credEgreso=atof(pal[2]);
        printf("%s %35s %10.2lf\n", especialidades[*contEsp].cod,especialidades[*contEsp].nombre,
                                especialidades[*contEsp].credEgreso);
        (*contEsp)++;
        free(pal[2]);
    }    
    fclose(archEsp);
}

void LeerCurso(struct Curso* curso,int *contCurs,char* nombreArch){
    FILE*archCurs;
    archCurs=abrirArch(nombreArch,"r");
    
    int numPal; 
    char *pal[3], *pt;
    (*contCurs)=0;
    while(1){
        pt=leerCadExact(archCurs);
        if(pt==NULL) break;
        sacaPalabras(pt, pal,&numPal, ',');
        curso[*contCurs].cod=pal[0];  //puntero tiene dm de pal
        curso[*contCurs].nombre=pal[1];
        curso[*contCurs].cred=atof(pal[2]);
        printf("%s %35s %10.2lf\n", curso[*contCurs].cod,curso[*contCurs].nombre,
                                curso[*contCurs].cred);
        (*contCurs)++;
        
        free(pal[2]);
       
    }
    
    fclose(archCurs);
}

void ProcesarAlumnos(struct Alumno *alumnos,int* contAlum,struct Curso* cursos,
                    int contCurs,struct Especialidad *especialidades, int contEsp){
    FILE*archAlum;
    archAlum=abrirArch("alumnos.csv", "r");
    
    (*contAlum)=0;
    int numPal, numCurs,j, pos;
    double sumNota;
    char *pal[155], *pt;
    while(1){
        pt=leerCadExact(archAlum);
        if(pt==NULL) break;
        sacaPalabras(pt, pal, &numPal, ',');
        alumnos[*contAlum].cod=pal[0];
        alumnos[*contAlum].nombre=pal[1];
        alumnos[*contAlum].espec=pal[2];
        
        numCurs=(numPal-3)/2;
        sumNota=0; //para cada linea
        j=3;
        alumnos[*contAlum].numCredAprob=0;
        //para hallar el promedio
        for(int i=0; i<numCurs;i++){
            pos=buscarCurs(pal[j],cursos,contCurs); //buscando curso
            if(pos!=-1){
                (alumnos[*contAlum].numCredAprob)+=cursos[pos].cred;
                sumNota+=(atof(pal[j+1])*cursos[pos].cred);    //numCred * nota    para sacar el promedio ponderado
            }
            
            j+=2; //si pongo j++ no porq seria 4
        }
        alumnos[*contAlum].prom=sumNota/alumnos[*contAlum].numCredAprob;
        //calculo el estado del alumno
        pos=buscarEsp(alumnos[*contAlum].espec,especialidades,contEsp); //buscando especialidad
            if(pos!=-1){
                if(alumnos[*contAlum].numCredAprob>=especialidades[pos].credEgreso)
                    alumnos[*contAlum].estado=1;
                else alumnos[*contAlum].estado=0;
            }
        (*contAlum)++;
        for(int i=3; i<numPal; i++) free(pal[i]);
        
    }
    fclose(archAlum);
}


void OrdenarPromedio(struct Alumno *alumnos,int contAlum){
    for(int i=0; i<contAlum; i++){
        for(int j=i+1; j<contAlum; j++){
            if(alumnos[i].prom<alumnos[j].prom){
                intercambiarEstruc(alumnos, i, j);
            }
        }
    }
}

void intercambiarEstruc(struct Alumno *alumnos, int i , int j){
    struct Alumno aux;
    aux=alumnos[i];
    alumnos[i]=alumnos[j];
    alumnos[j]=aux;
}
void HallarOrdenMerito(struct Alumno *alumnos, int contAlum){
    
    for(int i=0; i<contAlum; i++){
        if(i>=0 && i<(contAlum/3)) alumnos[i].ordenMerito=0;
        if(i>=(contAlum/3) && i< ((contAlum*2)/3)) alumnos[i].ordenMerito=1;
        else alumnos[i].ordenMerito=2;
    }
}

void OrdenarCodEspYCred(struct Alumno *alumnos, int contAlum){
    for(int i=0; i<contAlum-1; i++){
        for(int j=i+1; j<contAlum; j++){
            if(strcmp(alumnos[i].espec,alumnos[j].espec)>0 ||  
                    (strcmp(alumnos[i].espec,alumnos[j].espec)==0 && alumnos[i].numCredAprob<alumnos[j].numCredAprob ) ){
                
                intercambiarEstruc(alumnos, i, j);
            }
        }
    }
}


void ImprimirRep(struct Alumno* alumnos,int contAlum, struct Especialidad*especialidades, int contEsp){
    FILE* archRep;
    archRep=abrirArch("ReporteDeAlumnos.txt", "w");
    fprintf(archRep, "%45s\n", "RELACION DE ALUMNOS DE LA INSTITUCION");
    imprimirLin(archRep, '=',MAX_CAR );
    fprintf(archRep, "%s %20s %30s %10s %10s %20s %20s\n", "Codigo", "Nombre", "Especialidad0",
                        "Creditos", "Promedio", "Orden", "Situacion");
    imprimirLin(archRep, '-',MAX_CAR );
    int pos;
    for(int i=0; i<contAlum; i++){
        
        pos=buscarEsp(alumnos[i].espec,especialidades,contEsp);
        if(pos!=-1){
            
            fprintf(archRep,"%s %-30s %-30s %10.2lf %10.2lf ", alumnos[i].cod,alumnos[i].nombre,
                especialidades[pos].nombre,alumnos[i].numCredAprob,alumnos[i].prom);
            if(alumnos[i].ordenMerito==0) fprintf(archRep,"%20s","Tercio Superior");
            if(alumnos[i].ordenMerito==1) fprintf(archRep,"%20s", "Tercio Medio");
            else fprintf(archRep,"%20s","Tercio Inferior");
            if(alumnos[i].estado==0) fprintf(archRep,"%20s\n", "No egresado");
            else  fprintf(archRep,"%20s", "Egresado\n");
        }
 
    }
    imprimirLin(archRep, '=',MAX_CAR );
    fprintf(archRep, "Numero total de alumnos: %d",contAlum );
    fclose(archRep);
}

void imprimirLin(FILE* arch,char c,int cant){
    for(int i=0; i<cant; i++)
        fprintf(arch,"%c",c);
    fprintf(arch,"\n");
}
int buscarEsp(char* name, struct Especialidad *espec, int numArr){

    for(int i=0; i<numArr; i++){
	if(strcmp(name,espec[i].cod)==0) return i;
    }
    return -1;
}

int buscarCurs(char* curso,struct Curso *cursos,int contCurs){
    for(int i=0; i<contCurs; i++){
	if(strcmp(curso,cursos[i].cod)==0) return i;
    }
    return -1;
}

void sacaPalabras(char* text,char** palabra,int*numPal,char carSep){
    
    int i=0,j;
    char* pt, buff[200];
    (*numPal)=0;
    while(1){
        while(text[i]==carSep) i++;
        if(text[i]==0) break;
        j=0;
        while(text[i]!=carSep && text[i]!=0){
            buff[j]=text[i];
            j++;
            i++;
        }
        buff[j]=0;
        pt=(char*)malloc(sizeof(char)*(j+1));
        strcpy(pt,buff);
        palabra[*numPal]=pt;
        (*numPal)++;
    }
}
char* leerCadExact(FILE*arch){
    int len;
    char *pt, buff[500];
    leerCad(buff,500,arch);
    if(feof(arch)) return NULL;
    
    len=strlen(buff);
    pt=(char*)malloc(sizeof(char)*(len+1));
    strcpy(pt,buff);
    return pt;
}
void leerCad(char* cad, int tope, FILE*arch){
    int nCar;
    fgets(cad, tope, arch);
    nCar=strlen(cad);
    if(cad[nCar-1]=='\n') cad[nCar-1]=0;
}
    
FILE* abrirArch(const char* nombreArch, const char* modo){
    FILE* arch;
    arch=fopen(nombreArch,modo);
    if(arch==NULL){
        printf("ERROR: No se puede abrir el archivo %s\n",nombreArch );
        exit(1);
    }
    return arch;
}

