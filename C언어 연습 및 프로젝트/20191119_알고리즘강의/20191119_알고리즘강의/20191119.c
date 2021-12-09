#include<stdio.h>

int main()
{
	char toWrite = 0;

	FILE* f;
	//11110000을 8byte로 씀
	//f = fopen("data", "wt");
	//fprintf(f, "11110000");
	//fclose(f);

	//binary mode
	//11110000을 1byte로 씀
	f = fopen("data", "wb");
	toWrite = 0xf0;

	//text는 fprint , binarty는 fwrite
	//toWrite 버퍼에서(주소)
	//1바이트 짜리를
	//1개를
	//파일f에쓴다
	//어떤 애를,몇바이트씩,몇개를,어느 파일에서
	fwrite(&toWrite, 1, 1, f);
	fclose(f);

}