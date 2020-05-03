			AREA FUNCTION, CODE, READONLY
			EXPORT StrCopyRev
				
StrCopyRev	PROC

			mov r3, #0	;initial value of r3


loop_0	;sizing of array-source
			
			;load the data from cells of array-source 
			ldrb r2, [r0, r3]
			
			;"iterator"
			add r3, #1	;r3 += 1
			
			;if(r2 == 0) {continue}
			;else {new iteration of <loop_0>}
			cmp r2, #0
			bne loop_0
			
			;if(r3 == 1) {return from the function}
			;else {continue}
			cmp r3, #1
			beq end_

			;correct the size of array-source
			sub r3, #2	;r3 -= 2
			
			add r0, r3	;go to the end of array-source
		
loop_1	;copying array-source to array-destination in reverse order

			LDRB r3, [r0]	;load the data from array-source to temp reg
			STRB r3, [r1]	;load data from temp reg to array-destination
			
			;addresses of cells of array-source and array-destination
			subs r0, #1	;r0--		
			adds r1, #1	;r1++
			
			;if(r3 == 0) {return from the function}
			;else {new iteration of <loop_1>}
			cmp r3, #0
			bne loop_1
			bx lr

end_
			ENDP


			EXPORT SumOfUnsigned
				
SumOfUnsigned PROC
			
			push {r4}	;save r4 to stack
			
			eor r4, r4	;(r4 = 0)clear the high part of accumulator
			
			;load to accumulator the start value
			ldr r2, [r0]
			mov r3, r2
			
			sub r1, #1	;(r1 -= 1)dec the iterator
			add r0, #4	;(r0 += 4)increase the addr of cell of array
loop_2
			
			ldr r2, [r0]	;load data from array
			adds r3, r2		;add add it to accumulator
			adc r4, #0		;if carry flag is set then r4 += 1
			
			sub r1, #1	;(r1 -= 1)dec the iterator	
			add r0, #4	;(r0 += 4)increase the addr of cell of array

			;if(r1 != 0) { do next iteration}
			;else {continue}
			cmp r1, #0
			bne loop_2
			
			mov r0, r3	;load the low part of result to r0
			mov r1, r4	;load the high part of result to r1
			
			pop {r4}	;load r4 from stack
			bx lr	;return from the function
	
			ENDP




			EXPORT SumOfSigned
				
SumOfSigned PROC
			
			push {r4-r5}	;save r4 and r5 to stack
			
			;move to temporary registers data from r0 and r1
			mov r2, r0
			mov r3, r1
			
			;clear r0 and r1
			eor r0, r0
			eor r1, r1
			
loop_sig
			ldr r4, [r2]		;load the value to be added
			asr r5, r4, #31		;extend r5 with the sign of r4
			adds r0, r0, r4		;add lower 4 bytes and set carry flag
			adc r1, r1, r5		;add upper 4 bytes including carry
			
			add r2, #4		;increase an addres of data
			sub r3, #1		;decrease an iteratoe
			
			cmp r3, #0		;if(r3 != 0)
			bne loop_sig	;then <new iteratin>
			
			;else <exit>
			pop {r4-r5}
			bx lr

	
			ENDP


			END