#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, long cant) {
	//printf("cant es %i\n", cant);
	unsigned char *tmp = (unsigned char *)malloc(cant);
	int i=0;
	for (i; i<cant; i++) {
		//printf("mask[i] contiene %i\n", mask[i]);
		//printf("a[i] contiene %i\n", a[i]);
		//printf("b[i] contiene %i\n", b[i]);
		if (mask[i] != 0) { 
			tmp[i] = b[i];
		} else { 
			tmp[i] = a[i];
		}  
		printf("i es %i\n", i);
		//printf("ahora tmp[i] contiene %i\n", tmp[i]);
	}
	a = tmp;
	return 0;
}

//extern 
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant) { }


int leer_rgb(char *archivo, unsigned char *buffer, int ancho, int alto) {
	//printf("Procesando arhivo es %s\n", archivo);
	FILE *archivoRead;
	long tamanio = ancho*alto*3;
	archivoRead = fopen(archivo, "rb");
	buffer = (unsigned char *)malloc(tamanio);
	//fseek(archivoRead, 0, SEEK_SET);
	int tamanioArchivo = fread(buffer, 1, tamanio, archivoRead);
	printf("Tamanio es %i\n", tamanio);
	printf("El archivo leido tiene %i\n", tamanioArchivo);
	fclose(archivoRead);
	
	
	return 0;
}

int escribir_rgb(char *archivo, unsigned char *buffer, int filas, int columnas) {
	FILE *archivoWrite;
	long tamanio = filas*columnas*3;
	archivoWrite = fopen(archivo, "wb");
	//fseek(archivoWrite, 0, SEEK_SET);
	buffer = (unsigned char *)malloc(tamanio);
	int tamanioArchivo = fwrite(buffer, 1, tamanio, archivoWrite);
	printf("El archivo escrito tiene %i\n", tamanioArchivo);
	fclose(archivoWrite);
	return 0;
}

int main(int argc, char** argv) {
	//printf("Hay %i par%cmetros.\n", argc, 160);
//	if(argc < 6) {
//		printf("Faltan par%cmetros.\n", 160);
//		return 1;
//	}
	int ancho;
	int alto;
	long cantidad;
	unsigned char *img1;
	unsigned char *img2;
	unsigned char *mascara;
	
	//TEST
	ancho = 100;
	alto = 56;
	cantidad = ancho * alto * 3;
	leer_rgb("img1.rgb", img1, ancho, alto);
//	leer_rgb("img2.rgb", img2, ancho, alto);
	//leer_rgb("mask.rgb", mascara, ancho, alto);
//escribir_rgb("salida_c.rgb", img2, ancho, alto);
//escribir_rgb("salida_c.rgb", img2, ancho, alto);
	escribir_rgb("salida_c.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_c.rgb con el contenido de img1.
	// sscanf(argv[4], "%d", &ancho);
	// sscanf(argv[5], "%d", &alto);
	// cantidad = ancho * alto * 3;
	// leer_rgb(argv[1], img1, ancho, alto);
	// leer_rgb(argv[2], img2, ancho, alto);
	// leer_rgb(argv[3], mascara, ancho, alto);
	
	//TODO: Imprimir el tamaño???
	
	//TODO: Iniciar cronómetro.
	//printf("Enmascarando con C");
	//enmascarar_c(img1, img2, mascara, cantidad);
	//printf("Fin del enmascarado");
	//TODO: Detener cronómetro y mostrar por pantalla. 
	//printf("Escribiendo archivo");
	//escribir_rgb("salida_c.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_c.rgb con el contenido de img1.
	//printf("Archivo escrito");
	//leer_rgb(argv[1], img1, ancho, alto);
	//leer_rgb(argv[2], img2, ancho, alto);	//No estoy seguro si es necesario, hay que testear.
	
	//TODO: Iniciar cronómetro. Ver si tiene mas de 16 bytes
	//enmascarar_asm(img1, img2, mascara, cantidad);
	//TODO: Detener cronómetro y mostrar por pantalla. 
	//escribir_rgb("salida_asm.rgb", img1, ancho, alto);	//img1 se encuentra pisado escribir archivo salida_asm.rgb con el contenido de img1.
	
	return 0;
}
