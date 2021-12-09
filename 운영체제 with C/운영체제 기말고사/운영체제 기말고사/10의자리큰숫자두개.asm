CODE SEGMENT
ASSUME CS:CODE, DS:DATA

CR	EQU	0DH;	line change 
LF	EQU	0AH

	MOV	AX, DATA	;Use data segment
	MOV	DS, AX

	MOV AH, 1 ;	
	INT 21H
	MOV DATA101, AL; 		쭉 이제 10의 자리, 1의자리 숫자를 3번씩 반복해서 저장
	MOV DATABIG101, AL;	그 중 첫번째 값과 두번째 값을 미리 연산용 변수에 저장
	
	MOV AH, 1 ;
	INT 21H
	MOV DATA102, AL
	MOV DATABIG102, AL

	MOV AH, 1 ;
	INT 21H
	MOV DATA201, AL
	MOV DATABIG201, AL

	MOV AH, 1 ;
	INT 21H
	MOV DATA202, AL
	MOV DATABIG202, AL

	MOV AH, 1 ;
	INT 21H
	MOV DATA301, AL; 그렇기 때문에 3번째만 추가변수에 저장이 되지 않음

	MOV AH, 1 ;
	INT 21H
	MOV DATA302, AL

	
	 MOV	DL, CR	; Line change
  	 MOV  	AH, 2
  	 INT	21H

  	 MOV	DL, LF
  	 MOV	AH, 2
  	 INT	21H
	
ONTW:	;여기서 부터 누구를 선발할지 결정, ONTW는 ONETWO를 비교한다의 약자
	;1st가 확정이냐 아니냐를 판별
	MOV	AL, DATA101; 
	MOV	BL, DATA201;
	CMP	AL, BL		; 10의 자리를 비교해서
	JA	TWTH		; first가 크면 1은 확정이므로 2,3을 비교하러감
	JB	ONTH		; 아닌 경우는 2가 확정이므로 1,3을 비교하러감
				;만약 10의 자리가 같으면 1의 자리를 비교하러 감
	MOV	AL, DATA102
	MOV	BL, DATA202
	CMP	AL, BL
	JA	TWTH	;10의 자리와 동일하게 크기가 판별되면 비교하러 감 (2,3 비교)
	JB	ONTH	;(1,3비교)
	;JE	TWTH	;만일 둘이 같은 경우 결국 1번,2번 중 둘중하나는 확실히 쓰기 때문에
			;굳이 별도의 점프가 필요 없음, 결국 JUMP LABEL에는 다 3번째와 비교하기 때문에
	
ONTH:	;1이 확정이 아님, 2는확정, 21이냐 23이냐
	MOV	AL, DATA101; 
	MOV	BL, DATA301;
	CMP	AL, BL		; 1st와 3rd의 10의 자리 비교
	JA	DETONTW	; 1st가 클시 1,2번 사용 확정 (determinate one & two라는 뜻)
	JB	DETTWTH		; 3rd가 클시 2,3번 사용 확정; 모두 이런 식이다.

	MOV	AL, DATA102
	MOV	BL, DATA302
	CMP	AL, BL	;	1st와 3rd의 1의 자리 비교
	JA	DETONTW	; 1st가 클시 1,2번 사용 확정 (determinate one & two라는 뜻)
	JB	DETTWTH		; 3rd가 클시 2,3번 사용 확정; 
	JMP	CALCUL		; 1,3이 같다? 결국 1,2번을 확정적으로 사용하니까 바로 계산
	
TWTH:   ;1은 확정, 12이냐 13이냐 위의 ONTH와 동일한 방식
	MOV	AL, DATA201; 
	MOV	BL, DATA301;
	CMP	AL, BL		; 2nd 와 3rd의 10의 자리 비교
	JA	DETONTW	; 1,2번 확정
	JB	DETONTH		; 1,3번확정
				;같을시 1의 자리 비교
	MOV	AL, DATA202
	MOV	BL, DATA302
	CMP	AL, BL	
	JA	DETONTW
	JB	DETONTH
	JMP	CALCUL		;2,3이 같다? 역시 1,2를 사용하니까 바로 계산으로 점프

DETONTW:	JMP	CALCUL	; 바로 계산하면 됨

	

DETONTH:	MOV	AL, DATA301	;1,3번이 확정 됬기 때문에 2번 값이 들어있는 곳에
		MOV	BL, DATA302	;3번 값을 갱신해줌
		MOV	DATABIG201, AL
		MOV	DATABIG202, BL
		JMP	CALCUL		;그리고 계산

DETTWTH:	MOV	AL, DATA301	;2,3번이 확정됬기 때문에 1번 값이 들어있는 곳에 
		MOV	BL, DATA302	;3번값 갱신
		MOV	DATABIG101, AL	
		MOV	DATABIG102, BL	
		JMP	CALCUL		;계산

CALCUL:	MOV	CL, DATABIG102 ; 1의 자리
	ADD	CL, DATABIG202 ; 덧셈

	MOV	BL, DATABIG101; 10의 자리
	ADD	BL, DATABIG201;	덧셈 ,굳이 ADC를 쓰지 않고 계산함
			
	MOV	AL, 106; 문자표로 '10'의 개념이기에
	CMP	CL, AL;	1의 자리가 10 미만이면 그냥 계산
	JB	CALCUL2
			;이상인 경우 1의 자리 -10, 10의 자리 +1
	INC	BL
	SUB	CL, 10
			
CALCUL2:	CMP	BL, AL;	다시 10의 자리가 100의 자리가 되는 지 계산을 위해 비교
	JB	PRIINT	;작은 경우 그냥 출력
	
	SUB	BL, 10	;큰 경우 10의 자리 -10
	MOV	DL, '1'	;1(100)을 출력
	MOV	AH, 2
	INT	21H
	
	
PRIINT:	SUB	BL, 48; 10자리 출력할 건데 문자표 계산을 위해 -'0'을 해줌
	MOV	DL, BL;
	MOV	AH, 2
	INT	21H
	
	SUB	CL, 48; 1의 자리 동일한 방법으로 출력
	MOV	DL, CL;
	MOV	AH, 2
	INT	21H

	
FIN:	MOV	AH, 4CH	
	INT	21H

CODE ENDS

DATA	SEGMENT

DATA101	DB 	0
DATA102 DB 	0

DATA201 DB 	0
DATA202 DB	0

DATA301 DB 	0
DATA302 DB 	0	

DATABIG101	DB	0
DATABIG102	DB	0

DATABIG201	DB	0
DATABIG202	DB	0

DATA ENDS

END