#define FUSE_USE_VERSION 28
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stlib.h>
#include <math.h>
#include <fuse.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

void atbash(char kode[])
{
	int i;
	for(i = 0; i < strlen(kode); i++)
	{
		if(isalpha(kode[i]))
		{
			if(islower(kode[i]))
			kode[i] += (27 - ((kode[i] - 96) * 2));
			else if(isupper(kode[i]))
			kode[i] += (27 - ((kode[i] - 64) * 2));
		}
	}
}

void kodes(char kode[])
{
	int i;
	for(i = 0; i < strlen(kode); i++)
	{
		if(isalpha(kode[i]))
		{
			if(islower(kode[i]))
			{
				if(kode[i] <= 109)
				kode[i] += 13;
				else
				kode[i] -= 13;
			}
			else if(isupper(kode[i]))
			{
				if(kode[i] <= 77)
				kode[i] += 13;
				else
				kode[i] -= 13;
			}
		}
	}
}

void vignette(char kode[])
{
	int i, temp;
	char* sisop = "SISOP";
	for(i = 0; i < strlen(kode); i++)
	{
		if(isalpha(kode[i]))
		{
			if(islower(kode[i]))
			{
				if(kode[i] + (sisop[i % strlen(sisop)] - 64) <= 122)
				kode[i] += (sisop[i % strlen(sisop)] - 64) - 1;
				else
				kode[i] -= 26 - (sisop[i % strlen(sisop)] - 64) + 1;
			}
			else if(isupper(kode[i]))
			{
				if(kode[i] + (sisop[i % strlen(sisop)] - 64) <= 90)
				kode[i] += (sisop[i % strlen(sisop)] - 64) - 1;
				else
				kode[i] -= 26 - (sisop[i % strlen(sisop)] - 64) + 1;
			}
		}
	}
}

void special(char kode[])
{
	int biner[strlen(kode)], i, angka = 0, j = 0, k = 0;
	char angkachar[1000];
	for(i = 0; i < strlen(kode); i++)
	{
		if(kode[i] == '.')
		break;
		if(isalpha(kode[i]) && isupper(kode[i]))
		{
			biner[i] = 1;
			kode[i] = tolower(kode[i]);
		}
		else
		{
			biner[i] = 0;
		}
		//printf("%d", biner[i]);
		j++;
	}
	//printf("\n%d\n", j);
	j -= 1;
	for(j; j >= 0; j--)
	{
		if(biner[j] != 0)
		{
			angka += pow(2, k);
			//printf("%d\n", angka);
		}
		k++;
	}
	itoa(angka, angkachar, 10);
	strcat(kode, ".");
	strcat(kode, angkachar);
//	printf("%d\n", angka);
}

int main(int argc, char const *argv[]) {
  
  return 0;
}
