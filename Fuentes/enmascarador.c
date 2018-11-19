#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, long cant) {
	int i=0;
	for (i; i<cant; i++) {
		if (mask[i] != 0) { 
			a[i] = b[i];
		}
	}
	return 0;
}

//extern 
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant) { }


int leer_rgb(char *archivo, unsigned char *buffer, int ancho, int alto) {
	FILE *archivoRead = NULL;
	archivoRead = fopen(archivo, "rb");
	fread(buffer, 1, ancho*alto*3, archivoRead);
	fclose(archivoRead);
	return 0;
}

int escribir_rgb(char *archivo, unsigned char *buffer, int filas, int columnas) {
	FILE *archivoWrite = NULL;
	archivoWrite = fopen(archivo, "wb");
	fwrite(buffer, 1, filas*columnas*3, archivoWrite);
	fclose(archivoWrite);
	return 0;
}


int main(int argc, char *argv[]) {
	if(argc < 6) {
		printf("Faltan par%cmetros.\n", 160);
		return 1;
	}
	int ancho;
	int alto;
	long cantidad;
	unsigned char *img1 = NULL;
	unsigned char *img2 = NULL;
	unsigned char *mascara = NULL;
	
	sscanf(argv[4], "%d", &ancho);
	sscanf(argv[5], "%d", &alto);
	cantidad = ancho * alto * 3;
	
	img1 = malloc(cantidad);
	img2 = malloc(cantidad);
	mascara = malloc(cantidad);
			
	leer_rgb(argv[1], img1, ancho, alto);
	leer_rgb(argv[2], img2, ancho, alto);
	leer_rgb(argv[3], mascara, ancho, alto);
	
	clock_t inicio = clock();
	enmascarar_c(img1, img2, mascara, cantidad);
	clock_t fin = clock();
	double tiempoTotal = (double)(fin - inicio) / CLOCKS_PER_SEC;
	printf ("enmascarar_c demora %f segundos en una imagen de %i x %i\n", tiempoTotal, ancho, alto);
	escribir_rgb("salida_c.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_c.rgb con el contenido de img1.
	
	leer_rgb(argv[1], img1, ancho, alto);
	//leer_rgb(argv[2], img2, ancho, alto);	//No estoy seguro si es necesario, hay que testear.
	//TODO: Iniciar cronómetro. Ver si tiene mas de 16 bytes
	inicio = clock();
	enmascarar_asm(img1, img2, mascara, cantidad);
	fin = clock();
	tiempoTotal = (double)(fin - inicio) / CLOCKS_PER_SEC;
	printf ("enmascarar_asm demora %f segundos en una imagen de %i x %i\n", tiempoTotal, ancho, alto);
	escribir_rgb("salida_asm.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_asm.rgb con el contenido de img1.
	
	free(img1);
	free(img2);
	free(mascara);
	
	return 0;
}
