#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RGB 3
#define lectura "rb"
#define escritura "wb"
#define ERROR 1
#define OK 0

int enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, long cant) {
	int i=0;
	for (i; i<cant; i++) {
		if (mask[i] != 0) { 
			a[i] = b[i];
		}
	}
	return OK;
}

extern int enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);

int leer_rgb(char *archivo, unsigned char *buffer, long tamanio) {
	FILE *archivoRead = fopen(archivo, lectura);
	long tamanioArchivo = fread(buffer, sizeof(unsigned char), tamanio, archivoRead);
	fclose(archivoRead);
	return tamanioArchivo == tamanio ? OK : ERROR;
}

int escribir_rgb(const char *archivo, unsigned char *buffer, long tamanio) {
	FILE *archivoWrite = archivoWrite = fopen(archivo, escritura);
	long tamanioArchivo = fwrite(buffer, sizeof(unsigned char), tamanio, archivoWrite);
	fclose(archivoWrite);
	return tamanioArchivo == tamanio ? OK : ERROR;
}

int main(int argc, char *argv[]) {
	const int parametrosEsperados = 6;
	const int aCuote = 160;
	const int minAsm = 16;
	const char *strFaltanParametros = "\nFaltan par%cmetros.\n";
	const char *strTamanio = "%i x %i";
	const char *strErrorDeLectura = "\nError en la lectura.\n";
	const char *strErrorDeEscritura = "\nError en la escritura.\n";
	const char *strErrorEnmascararC = "\nError al enmascarar en C.\n";
	const char *strErrorEnmascararAsm = "\nError al enmascarar en Assembler.\n";
	const char *strTamanioMinimo = ". El vector tiene menos de 16 bytes. No se puede operar optimamente en Assembler.\n";
	const char *strTiempoTotal = ", %f segundos";
	const char *nombreArchivoSalidaC = "salida_c.rgb";
	const char *nombreArchivoSalidaAsm = "salida_asm.rgb";
	
	if(argc < parametrosEsperados) {
		printf(strFaltanParametros, aCuote);
		return ERROR;
	}
	
	int ancho;
	int alto;
	sscanf(argv[4], "%d", &ancho);
	sscanf(argv[5], "%d", &alto);
	printf(strTamanio, ancho, alto);
	long cantidad = ancho * alto * RGB;
	
	int resultadoEjecucion = OK;	
	unsigned char *img1 = malloc(cantidad);
	unsigned char *img2 = malloc(cantidad);
	unsigned char *mascara = malloc(cantidad);
			
	if (leer_rgb(argv[1], img1, cantidad) != OK ||
		leer_rgb(argv[2], img2, cantidad) != OK ||
		leer_rgb(argv[3], mascara, cantidad) != OK) {
		printf(strErrorDeLectura);
		resultadoEjecucion = ERROR;
		goto FINALIZAR;
	}
	
	clock_t inicio = clock();
	if (enmascarar_c(img1, img2, mascara, cantidad) != OK) {
		printf(strErrorEnmascararC);
		resultadoEjecucion = ERROR;
		goto FINALIZAR;
	}
	printf (strTiempoTotal, (double)(clock() - inicio) / CLOCKS_PER_SEC);

	if (escribir_rgb(nombreArchivoSalidaC, img1, cantidad) != OK) {
		printf(strErrorDeEscritura);
		resultadoEjecucion = ERROR;
		goto FINALIZAR;
	}
	if (leer_rgb(argv[1], img1, cantidad) != OK) {
		printf(strErrorDeLectura);
		resultadoEjecucion = ERROR;
		goto FINALIZAR;
	}
	
	if (cantidad < minAsm) {
		printf(strTamanioMinimo);
		goto FINALIZAR;
	} 
	inicio = clock();
	if (enmascarar_asm(img1, img2, mascara, cantidad) != OK) {
		printf(strErrorEnmascararAsm);
		resultadoEjecucion = ERROR;
		goto FINALIZAR;
	}
	printf (strTiempoTotal, (double)(clock() - inicio) / CLOCKS_PER_SEC);
	
	if (escribir_rgb(nombreArchivoSalidaAsm, img1, cantidad) != OK) {
		printf(strErrorDeEscritura);
		resultadoEjecucion = ERROR;
		goto FINALIZAR;
	}

	FINALIZAR:
	free(img1);
	free(img2);
	free(mascara);
	return resultadoEjecucion;
}
