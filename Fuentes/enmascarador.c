#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant) {
	int i;
	for (i=0; i<cant; i++) {
		if (mask[i] != 0) { 
			a[i] = b[i];
		}
	}
	return 0;
}

//extern 
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant) { }

int leer_rgb(char *archivo, unsigned char *buffer, int ancho, int alto) {
	return 0;
}

int escribir_rgb(char *archivo, unsigned char *buffer, int filas, int columnas) {
	return 0;
}

int main(int argc, char** argv) {
	if(argc != 5) {
		printf("Faltan par%cmetros.\n", 160);
		return 1;
	}
	int ancho;
	int alto;
	int cantidad;
	unsigned char *img1;
	unsigned char *img2;
	unsigned char *mascara;
	
	sscanf(argv[4], "%d", &ancho);
	sscanf(argv[5], "%d", &alto);
	cantidad = ancho * alto * 3;
	leer_rgb(argv[1], img1, ancho, alto);
	leer_rgb(argv[2], img2, ancho, alto);
	leer_rgb(argv[3], mascara, ancho, alto);
	
	//TODO: Imprimir el tamaño???
	
	//TODO: Iniciar cronómetro.
	enmascarar_c(img1, img2, mascara, cantidad);
	//TODO: Detener cronómetro y mostrar por pantalla. 
	escribir_rgb("salida_c.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_c.rgb con el contenido de img1.
	
	leer_rgb(argv[1], img1, ancho, alto);
	leer_rgb(argv[2], img2, ancho, alto);	//No estoy seguro si es necesario, hay que testear.
	
	//TODO: Iniciar cronómetro.
	enmascarar_asm(img1, img2, mascara, cantidad);
	//TODO: Detener cronómetro y mostrar por pantalla. 
	escribir_rgb("salida_asm.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_asm.rgb con el contenido de img1.
	
	return 0;
}
