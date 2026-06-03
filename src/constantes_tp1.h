#ifndef __CONSTANTES_TP1_H__
#define __CONSTANTES_TP1_H__

#define FORMATO_LECTURA "%[^,],%[^,],%i,%i,%i%*[^\n]\n"
#define FORMATO_ESCRITURA "%s,%s,%i,%i,%i\n"
#define CHAR_DIVISOR_CAMPOS ','
#define INDICADOR_NUEVA_LINEA '\n'

#define MAX_TIPOS 8
#define MAX_NOM_TIPO 5

#define CANT_DESEADA_LECTURA 5
#define TAM_INICIAL_BUFFER 1
#define AJUSTE_TAM_BUFFER 2

#define SIN_ERRORES 0
#define ERR_MEMORIA 1
#define LINEA_VACIA 2
#define LINEA_INVALIDA 3

#endif // __CONSTANTES_TP1_H__