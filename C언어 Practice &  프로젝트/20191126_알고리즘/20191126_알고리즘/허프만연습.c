
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SZ 100
#define ASCII 256

typedef struct node
{
	char c;
	int f;
	struct node* left;
	struct node* right;

}node;

node **heap;
int lastheapidx = 0;

int charFreq[ASCII]; // charFreq[97 (a)] = 10; charFreq[65(A)] = 34;

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

int countnonzerocharacter()
{
	int cnt = 0;
	for (int i = 0; i < ASCII; i++)
	{
		if (charFreq[i] > 0)
		{
			cnt++;
		}
	}
	return cnt;
}

void addheap(node* _temp)
{
	lastheapidx++;
	heap[lastheapidx] = _temp;

	int currentidx = lastheapidx;
	int parentidx = currentidx/ 2;
	while (parentidx >= 1)
	{
		if (heap[parentidx]->f > heap[currentidx]->f)
		{
			//부모가 자식보다 크면 안되니까...
			//바꿔야함
			node* temp = heap[parentidx];
			heap[parentidx] = heap[currentidx];
			heap[currentidx] = temp;

			currentidx = parentidx;
			parentidx = currentidx / 2;
		}
		else
		{ 
			//자식이 더 작으면 탈출
			break;
		}
	}
}

void performEncoding(char* fName)
{
	//fopen, fread, fclose
	FILE* fin;
	fin = fopen(fName, "rt");
	char buf[SZ];
	if (fin == 0)
	{
		printf("Unable to open %s. Program terminated.\n", fName);
		return;
	}
	memset(charFreq, 0, ASCII * sizeof(int)); //set charFreq as zero
	while (fgets(buf, SZ, fin) != 0)
	{
		int len = strlen(buf);
		for (int i = 0; i < len; i++)
		{
			charFreq[(int)buf[i]]++;
		}
	}

	showCharFrequency();
	//빈도수가 0 이상인것 출력
	int cnt = countnonzerocharacter();
	heap = (node **)malloc((cnt + 1) * sizeof(node*));
	memset(heap, 0, (cnt + 1) * sizeof(node*));
	
	for (int i = 0; i < ASCII; i++)
	{
		if (charFreq[i] > 0)
		{
			node* temp = (node*)malloc(sizeof(node));
			temp->c = (char)i;
			temp->f = charFreq[i];
			temp->left = temp->right = 0;
			addheap(temp);
		}
	}

	printf("root %d (%c ) : %d\n", (int)heap[1]->c, heap[1]->c, heap[1]->f);
	fclose(fin);

}

void showCharFrequency(void)
{
	//charfreq
	for (int i = 0; i < ASCII; i++)
	{
		// 빈도수 1이상인 것만 출력
		if (charFreq[i] > 0)
		{
			printf("ASCII code %d ( %c ) : %d \n", i, (char)i, charFreq[i]);
		}
	}
}