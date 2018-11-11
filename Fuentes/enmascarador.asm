;Enter para testear=>%include "io.inc"
section .data

global _enmascarar_asm

section .text
;Enter para testear=>global CMAIN
;Enter para testear=>CMAIN:
;Enter para testear=>    mov ebp, esp; for correct debugging
    ;write your code here
;Enter para testear=>    xor eax, eax
;Enter para testear=>    ret

;Inicio de la función.
_enmascarar_asm:
    PUSH        EBP
    MOV	        EBP,    ESP
;[EBP+8]    Puntero a img1
;[EBP+12]   Puntero a img2
;[EBP+16]   Puntero a la mascara
;[EBP+20]   cantidad de bytes
    MOV         EAX,    [EBP+8]    ;Desde C siempre tiene que venir múltiplo de 4? COnsultar con Carlos.
    MOV         EBX,    [EBP+12]
    MOV         ECX,    [EBP+16]
    XOR         EDX,    EDX
    MOV         EDX,    [EBP+20]    
CICLOENMASCARAR:
;Hay que controlar si vino vacío o si tamaño es menor a 4?
    MOVUPS      XMM0,   [EAX]
    MOVUPS      XMM1,   [EBX]
    MOVUPS      XMM2,   [ECX]
    ;LOGICA
    ADD         EAX,    4
    ADD         EBX,    4
    ADD         ECX,    4
    SUB         EDX,    4
    CMP         EDX,    0
    JNE         CICLOENMASCARAR
;Fin de la función.            
    POP         EBP
    RET