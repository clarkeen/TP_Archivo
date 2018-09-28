/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: desktop
 *
 * Created on 9 de septiembre de 2018, 15:36
 */


#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "struct.h"

int main(int argc, char** argv) {

    int op_N = 1;
    switch (argc) {
        case 1:
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
                        menu_opcion_4();
                        pausa();
                        break;
                    case 0:
                        puts("--------------------------");
                        puts("|         Adios          |");
                        puts("--------------------------");
                        break;
                }
            } while (op_N != 0);
            break;
        case 2:
            switch (*argv[1]) {
                case '1':
                    crear_archivo_struct();
                    break;
                case '2':
                    crear_archivo_indice_primario();
                    break;
                case '3':
                    crear_archivo_indice_hashing();
                    break;
                case '4':
                    menu_opcion_4();
                    break;
            }
            break;
    }
    return (EXIT_SUCCESS);
}

