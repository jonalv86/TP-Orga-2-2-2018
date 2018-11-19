;Enter para testear=>%include "io.inc"
section .data

;Inicio Testing=>
;img1: db 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
;img2: db 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
;mask: db 0, 255, 255, 255, 0, 0, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 0, 0, 255 
;cantidad: dd 26
;<= Fin Testing

global _enmascarar_asm

section .text
;Inicio Testing=>
;global CMAIN
;CMAIN:
;    mov ebp, esp; for correct debugging
;    mov eax, img1
;    mov ebx, img2
;    mov ecx, mask
;    ;xor edx, edx
;    mov edx, [cantidad]
;    push edx
;    push ecx
;    push ebx
;    push eax
;    call _enmascarar_asm
;    add esp, 16
;    xor eax, eax
;    ret
;<= Fin testing
;Inicio de la función.
_enmascarar_asm:
    PUSH        EBP
    MOV	        EBP,    ESP
    MOV         EAX,    [EBP+8]     ;[EBP+8] Puntero a img1
    MOV         EBX,    [EBP+12]    ;[EBP+12] Puntero a img2
    MOV         EDX,    [EBP+16]    ;[EBP+16] Puntero a la mascara
    XOR         ECX,    ECX
    MOV         ECX,    [EBP+20]    ;[EBP+20] Cantidad de bytes

CICLOENMASCARAR:
    CMP         ECX,     0
    JE          FINALIZARCICLO
    CMP         ECX,     15
    JBE         ACOMODAR
    MOVUPS      XMM0,   [EAX]
    MOVUPS      XMM1,   [EBX]
    MOVUPS      XMM2,   [EDX]
    ;LOGICA
    PAND        XMM1,   XMM2       
    ;PANDN       XMM2,   XMM2   Esperaba que lo de vuelta. Tampoco hay una instruccion para negar la mascara. 
    ;PAND        XMM0,   XMM2    
    POR         XMM0,   XMM2
    PXOR        XMM0,   XMM2
    PADDB       XMM0,   XMM1
    MOVUPS      [EAX],  XMM0
    ADD         EAX,    16
    ADD         EBX,    16
    ADD         EDX,    16
    SUB         ECX,    16
    JMP         CICLOENMASCARAR
    
ACOMODAR:
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

FINALIZARCICLO:
    XOR         EAX,    EAX
    POP         EBP
    RET