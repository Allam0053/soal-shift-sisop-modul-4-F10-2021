#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int main(int argc, char const *argv[]) {
  
  return 0;
}
