/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "struct.h"


registro registro_arreglo[LISTA_SIZE];
tabla_primaria tabla_primaria_arreglo[LISTA_SIZE];
long int tabla_hash_arreglo[LISTA_HASH_SIZE];

/* ****** valida el número ingresado en la opcion entre opcion_min a num_max ****** */
int valida_numero_menu(char texto[], int opcion_min, int num_max) {
    int num;
    bool encontro;
    printf("%s\nIngrese un opción: ", texto);
    scanf("%d", &num);
    do {
        encontro = false;
        //limpia stdin, si queso un salto de linea
        //fflush(stdin);
        limpiar_salto_linea();
        if (num < opcion_min || num > num_max) { //si esta fuera de rango, muestra un error
            system("clear");
            printf("%s", texto);
            error("ingrese un número valida.");
            printf("Ingrese un opción: ");
            scanf("%d", &num);
        } else
            encontro = true;
    } while (encontro == false);
    system("clear");
    return num;
}

/* ****** valida el número ingresado entre 1 a 100 ****** */
float valida_numero_porcentaje() {
    float num;
    bool encontro;
    do {
        encontro = false;
        printf("Ingrese el porcentage del hash : %% ");
        scanf("%f", &num);
        //limpia stdin, si queso un salto de linea
        //fflush(stdin);
        limpiar_salto_linea();
        if (num < 1 || num > 100) { //si esta fuera de rango, muestra un error
            system("clear");
            error("ingrese un número valida. (1 al 100)");
        } else
            encontro = true;
    } while (encontro == false);
    return num;
}

/* ****** detener para ver en patalla ****** */
void pausa(void) {
    char i = '\0';
    puts("Presione ENTER para continuar...");
    fflush(stdin);
    scanf("%c", &i);
    system("clear");
}

/* ****** valida el DNI ingresado entre DNI_MIN a DNI_MAX ****** */
unsigned int validar_numero_dni() {
    bool encontro;
    unsigned int num;
    do {
        encontro = false;
        printf("Ingrese el DNI: ");
        scanf("%u", &num);
        //limpia stdin, si queso un salto de linea
        //fflush(stdin);
        limpiar_salto_linea();
        if (num < DNI_MIN || num > DNI_MAX) {
            system("clear");
            error("ingrese un número DNI valido.");
        } else
            encontro = true;
    } while (encontro != true);
    return num;
}

/* ****** limpia una variable de tipo registro ****** */
registro limpiar_registro(void) {
    registro limpia;
    memset(limpia.dni, '\0', sizeof (limpia.dni));
    memset(limpia.nombre, '\0', sizeof (limpia.nombre));
    memset(limpia.apellido, '\0', sizeof (limpia.apellido));
    return limpia;
}

/* ****** limpia una variable de tipo tabla_primaria ****** */
tabla_primaria limpiar_tabla_primaria(void) {
    tabla_primaria limpia;
    limpia.item = 0;
    memset(limpia.clave_primaria, '\0', sizeof (limpia.clave_primaria));
    return limpia;
}

/* ****** suma los caracteres de una cadena ****** */
long int sumar_caracteres(char cadena[]) {
    int i;
    long int suma = 0;
    for (i = 0; i < strlen(cadena); i++)
        suma += cadena[i];
    return suma;
}

/* ****** crea un registro ****** */
registro cargar_registro(void) {
    registro persona = limpiar_registro();
    int i;
    unsigned int dni;
    fflush(stdin);
    /* ****** cargar DNI ****** */
    dni = validar_numero_dni();
    unsigned_to_char(dni, persona.dni);
    sscanf(persona.dni, "%[^\n]", persona.dni);
    //limpiar_salto_linea();
    fflush(stdin);
    /* ****** cargar nombre ****** */
    printf("Ingrese el nombre: ");
    fgets(persona.nombre, sizeof (persona.nombre), stdin);
    sscanf(persona.nombre, "%[^\n]", persona.nombre);
    for (i = 0; i < sizeof (persona.nombre); i++)
        persona.nombre[i] = toupper(persona.nombre[i]);
    fflush(stdin);
    /* ****** cargar apellido ****** */
    printf("Ingrese el apellido: ");
    fgets(persona.apellido, sizeof (persona.apellido), stdin);
    sscanf(persona.apellido, "%[^\n]", persona.apellido);
    for (i = 0; i < sizeof (persona.apellido); i++)
        persona.apellido[i] = toupper(persona.apellido[i]);

    return persona;
}

/* ****** convietre un numreo de unsigned a cadena char con sus puntos (123.456.789) ****** */
void unsigned_to_char(unsigned dni, char letra[CARACTERES_DNI]) {
    unsigned int cont, num, mod;
    int i, j;
    char numero[CARACTERES_DNI];
    memset(numero, '\0', CARACTERES_DNI);
    memset(letra, '\0', CARACTERES_DNI);
    num = dni;
    mod = dni;
    i = 0;
    cont = 0;
    while (num / 10 > 0) {
        mod = num % 10;
        num /= 10;
        letra[0] = '0' + mod;
        numero[cont++] = letra[0];
        if (++i == 3) {
            i = 0;
            numero[cont++] = '.';
        }
    }
    letra[0] = '0' + num;
    numero[cont] = letra[0];
    j = 0;
    for (i = cont; i >= 0; i--, j++)
        letra[j] = numero[i];
}

/* ****** guarda el registro en un archivo .bin ****** */
void guardar_registro(registro persona) {
    FILE* f;
    f = fopen(ARCHIVO, "ab");
    if (f)
        fwrite(&persona, sizeof (registro), 1, f);
    fclose(f);
}

/* ****** mostrar todo los registros ****** */
void mostrar_todos_los_registros(void) {
    registro aux = limpiar_registro();
    FILE* f;
    f = fopen(ARCHIVO, "rb");
    if (f) {
        puts("");
        printf("| %*s | %-*s | %-*s |\n", CARACTERES_DNI, "DNI", CARACTERES_NOMBRE, "Nombre", CARACTERES_APELLIDO, "Apellido");
        while (fread(&aux, sizeof (registro), 1, f))
            printf("| %*s | %-*s | %-*s |\n", CARACTERES_DNI, aux.dni, CARACTERES_NOMBRE, aux.nombre, CARACTERES_APELLIDO, aux.apellido);
        fclose(f);
    }
    puts("");
}

/* ****** mostrar un registro espesifico ****** */
void mostrar_un_registro(long int item) {
    registro persona = limpiar_registro();
    FILE* f;
    puts("");
    f = fopen(ARCHIVO, "rb");
    if (f) {
        fseek(f, item, SEEK_SET);
        printf("| %*s | %-*s | %-*s |\n", CARACTERES_DNI, "DNI", CARACTERES_NOMBRE, "Nombre", CARACTERES_APELLIDO, "Apellido");
        fread(&persona, sizeof (registro), 1, f);
        printf("| %*s | %-*s | %-*s |\n", CARACTERES_DNI, persona.dni, CARACTERES_NOMBRE, persona.nombre, CARACTERES_APELLIDO, persona.apellido);
    }
    puts("");
}

/* ****** mostrar la matriz de tipo registro(registro) ****** */
void mostrar_striuct_registro(void) {
    int i;
    printf("| %*s | %-*s | %-*s |\n", CARACTERES_DNI, "DNI", CARACTERES_NOMBRE, "Nombre", CARACTERES_APELLIDO, "Apellido");
    for (i = 0; i < LISTA_SIZE; i++)
        printf("| %*s | %-*s | %-*s |\n", CARACTERES_DNI, registro_arreglo[i].dni, CARACTERES_NOMBRE, registro_arreglo[i].nombre, CARACTERES_APELLIDO, registro_arreglo[i].apellido);
    puts("");
}

/* ****** crea tabal_primaria ****** */
void crear_tabla_primaria(void) {
    FILE* f;
    registro persona;
    int i;
    for (i = 0; i < LISTA_SIZE; i++)
        tabla_primaria_arreglo[i] = limpiar_tabla_primaria();

    f = fopen(ARCHIVO, "rb");
    if (f) {
        i = 0;
        tabla_primaria_arreglo[i].item = ftell(f);
        while (fread(&persona, sizeof (registro), 1, f)) {
            /* ****** crea la tabla_primaria ****** */
            sprintf(tabla_primaria_arreglo[i].clave_primaria, MASCARA_CLAVE_PRIMARIA, persona.apellido, persona.nombre, persona.dni);
            tabla_primaria_arreglo[++i].item = ftell(f);
        }
    }
    fclose(f);
}

/* ****** ordena la matriz de tipo tabla_primaria ****** */
void ordenar_tabla_primaria(void) {
    tabla_primaria aux = limpiar_tabla_primaria();
    int i, j;
    for (j = 1; j < LISTA_SIZE; j++) {
        for (i = (LISTA_SIZE - 1); i >= j; i--) {
            if (strcmp(tabla_primaria_arreglo[i].clave_primaria, tabla_primaria_arreglo[i - 1].clave_primaria) <= 0) {
                aux = tabla_primaria_arreglo[i];
                tabla_primaria_arreglo[i] = tabla_primaria_arreglo[i - 1];
                tabla_primaria_arreglo[i - 1] = aux;
            }
        }
    }
}

/* ****** mostrar la matriz de tipo tabla_primaria ****** */
void mostrar_struct_tabla_primaria(void) {
    int i;
    printf("| %-*s | %-8s |\n", CARACTERES_TABLA_PRIMARIA, "Clave primaria", "registro");
    for (i = 0; i < LISTA_SIZE; i++)
        printf("| %-*s | %8li |\n", CARACTERES_TABLA_PRIMARIA, tabla_primaria_arreglo[i].clave_primaria, tabla_primaria_arreglo[i].item);
    puts("");
}

/* ****** mostrar la tabla_primaria ****** */
void mostrar_tabla_primaria(void) {
    tabla_primaria aux = limpiar_tabla_primaria();
    FILE* f;
    f = fopen(TABLA_PRIMARIA, "rb");
    if (f) {
        printf("| %-*s | %-8s |\n", CARACTERES_TABLA_PRIMARIA, "Clave primaria", "registro");
        while (fread(&aux, sizeof (tabla_primaria), 1, f))
            printf("| %-*s | %8li |\n", CARACTERES_TABLA_PRIMARIA, aux.clave_primaria, aux.item);
        fclose(f);
    }
    puts("");
}

/* ****** guarda la tabla_primaria ****** */
void guardar_tabla_primaria(void) {
    tabla_primaria aux = limpiar_tabla_primaria();
    FILE* f;
    int i;
    f = fopen(TABLA_PRIMARIA, "wb");
    if (f) {
        for (i = 0; i < LISTA_SIZE; i++) {
            aux = tabla_primaria_arreglo[i];
            fwrite(&aux, sizeof (tabla_primaria), 1, f);
        }
        fclose(f);
    }
}

/* ****** lee el registro guardado (archivo.bin) y llena la matris devuelve la cantidad de registros cargados ****** */
int leer_regisrto(registro persona_vector[]) {
    FILE* f;
    registro persona = limpiar_registro();
    int i = 0;
    f = fopen(ARCHIVO, "rb");
    if (f) {
        while (fread(&persona, sizeof (registro), 1, f)) {
            strcpy(persona_vector[i].dni, persona.dni);
            strcpy(persona_vector[i].nombre, persona.nombre);
            strcpy(persona_vector[i++].apellido, persona.apellido);
        }
        fclose(f);
    }
    return i;
}

/* ****** mostrar la tabla_hash ****** */
void mostrar_tabla_hash(int size_hash) {
    FILE* f;
    int i = 1, digitos = 1;
    long int aux = limpiar_tabla_hash();
    while (size_hash / 10 > 0) {
        digitos++;
        size_hash /= 10;
    }
    f = fopen(TABLA_HASHING, "rb");
    if (f) {
        printf("| %*s | %*s |\n", digitos, "ID", (digitos < 4) ? 4 : digitos, "Dato");
        while (fread(&aux, sizeof (long int), 1, f))
            printf("| %*i | %*li |\n", digitos, i++, (digitos < 4) ? 4 : digitos, aux);
        fclose(f);
    }
    puts("");
}

/* ****** crea y guarda la tabla_hashing ****** */
int crear_tabla_hashing(void) {
    FILE* f;
    tabla_primaria tabla = limpiar_tabla_primaria();
    bool guardado;
    int i, id;

    /* ****** define el largo de la tabla_hashing ****** */
    double porcentaje = valida_numero_porcentaje();
    porcentaje /= 100;
    int size_hash = LISTA_SIZE;
    size_hash /= porcentaje;
    puts("");

    for (i = 0; i < size_hash; i++)
        tabla_hash_arreglo[i] = limpiar_tabla_hash();

    for (i = size_hash; i < LISTA_HASH_SIZE; i++)
        tabla_hash_arreglo[i] = marcar_tabla_hash();

    f = fopen(TABLA_PRIMARIA, "rb");
    if (f) {
        id = 0;
        while (fread(&tabla, sizeof (tabla_primaria), 1, f)) {
            /* ****** crea la tabla_primaria ****** */
            guardado = false;
            id = (sumar_caracteres(tabla.clave_primaria) % size_hash);
            while (guardado == false) {
                if (tabla_hash_arreglo[id] == 0) { 
                    tabla_hash_arreglo[id] = (long int) (tabla.item + 1);  /* comienso del registro "+ 1"
                                                                            * para que empiese de 1 y no de 0 en el indice de hash */
                    guardado = true;
                } else
                    id = ++id % size_hash;
            }
        }
    }
    fclose(f);
    return size_hash;
}

/* ****** mostrar la matriz de tipo tabla_hash ****** */
void mostrar_struct_tabla_hash(int size_hash) {
    int i, digitos = 1, cont_digitos = size_hash;
    while (cont_digitos / 10 > 0) {
        digitos++;
        cont_digitos /= 10;
    }
    printf("| %*s | %*s |\n", digitos, "ID", (digitos < 4) ? 4 : digitos, "Dato");
    for (i = 0; i < size_hash; i++)
        printf("| %*i | %*li |\n", digitos, i + 1, (digitos < 4) ? 4 : digitos, tabla_hash_arreglo[i]);
}

/* ****** guarda la tabla_hash ****** */
void guardar_tabla_hash(int size_hash) {
    FILE* f;
    long int aux = limpiar_tabla_hash();
    f = fopen(TABLA_HASHING, "wb");
    if (f) {
        int i;
        for (i = 0; i < size_hash; i++) {
            aux = tabla_hash_arreglo[i];
            fwrite(&aux, sizeof (long int), 1, f);
        }
        fclose(f);
    }
}

/* ****** buscala clave primaria en el archivo.bin ****** */
void acceder_archivo_tabla_primaria(registro persona) {
    FILE* f;
    tabla_primaria aux = limpiar_tabla_primaria();
    tabla_primaria buscar = limpiar_tabla_primaria();

    sprintf(buscar.clave_primaria, MASCARA_CLAVE_PRIMARIA, persona.apellido, persona.nombre, persona.dni);

    f = fopen(TABLA_PRIMARIA, "rb");
    if (f) {
        while (fread(&aux, sizeof (tabla_primaria), 1, f)) {
            if (strcmp(aux.clave_primaria, buscar.clave_primaria) == 0)
                buscar.item = aux.item;
        }
        fclose(f);
    }
    mostrar_un_registro(buscar.item);
}

void acceder_archivo_tabla_hash(registro persona, int size_hash) {
    FILE* f;
    tabla_primaria aux_indice_primario = limpiar_tabla_primaria();
    tabla_primaria aux_buscar = limpiar_tabla_primaria();
    long int aux_tabla_hashing = limpiar_tabla_hash();
    long int buscar = limpiar_tabla_hash();
    long int item;
    long int registro;
    bool encontrado = false;

    sprintf(aux_buscar.clave_primaria, MASCARA_CLAVE_PRIMARIA, persona.apellido, persona.nombre, persona.dni);

    buscar = (sumar_caracteres(aux_buscar.clave_primaria) % size_hash);

    do {

        f = fopen(TABLA_HASHING, "rb");
        if (f) {
            fseek(f, buscar * sizeof (long int), SEEK_SET);
            fread(&aux_tabla_hashing, sizeof (long int), 1, f);
            registro = aux_tabla_hashing;
            fclose(f);
        }

        f = fopen(TABLA_PRIMARIA, "rb");
        if (f) {
            fseek(f, registro - 1, SEEK_SET); /* "- 1" reato el uno que anteriormente sume
                                               * para que empiese de 1 y no de 0 en el indice de hash */
            fread(&aux_indice_primario, sizeof (tabla_primaria), 1, f);
            item = aux_indice_primario.item;
            fclose(f);
        }
        if (strcmp(aux_buscar.clave_primaria, aux_indice_primario.clave_primaria) == 0)
            encontrado = true;

        buscar = ++buscar % size_hash;

    } while (encontrado == false);

    mostrar_un_registro(item);
}

/* ****** mostrar la tabla_hash ****** */
int tamanio_tabla_hash(void) {
    long int aux = limpiar_tabla_hash();
    FILE* f;
    int i = 0;
    f = fopen(TABLA_HASHING, "rb");
    if (f) {
        while (fread(&aux, sizeof (long int), 1, f))
            i++;
        fclose(f);
    }
    return i;
}

/* ****** crear la estructura del registro(person) ****** */
void crear_archivo_struct(void) {
    puts("crear un archivo con estructura de campo y regitro.\n");
    int i;
    bool encontrado = false;
    int size_hash = leer_regisrto(registro_arreglo);
    if (size_hash > 0)
        printf("se cargaron %d Registros.\n", size_hash);
    for (i = size_hash; i < LISTA_SIZE; i++) {
        printf("Registro %d\n", i + 1);
        registro_arreglo[i] = cargar_registro();
        guardar_registro(registro_arreglo[i]);
        encontrado = true;
    }
    if (!encontrado)
        error("el registro esta lleno");
    mostrar_todos_los_registros();
}

void crear_archivo_indice_primario(void) {
    puts("crear un archivo con un indice primario.\n");
    crear_tabla_primaria();
    ordenar_tabla_primaria();
    guardar_tabla_primaria();
    mostrar_tabla_primaria();
}

void crear_archivo_indice_hashing(void) {
    puts("crear un tabla de hashing para acceso directo al archivo (utilizar saturacion prograsiva).\n");
    int size_hash = crear_tabla_hashing();
    guardar_tabla_hash(size_hash);
    mostrar_tabla_hash(size_hash);
}

void acceso_directo_indice_primario(void) {
    puts("acceso directo por tabla de indice primario.\n");
    mostrar_todos_los_registros();
    registro registro = cargar_registro();
    acceder_archivo_tabla_primaria(registro);
}

void acceso_directo_indice_hashing(void) {
    puts("acceso directo por tabla de indice hashing.\n");
    mostrar_todos_los_registros();
    int size_hash = tamanio_tabla_hash();
    registro registro = cargar_registro();
    acceder_archivo_tabla_hash(registro, size_hash);
}