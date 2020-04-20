; Initialize Stack Size
; Equ 400 hex (1024) bytes
Stack_Size      EQU     0x00000400
; Area STACK (NOINIT and READ/WRITE)
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
; Initialize memory equals Stack_Size
Stack_Mem       SPACE   Stack_Size
__initial_sp
; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  Reset_Handler             [WEAK]
__Vectors
                DCD     __initial_sp           ; Top of Stack
                DCD     Reset_Handler          ; Reset Handler
__Vectors_End
                AREA    |.text| , CODE, READONLY

Reset_Handler   PROC
                B __main
                ENDP
					
;DEFINES OF CONSTANTS				
X_	EQU 0x20
Y_	EQU 0x05
Z_	EQU 0x04
	
CONST_FOR_XOR EQU 0xff

__main      	PROC							
				; place you initialization code here
				
;##################################################################
;ARITHMETICAL	###################################################
;##################################################################
				
				;load a start values from code memory
				mov r0, #X_	;r0 -> X
				mov r1, #Y_	;r1 -> Y
				mov r2, #Z_	;r2 -> Z
				
				
	;ACTIONS WITHOUT SIGN
				add r3, r0, r1	;r3 = r0 + r1 = X + Y
				sub r4, r1, r2	;r4 = r1 - r2 = Y - Z
				sub r5, r0, r1	;r5 = r0 - r1 = X - Y
				
				add r3, r4	;r3 = r3 + r4 = (X + Y) + (Y - Z)
				
				;ready result
				sub r3, r5	;r3 = r3 - r5 = (X + Y) + (Y - Z) - (X - Y)
				
				;store the result to data memory
				ldr r4, =Q_A
				str r3, [r4]
				
				nop	;only because it's convenient breakpoint
				
	;ACTIONS WITH SIGN
				adds r3, r0, r1	;r3 = r0 + r1 = X + Y
				subs r4, r1, r2	;r4 = r1 - r2 = Y - Z
				subs r5, r0, r1	;r5 = r0 - r1 = X - Y
				
				nop	;only because it's convenient breakpoint				
				
				adds r3, r4	;r3 = r3 + r4 = (X + Y) + (Y - Z)
				
				;ready result
				subs r3, r5	;r3 = r3 - r5 = (X + Y) + (Y - Z) - (X - Y)
				
				;store the result to data memory
				ldr r4, =Q_AS
				str r3, [r4]
				
				nop	;only because it's convenient breakpoint

;##################################################################
;LOGICAL	###################################################
;##################################################################

				;load a start values from code memory
				ldr r4, =A_
				ldr r0, [r4]	;r0 -> A
				ldr r4, =B_
				ldr r1, [r4]	;r1 -> B
				ldr r4, =C_
				ldr r2, [r4]	;r2 -> C
				ldr r4, =D_
				ldr r3, [r4]	;r3 -> D
				
	;ACTIONS WITHOUT SIGN
				eor r4, r0, #CONST_FOR_XOR	;r4 = r0 XOR 0xf = !r0 = !A
				eor r5, r2, #CONST_FOR_XOR	;r5 = r2 XOR 0xf = !r2 = !C

				and r6, r4, r5	;r6 = r4 AND r5 = !A AND !C
				and r6, r1	;r6 = r6 AND r1 = !A AND !C AND B
				
				eor r7, r1, #CONST_FOR_XOR	;r7 = r1 XOR 0xf = !r1 = !B
				
				and r8, r7, r2	;r8 = r7 AND r2 = !B AND C
				and r8, r3	;r8 = r8 AND r3 = !B AND C AND D
				
				and r9, r0, r2	;r9 = r0 AND r2 = A AND C
				
				orr r8, r9	;r8 = r8 OR r9 = (!B AND C AND D) OR (A AND C)
				
				;ready result
				orr r6, r8 ;r6 = r6 OR r8 = (!A AND !C AND B) OR ((!B AND C AND D) OR (A AND C))
				
				;store the result to data memory
				ldr r4, =Q_L
				str r6, [r4]
				
				nop	;only because it's convenient breakpoint
				
				
	;ACTIONS WITH SIGN
				eors r4, r0, #CONST_FOR_XOR	;r4 = r0 XOR 0xf = !r0 = !A
				eors r5, r2, #CONST_FOR_XOR	;r5 = r2 XOR 0xf = !r2 = !C

				ands r6, r4, r5	;r6 = r4 AND r5 = !A AND !C
				ands r6, r1	;r6 = r6 AND r1 = !A AND !C AND B
				
				eors r7, r1, #CONST_FOR_XOR	;r7 = r1 XOR 0xf = !r1 = !B
				
				ands r8, r7, r2	;r8 = r7 AND r2 = !B AND C
				ands r8, r3	;r8 = r8 AND r3 = !B AND C AND D
				
				ands r9, r0, r2	;r9 = r0 AND r2 = A AND C
				
				orrs r8, r9	;r8 = r8 OR r9 = (!B AND C AND D) OR (A AND C)
				
				;ready result
				orrs r6, r8 ;r6 = r6 OR r8 = (!A AND !C AND B) OR ((!B AND C AND D) OR (A AND C))
				
				;store the result to data memory
				ldr r4, =Q_LS
				str r6, [r4]
				
				nop	;only because it's convenient breakpoint
							
__mainloop            
				; place you application code here	

		B __mainloop
		ENDP

;Area of Readonly data
		AREA |MY_CONST|, DATA, READONLY
		ALIGN 4		
			
A_		DCD 0x50
B_		DCD 0x01
C_		DCD 0x33
D_		DCD 0xe2

;Area of RW data
		AREA |MY_DATA|, DATA, READWRITE 
		ALIGN 4	
			
Q_A		DCD 0	;for saving result of arithmetic operations without sign
Q_AS	DCD 0	;for saving result of arithmetic operations with sign
Q_L		DCD 0	;for saving result of logic operations without sign
Q_LS	DCD 0	;for saving result of logic operations with sign
		
		END
		