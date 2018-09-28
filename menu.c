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


void menu_opcion_4() {
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

