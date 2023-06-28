#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nroEstudiantes 20
#define tamanioNombre 30

//Prototipado
int cargarEstudiante(int [], char [nroEstudiantes][tamanioNombre], int []);
void mostrarArregloParalelo(int [], char nombres[nroEstudiantes][tamanioNombre], int [], int );
int buscarLegajo(int [], int , int );
int generarEstudiantes(int [], char [nroEstudiantes][tamanioNombre], int [], int );
void generarNombre(char [nroEstudiantes][tamanioNombre], int );
void ordenarEstudiantes(int [], char [nroEstudiantes][tamanioNombre], int [], int );
void intercambiarArreglosParalelos(int [], char [nroEstudiantes][tamanioNombre], int [], int );

//MAIN
int main()
{
    printf("\nTrabajo Práctico Nro 5: Arreglos Paralelos");
    printf("\n\nSean los arreglos paralelos que simbolizan la entidad de software 'alumno':");
    printf("\n|    int legajos[20];");
    printf("\n|    char nombres[20][30];");
    printf("\n|    int anios[20];");
    printf("\n\n1. Crear una funcion que los cargue, hasta que el usuario lo decida.");
    printf("\n\n2. Crear una funcion que busque dentro del arreglo de legajos y retorne la posicion de un determinado valor.");
    printf("\n\n3. Hacer una funcion que reciba como parametro todos los arreglos y encuentre el nombre correspondiente a un");
    printf("\ndeterminado legajo y lo imprima por pantalla. Se debe invocar la funcion 2.");
    printf("\n\n4. Hacer una funcion que reciba como parametro todos los arreglos y los ordene por nombre. (por el metodo de seleccion o insercion).");
    printf("\n\n5. Mostrar por pantalla los 3 arreglos pero de a un “registro” o alumno por vez (es decir: muestra el legajo, nombre y anios del 1er");
    printf("\nalumno, luego el legajo, nombre y anios del 2do alumno, y asi sucesivamente).. \n");

    int legajos[nroEstudiantes];
    char nombres[nroEstudiantes][tamanioNombre];
    int anios[nroEstudiantes];
    int validos, legajoBuscado, legajoIndex, validosAGenerar;
    srand(time(NULL));

    //Generacion de validos, ejercicio 1
    //validos = cargarEstudiante(legajos, nombres, anios); //deprecated (?
    validosAGenerar = 8; //genera 8 estudiantes
    validos = generarEstudiantes(legajos, nombres, anios, validosAGenerar);
    mostrarArregloParalelo(legajos, nombres, anios, validos);

    //buscarLegajo, ejercicio 2
    printf("\n\nIngrese el numero de legajo que desea buscar: ");
    fflush(stdin);
    scanf("%i", &legajoBuscado);
    legajoIndex = buscarLegajo(legajos, validos, legajoBuscado);
    if( legajoIndex == -1 )
    {
        printf("\nEl legajo no se encuentra dentro de la base de datos.");
    }
    else
    {
        printf("\nEl legajo se encuentra en el index: %i", legajoIndex);
    }

    //buscarNombreLegajo
    printf("\nEl nombre del estudiante legajo nro '%i' es: %s", legajos[legajoIndex], nombres[legajoIndex]);

    //Ordenar por Nombre los arreglos paralelos
    ordenarEstudiantes(legajos, nombres, anios, validos);
    mostrarArregloParalelo(legajos, nombres, anios, validos);

    printf("\n\nSaliendo del programa... \n");
}

int cargarEstudiante(int legajos[], char nombres[nroEstudiantes][tamanioNombre], int anios[])
{
    int i = 0;
    char continuar;
    do
    {
        printf("\nIngrese el nro de legajo del estudiante: ");
        fflush(stdin);
        scanf("%i", &legajos[i]);

        printf("\nIngrese el nombre del estudiante: ");
        fflush(stdin);
        gets(nombres[i]);

        printf("\nIngrese la edad del estudiante: ");
        fflush(stdin);
        scanf("%i", &anios[i]);

        printf("\n\nIngreso de datos del alumno finalizado. Desea Ingresar otro alumno? ('s' para ingresar un nuevo alumno)");
        fflush(stdin);
        scanf("%c", &continuar);

        i++;
    }
    while( continuar == 's' && i < nroEstudiantes );
    return i;
}

void mostrarArregloParalelo(int legajos[], char nombres[nroEstudiantes][tamanioNombre], int anios[], int validos)
{
    int i = 0;

    while( i < validos)
    {
        printf("\n\nEstudiante Index: %i", i);
        printf("\nLegajo: %4i", legajos[i]);
        printf("\nNombre: %s", nombres[i]);
        printf("\nAnios: %i", anios[i]);
        i++;
    }
}

int buscarLegajo(int legajos[], int validos, int legajoBuscado)
{
    int i = 0;
    while( i < validos )
    {
        if( legajos[i] == legajoBuscado ) return i;
        i++;
    }
    return -1;
}

int generarEstudiantes(int legajos[], char nombres[nroEstudiantes][tamanioNombre], int anios[], int validosAGenerar)
{
    int i = 0, j = 0;

    while( i < validosAGenerar)
    {
        legajos[i] = rand()%9999+1;
        generarNombre(nombres, i);
        anios[i] = rand()%40+18;
        i++;
    }
    return i;
}

void generarNombre( char nombres[nroEstudiantes][tamanioNombre], int i)
{
    int j = 0;

    while( j < 15 ) //15 tomado arbitrariamente
    {
        nombres[i][j] = rand()%25+97; //de la a a la z minusculas
        j++;
    }
    nombres[i][j] = '\0';
}

void ordenarEstudiantes(int legajos[], char nombres[nroEstudiantes][tamanioNombre], int anios[], int validos)
{
    int i = 1, j;

    while( i < validos )
    {
        j = i;
        while( j > 0 && strcmpi(nombres[j], nombres[j-1]) < 0 )
        {
            intercambiarArreglosParalelos(legajos, nombres, anios, j);
            j--;
        }
        i++;
    }
}

void intercambiarArreglosParalelos(int legajos[], char nombres[nroEstudiantes][tamanioNombre], int anios[], int indexPosterior)
{
    int i = indexPosterior;
    int legajosAux;
    char nombresAux[tamanioNombre];
    int aniosAux;

    legajosAux = legajos[i-1];
    legajos[i-1] = legajos[i];
    legajos[i] = legajosAux;

    strcpy(nombresAux, nombres[i-1]);
    strcpy(nombres[i-1], nombres[i]);
    strcpy(nombres[i], nombresAux);

    aniosAux = anios[i-1];
    anios[i-1] = anios[i];
    anios[i] = aniosAux;
}

