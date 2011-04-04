#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

//#define PRIMERO 1
#define SEGUNDO 2

double lista1[10];
double lista2[10];

void presentacion(void);
void descripcion(void);
void leerArchivo(void);
double media(double lista1[]);
double media2(double lista[]);
double sigma(double lista1[]);
double sigma1(double lista1[], double lista2[]);
double sigma2(double lista[]);
double beta1(double lista1[], double lista2[]);
double beta0(double lista1[], double lista2[]);
double rel(double lista1[], double lista2[]);
double rel2(double lista1[], double lista2[]);
void imprimirArchivo(void);

//Caracteres ASCII extendidos para el español.
const char et = 130; //E con tilde.
const char Et = 130; //E mayúscula con tilde.
const char at = 160; //A con tilde.
const char it = 161; //I con tilde.
const char ot = 162; //O con tilde.
const char ut = 163; //U con tilde.
const char nn = 164; //La eñe.
const char Nn = 165; //La eñe mayúscula.
const char Ut = 233; //U mayúscula con tilde.

int main(void) {
    presentacion();
    descripcion();
    leerArchivo();
    imprimirArchivo();
    system("pause");
    return 0;
}

void presentacion(void)
{
    cout << "Programa 3 - PSP1, LP II - Ingenier" << it << "a de Software\n"
           "Juan Carlos Moreno, c" << ot << "digo 0807536\n"
           "Camilo Alberto Aguirre, c" << ot << "digo 0906502\n"
           "Universidad Nacional de Colombia, 31 de marzo de 2011.\n"
           "-----------------------------------------------------------------"
           "---------------";
}

void descripcion(void)
{
    cout << "DESCRIPCION: ";
    cout << "Este programa calcula los par" << at << "metros de regresi"<< ot
         << "n lineal beta_0 y beta_1, y los coeficientes de correlaci" << ot
         << "n r y r^2  para un conjunto de n pares de datos. Los n pares de "
            "datos de entrada se almacenan en el fichero de texto 'datos.txt'"
            "y los datos de salida en el fichero de texto 'datos2.txt',"
            "que se crea tan pronto se ejecuta el programa. Ambos ficheros es"
            "t" << at << "n en la misma carpeta que el ejecutable.\n"
            "----------------------------------------------------------------"
            "----------------";
}

void leerArchivo(void) {
    char info[5];

    ifstream read;
    read.open("datos.txt",ios::in);

    if(!read)
        cout << "No se puede leer el archivo.\n";

    else
    {
            for (int n = 0; read >> info, n < 10; n++)
    {
        lista1[n] = atof(strtok(info,","));
		lista2[n] = atof(strtok(NULL,","));
    }

    read.close();
    cout << "Fichero de datos de entrada le" << it << "do con "
         << et << "xito.\n";
    }

}

double sigma(double lista1[]) {
	int i;
	double suma = 0;
	for (i = 0; i < 10; i++)
		suma += lista1[i];

	return suma;
}

double sigma1(double lista1[], double lista2[]) {
	int i;
	double suma = 0;
	for (i = 0; i < 10; i++)
		suma += lista1[i]*lista2[i];

	return suma;
}

double sigma2(double lista[]) {
	int i;
	double suma = 0;
	for (i = 0; i < 10; i++)
		suma += pow(lista[i], 2);

	return suma;
}

double media(double lista1[]) {
	return sigma(lista1)/10;
}

double media2(double lista1[]) {
	return sigma2(lista1)/10;
}

#if defined PRIMERO

double beta1(double lista1[], double lista2[]) {
	double beta1;
	beta1 = (sigma1(lista1, lista2) - (10 * media(lista1) * media(lista2))) /
			(sigma2(lista1) - (10 * pow(media(lista1), 2)));
	return beta1;
}

#elif defined SEGUNDO

double beta1(double lista1[], double lista2[]) {
	double beta1;
	beta1 = (sigma(lista1)*sigma(lista2) - (10 * sigma1(lista1, lista2)))/
			(pow(sigma(lista1), 2) - (10 * sigma2(lista1)));
	return beta1;
}

#endif

double beta0(double lista1[], double lista2[]) {
	double beta0;
	beta0 = media(lista2) - beta1(lista1, lista2) * media(lista1);
	return beta0;
}

double rel(double lista1[], double lista2[]) {
    double rel;
    rel = (10*sigma1(lista1, lista2) - sigma(lista1)*sigma(lista2))/
          sqrt((10*sigma2(lista1) - pow(sigma(lista1), 2))*
               (10*sigma2(lista2) - pow(sigma(lista2), 2)));
    return rel;
}

double rel2(double lista1[], double lista2[]) {
    double r = rel(lista1, lista2), rel2;
    rel2 = pow(r, 2);
    return rel2;
}

void imprimirArchivo(void) {
	ofstream out("datos2.txt");
	if(!out) {
		cout << "No se puede abrir el archivo.\n";
	}
	else
	{
        out << "beta_0: " << beta0(lista1, lista2) << "\n"
            << "beta_1: " << beta1(lista1, lista2) << "\n"
            << "r: " << rel(lista1, lista2) << "\n"
            << "r^2: " << rel2(lista1, lista2) << "\n";
        out.close();
        cout << "Fichero de datos de salida impreso con " << et << "xito.\n";
	}
}
