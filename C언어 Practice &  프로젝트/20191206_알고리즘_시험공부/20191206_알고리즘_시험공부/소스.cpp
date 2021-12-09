#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SZ 100
#define ascii 256

char code[256][100];
char buf[100];
int buf_cnt[ascii];
char decode_buf[ascii] = { 0, };
char make_code[100];
//3a200b11c201$00001101#

int main()
{
	int num;
	char code_code;
	char letter;
	char number;
	int k = 0;
	scanf("%d", &num); //최초의 입력 갯수 -> 필요없음
	scanf("%c", &code_code); // (알파벳입력) 이제부터 char로 모두 입력받을 거임
	int w = num;
	while (1)
	{
		if (code_code == '$')
		{
			break;
		}

		scanf("%c", &number); //알파벳 입력후 숫자를 char로 받을 거임
		buf_cnt[code_code] = (int)number; //숫자를 int형으로 변환
		/*
		int buf_counting = 0;
		while(buf_counting != number)
		{
		   buf[k] = code_code;
		   buf_counting++;
		   k++;
		}
		*/
		char _code = code_code; //현 알파벳을 복사
		int i = 0;

		while (1)
		{
			num--;
			scanf("%c", &code_code);//이제부터는 0또는 1을 입력받을거임
			if (code_code == '$')
			{
				break;
			}
			if (code_code < '0' || code_code > '1')
			{
				code[_code][i] = 0; //여기서 코드 종료를 알리는 0을 넣고
				//break가 되면 이번 code_code는 알파벳으로서 작용
				break;
			}
			else
			{
				code[_code][i] = code_code;
				i++;
			}
		}
		//printf("%s\n", code[_code]);
	}

	int j = 0;
	int flag = 0;
	int i = 0;
	int cnt = 0;
	while (1)
	{
		scanf("%c", &number);
		if (number == '#')
		{
			break;
		}
		make_code[j] = number; //number를 추가하고
		make_code[j + 1] = 0; //null을 끝자락에 붙힘(안해도됨)
		//printf("%s\n", make_code); 코드가 어떻게 형성되는지 확인
		for (int k = 0; k < 256; k++)
		{
			//모든 코드 테이블을 뒤져서
			if (code[k][0] == 0) //시작부터 아무것도 없다? 이 코드테이블은 비어있다
			{ //따라서 스킵
				continue;
			}
			flag = 0;
			i = 0;
			while (1) //코드 테이블에 값이 있는 것중에서
			{
				if (code[k][i] == 0) //현 코드 테이블이 끝날때까지 할 건데
				{
					break;
				}
				if (make_code[i] == code[k][i]) //현 코드와 각 코드테이블안의 코드를 한자리씩 각각비교
				{
					flag++; //같으면 flag올려줌
				}
				i++;
			}

			if (i == flag) // 만약 flag가 i값과 같다? -> 모든 요소가 같다
			{
				printf("%c", k);
				for (int i = 0; i < 100; i++) // 초기화 해주고
				{
					make_code[i] = 0;
				}
				flag = 0; //
				j = -1; //j=0부터 시작해야되니까 
				break;
			}
			//printf("%d %d\n", flag, i);
			/*
			for (int o = 0; o < j+1; o++) //현재 makecode의 길이 만큼
			{
			   if (make_code[o] == code[k][o])
			   {
				  flag++;
			   }
			}

			if (j+1 == flag)
			{
			   printf("%c", k);
			   for (int i = 0; i < 100; i++)
			   {
				  make_code[i] = 0;
			   }
			   //flag = 0;
			   j = -1;
			   break;
			}
			*/
		}
		j++; // 새로운 코드를 받아 테이블을 다시 탐색함
	}
	return 1;
}