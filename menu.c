/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "menu.h"

void menu_principal() {
    int op_N = 1;
    do {
        op_N = valida_numero_menu("\tTrabajo practico Archivo\n\n"
                "1-crear un archivo con estructura de campo y regitro.\n"
                "2-crear un archivo con un indice primario.\n"
                "3-crear un tabla de hashing para acceso directo al archivo (utilizar saturacion prograsiva).\n"
                "4-realizar prueba de acceso directo al archivo\n"
                "0-Salir\n", 0, 4);
        switch (op_N) {
            case 1:
                crear_archivo_struct();
                pausa();
                break;
            case 2:
                crear_archivo_indice_primario();
                pausa();
                break;
            case 3:
                crear_archivo_indice_hashing();
                pausa();
                break;
            case 4:
                menu_4();
                break;
            case 0:
                puts("--------------------------");
                puts("|         Adios          |");
                puts("--------------------------");
                break;
        }
    } while (op_N != 0);
}

void menu_4() {
    int op_N = 1;
    do {
        op_N = valida_numero_menu("\tRealizar prueba de acceso directo al archivo\n\n"
                "1-tabla de indice primario.\n"
                "2-tabla de indice hashing.\n"
                "0-menu prinsipal\n", 0, 4);
        switch (op_N) {
            case 1:
                acceso_directo_indice_primario();
                pausa();
                break;
            case 2:
                acceso_directo_indice_hashing();
                pausa();
                break;
        }
    } while (op_N != 0);
}

