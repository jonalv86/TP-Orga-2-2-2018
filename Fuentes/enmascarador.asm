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
    MOV         EAX,    [EBP+8]    ;Desde C siempre tiene que venir múltiplo de 4? Consultar con Carlos.
    MOV         EBX,    [EBP+12]
    MOV         EDX,    [EBP+16]
    XOR         ECX,    ECX
    MOV         ECX,    [EBP+20]    
CICLOENMASCARAR:
;Hay que controlar si vino vacío o si tamaño es menor a 4?
    CMP         ECX,     0
    JE          FINALIZARCICLO
    CMP         ECX,     15
    JBE         ACOMODAR

    MOVAPS      XMM0,   [EAX]
    MOVAPS      XMM1,   [EBX]
    MOVAPS      XMM2,   [EDX]
    ;LOGICA
    PAND        XMM1,   XMM2       
    PANDN       XMM2,   XMM2
    PAND        XMM0,   XMM2    
    PADDB       XMM0,   XMM1
    
    MOVAPS      [EAX],  XMM0
    
    ADD         EAX,    16
    ADD         EBX,    16
    ADD         EDX,    16
    SUB         ECX,    16
    
    JMP         CICLOENMASCARAR
    
ACOMODAR:
    ;mejorar
    PUSH        EAX
    MOV         EAX,    16
    SUB         EAX,    ECX
    MOV         ECX,    EAX
    POP         EAX
    SUB         EAX,    ECX
    SUB         EBX,    ECX
    SUB         EDX,    ECX
    MOV         ECX,    16
    JMP         CICLOENMASCARAR

    ;CMP         EDX,    0
    ;JNE         CICLOENMASCARAR
FINALIZARCICLO:            
    POP         EBP
    RET