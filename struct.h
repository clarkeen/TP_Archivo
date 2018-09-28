/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   struct.h
 * Author: desktop
 *
 * Created on 9 de septiembre de 2018, 16:44
 */

#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define LISTA_SIZE  10
//#define LISTA_HASH_SIZE  (LISTA_SIZE) * 100   /* 1000 <= 10 * 100 <= (LISTA_SIZE = 1 / 1%) */
//#define LISTA_HASH_SIZE  (int)((LISTA_SIZE)/(0.01))   /* LISTA_SIZE / 1% */
#define DNI_MIN  10000000        /* 8 Dijitos sin '.' */
#define DNI_MAX  9999999999      /* 10 Dijitos sin '.' */
#define CARACTERES_DNI  12
#define CARACTERES_NOMBRE  30
#define CARACTERES_APELLIDO  30
#define CARACTERES_TABLA_PRIMARIA  (int) ((3) + (3) + (CARACTERES_DNI))
#define MASCARA_CLAVE_PRIMARIA  "%.3s%.3s%s"     /* CARACTERES_NOMBRE=3 | CARACTERES_APELLIDO=3 | CARACTERES_DNI=12 */

#define error(x)  printf("\nERROR, %s\n\n", x)
#define limpiar_salto_linea()  while (getchar() != '\n')
#define limpiar_tabla_hash()  0     /* limpia una variable de tipo tabla_hash */

#define ARCHIVO  "archivo.bin"
#define TABLA_HASHING  "tabla_hashing.bin"
#define TABLA_PRIMARIA  "tabla_primaria.bin"

typedef struct {
    char dni[CARACTERES_DNI];
    char nombre[CARACTERES_NOMBRE];
    char apellido[CARACTERES_APELLIDO];
} registro;

typedef struct {
    char clave_primaria [CARACTERES_TABLA_PRIMARIA];
    long int item;
} tabla_primaria;

long int sumar_caracteres(char cadena[]);
int tamanio_tabla_hash(void);
int digitos_tamanio_hash(void);
int leer_regisrto(registro persona_vector[]);
int valida_numero_menu(char texto[], int num_min, int num_max);
void pausa(void);
void mostrar_tabla_hash(void);
void crear_archivo_struct(void);
void mostrar_tabla_primaria(void);
void mostrar_todos_los_registros(void);
void mostrar_un_registro(long int item);
void guardar_registro(registro persona);
void crear_archivo_indice_hashing(void);
void crear_archivo_indice_primario(void);
void acceso_directo_indice_hashing(void);
void acceso_directo_indice_primario(void);
void acceder_archivo_tabla_primaria(registro persona);
void unsigned_to_char(unsigned int dni, char letra[]);
void acceder_archivo_tabla_hash(registro persona, int size_hash);
void guardar_tabla_hash(long int tabla_hash_arreglo[], int size_hash);
void crear_tabla_hashing(long int tabla_hash_arreglo[], int size_hash);
void crear_tabla_primaria(tabla_primaria tabla_primaria_arreglo[], int size_hash);
void guardar_tabla_primaria(tabla_primaria tabla_primaria_arreglo[], int size_hash);
void ordenar_tabla_primaria(tabla_primaria tabla_primaria_arreglo[], int size_hash);
registro cargar_registro(void);
registro limpiar_registro(void);
tabla_primaria limpiar_tabla_primaria(void);

#endif /* STRUCT_H */
