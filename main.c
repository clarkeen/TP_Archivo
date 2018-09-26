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

/*
 * 
 */
int main(int argc, char** argv) {
    switch (argc) {
        case 1:
            menu_principal();
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
                    menu_4();
                    break;
            }
            break;
    }
    return (EXIT_SUCCESS);
}

