CODE SEGMENT
ASSUME CS:CODE, DS:DATA

CR	EQU	0DH;	line change 
LF	EQU	0AH

	MOV	AX, DATA	;Use data segment
	MOV	DS, AX

	MOV AH, 1 ;	
	INT 21H
	MOV DATA101, AL; 		�� ���� 10�� �ڸ�, 1���ڸ� ���ڸ� 3���� �ݺ��ؼ� ����
	MOV DATABIG101, AL;	�� �� ù��° ���� �ι�° ���� �̸� ����� ������ ����
	
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
	MOV DATA301, AL; �׷��� ������ 3��°�� �߰������� ������ ���� ����

	MOV AH, 1 ;
	INT 21H
	MOV DATA302, AL

	
	 MOV	DL, CR	; Line change
  	 MOV  	AH, 2
  	 INT	21H

  	 MOV	DL, LF
  	 MOV	AH, 2
  	 INT	21H
	
ONTW:	;���⼭ ���� ������ �������� ����, ONTW�� ONETWO�� ���Ѵ��� ����
	;1st�� Ȯ���̳� �ƴϳĸ� �Ǻ�
	MOV	AL, DATA101; 
	MOV	BL, DATA201;
	CMP	AL, BL		; 10�� �ڸ��� ���ؼ�
	JA	TWTH		; first�� ũ�� 1�� Ȯ���̹Ƿ� 2,3�� ���Ϸ���
	JB	ONTH		; �ƴ� ���� 2�� Ȯ���̹Ƿ� 1,3�� ���Ϸ���
				;���� 10�� �ڸ��� ������ 1�� �ڸ��� ���Ϸ� ��
	MOV	AL, DATA102
	MOV	BL, DATA202
	CMP	AL, BL
	JA	TWTH	;10�� �ڸ��� �����ϰ� ũ�Ⱑ �Ǻ��Ǹ� ���Ϸ� �� (2,3 ��)
	JB	ONTH	;(1,3��)
	;JE	TWTH	;���� ���� ���� ��� �ᱹ 1��,2�� �� �����ϳ��� Ȯ���� ���� ������
			;���� ������ ������ �ʿ� ����, �ᱹ JUMP LABEL���� �� 3��°�� ���ϱ� ������
	
ONTH:	;1�� Ȯ���� �ƴ�, 2��Ȯ��, 21�̳� 23�̳�
	MOV	AL, DATA101; 
	MOV	BL, DATA301;
	CMP	AL, BL		; 1st�� 3rd�� 10�� �ڸ� ��
	JA	DETONTW	; 1st�� Ŭ�� 1,2�� ��� Ȯ�� (determinate one & two��� ��)
	JB	DETTWTH		; 3rd�� Ŭ�� 2,3�� ��� Ȯ��; ��� �̷� ���̴�.

	MOV	AL, DATA102
	MOV	BL, DATA302
	CMP	AL, BL	;	1st�� 3rd�� 1�� �ڸ� ��
	JA	DETONTW	; 1st�� Ŭ�� 1,2�� ��� Ȯ�� (determinate one & two��� ��)
	JB	DETTWTH		; 3rd�� Ŭ�� 2,3�� ��� Ȯ��; 
	JMP	CALCUL		; 1,3�� ����? �ᱹ 1,2���� Ȯ�������� ����ϴϱ� �ٷ� ���
	
TWTH:   ;1�� Ȯ��, 12�̳� 13�̳� ���� ONTH�� ������ ���
	MOV	AL, DATA201; 
	MOV	BL, DATA301;
	CMP	AL, BL		; 2nd �� 3rd�� 10�� �ڸ� ��
	JA	DETONTW	; 1,2�� Ȯ��
	JB	DETONTH		; 1,3��Ȯ��
				;������ 1�� �ڸ� ��
	MOV	AL, DATA202
	MOV	BL, DATA302
	CMP	AL, BL	
	JA	DETONTW
	JB	DETONTH
	JMP	CALCUL		;2,3�� ����? ���� 1,2�� ����ϴϱ� �ٷ� ������� ����

DETONTW:	JMP	CALCUL	; �ٷ� ����ϸ� ��

	

DETONTH:	MOV	AL, DATA301	;1,3���� Ȯ�� ��� ������ 2�� ���� ����ִ� ����
		MOV	BL, DATA302	;3�� ���� ��������
		MOV	DATABIG201, AL
		MOV	DATABIG202, BL
		JMP	CALCUL		;�׸��� ���

DETTWTH:	MOV	AL, DATA301	;2,3���� Ȯ����� ������ 1�� ���� ����ִ� ���� 
		MOV	BL, DATA302	;3���� ����
		MOV	DATABIG101, AL	
		MOV	DATABIG102, BL	
		JMP	CALCUL		;���

CALCUL:	MOV	CL, DATABIG102 ; 1�� �ڸ�
	ADD	CL, DATABIG202 ; ����

	MOV	BL, DATABIG101; 10�� �ڸ�
	ADD	BL, DATABIG201;	���� ,���� ADC�� ���� �ʰ� �����
			
	MOV	AL, 106; ����ǥ�� '10'�� �����̱⿡
	CMP	CL, AL;	1�� �ڸ��� 10 �̸��̸� �׳� ���
	JB	CALCUL2
			;�̻��� ��� 1�� �ڸ� -10, 10�� �ڸ� +1
	INC	BL
	SUB	CL, 10
			
CALCUL2:	CMP	BL, AL;	�ٽ� 10�� �ڸ��� 100�� �ڸ��� �Ǵ� �� ����� ���� ��
	JB	PRIINT	;���� ��� �׳� ���
	
	SUB	BL, 10	;ū ��� 10�� �ڸ� -10
	MOV	DL, '1'	;1(100)�� ���
	MOV	AH, 2
	INT	21H
	
	
PRIINT:	SUB	BL, 48; 10�ڸ� ����� �ǵ� ����ǥ ����� ���� -'0'�� ����
	MOV	DL, BL;
	MOV	AH, 2
	INT	21H
	
	SUB	CL, 48; 1�� �ڸ� ������ ������� ���
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