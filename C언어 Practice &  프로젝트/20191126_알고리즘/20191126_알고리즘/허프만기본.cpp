#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUF_SZ 100
#define NUM_ASCII 256

int charFreq[NUM_ASCII]; // charFreq[97 (a)] = 10; charFreq[65(A)] = 34;

//argc : argument count
//ex. huff.exe - e alice.txt, argc==> 3 //프로그램이름, encoding, filename 해서 argc는 3개
// argv: argument variable
// argv[0] = "huff.exe", argv[1] ="-e", argv[2] = "alice.txt"

//function foward declaration
void performEncoding(char* fName);
void showCharFrequency(void);
int main(int argc, char* argv[])
{

	if (argc < 3)
	{
		printf("Usage: huff.exe -e fileToEncode\n");
		printf("	   huff.exe - d fileToDecode\n");
		return -1;
	}

	if (strcmp(argv[1], "-e") == 0)
	{
		//huffman coding
		printf("Start Huffman Encoding\n");
		performEncoding(argv[2]);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		//decoding
		printf("Start Huffman Decoding\n");
		//performDecoding(argv[3]);
	}
	else
	{
		printf("Usage: huff.exe -e fileToEncode\n");
		printf("	   huff.exe -d fileToDecode\n");
		return -1;
	}
	return 0;
}

void performEncoding(char* fName)
{
	//fopen, fread, fclose
	FILE* fin;
	fin = fopen(fName, "rt");
	char buf[BUF_SZ];
	if (fin == 0)
	{
		printf("Unable to open %s. Program terminated.\n", fName);
		return;
	}
	memset(charFreq, 0, NUM_ASCII * sizeof(int)); //set charFreq as zero
	while (fgets(buf, BUF_SZ, fin) != 0)
	{
		int len = strlen(buf);
		for (int i = 0; i < len; i++)
		{
			charFreq[(int)buf[i]]++;
		}
	}

	showCharFrequency();

	fclose(fin);

}

void showCharFrequency(void)
{
	//charfreq
	for (int i = 0; i < NUM_ASCII; i++)
	{
		// 빈도수 1이상인 것만 출력
		if (charFreq[i] > 0)
		{
			printf("ASCII code %d ( %c ) : %d \n", i, (char)i, charFreq[i]);
		}
	}
}