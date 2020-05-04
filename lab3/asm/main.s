; Initialize Stack Size
; Equ 400 hex (1024) bytes
Stack_Size     		 	EQU     0x00000400

RCC_AHB1_BASE			EQU		0x40023800
GPIOA_BASE				EQU		0x40020000
GPIOC_BASE				EQU		0x40020800


RCC_AHB1ENR_OFFSET		EQU		0x30
GPIOA_MODER_OFFSET		EQU		0x00
GPIOA_BSRR_OFFSET		EQU		0x18
GPIOC_PUPDR_OFFSET		EQU		0x0C
GPIOC_IDR_OFFSET		EQU 	0x10

	
FIRST_LED				EQU		4
BUTTON					EQU		13
	
	
DELAY					EQU		1500000


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

					
__main      	PROC							
				; place you initialization code here
				
				;enable clock on GPIOA and GPIOC
				ldr r0, =RCC_AHB1_BASE
				ldr r1, [r0, #RCC_AHB1ENR_OFFSET]
				orr r1, r1, #5;0b101
				str r1, [r0, #RCC_AHB1ENR_OFFSET]
				
				;set PA[4-9] to output
				ldr r0, =GPIOA_BASE
				ldr r1, [r0, #GPIOA_MODER_OFFSET]
				orr r1, #(1 << ((FIRST_LED+0) * 2))
				bic r1, #(1 << (((FIRST_LED+0) * 2) + 1))
				orr r1, #(1 << ((FIRST_LED+1) * 2))
				bic r1, #(1 << (((FIRST_LED+1) * 2) + 1))
				orr r1, #(1 << ((FIRST_LED+2) * 2))
				bic r1, #(1 << (((FIRST_LED+2) * 2) + 1))
				orr r1, #(1 << ((FIRST_LED+3) * 2))
				bic r1, #(1 << (((FIRST_LED+3) * 2) + 1))
				orr r1, #(1 << ((FIRST_LED+4) * 2))
				bic r1, #(1 << (((FIRST_LED+4) * 2) + 1))
				orr r1, #(1 << ((FIRST_LED+5) * 2))
				bic r1, #(1 << (((FIRST_LED+5) * 2) + 1))
				str r1, [r0, #GPIOA_MODER_OFFSET]
				
				;set pull-up on PC13
				ldr r0, =GPIOC_BASE
				ldr r1, [r0, #GPIOC_PUPDR_OFFSET]
				orr r1, #(1 << BUTTON * 2)
				str r1, [r0, #GPIOC_PUPDR_OFFSET]			

				
__mainloop            
				; place you application code here

;waiting for button press
_wait_button
				ldr r0, =GPIOC_BASE
				ldr r1, [r0, #GPIOC_IDR_OFFSET]
				and r1, #(1 << 13)
				cmp r1, #(1 << 13)
				beq _wait_button


;action after button press
				eor r3, r3
_loop
				ldr r0, =GPIOA_BASE
				ldr r1, [r0, #GPIOA_BSRR_OFFSET]
				
				mov r4, #16
				lsl r4, r3
				
				orr r1, r4
				str r1, [r0, #GPIOA_BSRR_OFFSET]

				bl _delay
				
				add r3, #1
				cmp r3, #6
				bne _loop
				
				
;turn off all leds after finishing of action				
				ldr r0, =GPIOA_BASE
				ldr r1, [r0, #GPIOA_BSRR_OFFSET]
				
				mov r4, #0xff
				lsl r4, #20
				
				orr r1, r4
				str r1, [r0, #GPIOA_BSRR_OFFSET]

				bl _delay
			
		B __mainloop
		ENDP
;////////////////////////////////////////////////
;delay void
_delay	PROC

		push {r2}
		
		ldr r2, =DELAY
delay
		sub r2, #1
		cmp r2, #0
		bne delay	
		
		pop {r2}
		bx lr
		ENDP	
;////////////////////////////////////////////////			
		ALIGN			
		END
