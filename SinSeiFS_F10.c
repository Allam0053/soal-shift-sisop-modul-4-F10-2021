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
			{
				kode[i] += (27 - ((kode[i] - 96) * 2));
			}
			else if(isupper(kode[i]))
			{
				kode[i] += (27 - ((kode[i] - 64) * 2));
			}
		}
	}
}

int main(int argc, char const *argv[]) {
  
  return 0;
}
