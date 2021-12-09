#include<stdio.h>
#include<string.h>

#define BUF_SZ 100
#define NUM_ASCII 255
int charFreq[NUM_ASCII]; //charFreq[97 (a)]=10; charFreq(65(A)]=34;





//argc : argument count
// ex. huff.exe -e alice.txt, argc==> 3
//argv : argument variable
//argv[0]="huff.exe' ,argv[1]='-e', argv[2]='alice.txt'
void showCharFrequency()
{
	// charFreq
	for (int i = 0; i < NUM_ASCII; i++)
	{
		// 빈도수 1 이상인것만 출력
		if (charFreq[i] > 0)
		{
			printf("ASCII code = %d ( %c ) ; %d \n", i, (char)i, charFreq[i]);
		}
	}
}
void perfomEncoding(char* fName)
{
	//fopen, fread, fclose
	FILE* finput;
	char buf[BUF_SZ];

	finput = fopen(fName, "rt");
	if (finput == 0)
	{
		printf("Unable to Open %s. Program terminated.\n", fName);
		return;
	}

	//file read
	memset(charFreq, 0, NUM_ASCII * sizeof(int));
	while (fgets(buf, BUF_SZ, finput) != 0)
	{
		int len = strlen(buf);

		for (int i = 0; i < len; i++)
		{
			charFreq[(int)buf[i]]++;

		}

	}

	showCharFrequency();
	fclose(finput);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Usage : huff.exe -e fileToEncode\n");
		printf("      : huff.exe -d fileToDecode\n");
		return -1;
	}

	if (strcmp(argv[1], "-e") == 0)
	{
		//huffman coding
		printf("Start Huffman Encoding\n");
		perfomEncoding(argv[2]);

	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		//decoding
		printf("Start Huffman Decoding\n");
		//perfomDecoding(argv[2]);
	}
	else
	{
		printf("Usage : huff.exe -e fileToEncode\n");
		printf("      : huff.exe -d fileToDecode\n");
		return -1;
	}
	return 0;
}