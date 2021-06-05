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

void kodes_balik(char kode[])
{
	int i;
	for(i = 0; i < strlen(kode); i++)
	{
		if(isalpha(kode[i]))
		{
			if(islower(kode[i]))
			{
				if(kode[i] > 109)
				kode[i] -= 13;
				else
				kode[i] += 13;
			}
			else if(isupper(kode[i]))
			{
				if(kode[i] > 77)
				kode[i] -= 13;
				else
				kode[i] += 13;
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
				//printf("%c %d\n", sisop[i % strlen(sisop)], kode[i]);
				if(kode[i] + (sisop[i % strlen(sisop)] - 64) - 1 <= 122)
				kode[i] += (sisop[i % strlen(sisop)] - 64) - 1;
				else
				kode[i] -= 26 - (sisop[i % strlen(sisop)] - 64) + 1;
				
				//printf("%d\n", kode[i]);
			}
			else if(isupper(kode[i]))
			{
				if(kode[i] + (sisop[i % strlen(sisop)] - 64) - 1 <= 90)
				kode[i] += (sisop[i % strlen(sisop)] - 64) - 1;
				else
				kode[i] -= 26 - (sisop[i % strlen(sisop)] - 64) + 1;
			}
		}
	}
}

void vignette_balik(char kode[])
{
	int i, temp;
	char* sisop = "SISOP";
	for(i = 0; i < strlen(kode); i++)
	{
		if(isalpha(kode[i]))
		{
			if(islower(kode[i]))
			{
				//printf("%d %d\n", sisop[i % strlen(sisop)] - 65, kode[i]);
				if(kode[i] - (sisop[i % strlen(sisop)] - 65) >= 97)
				kode[i] -= (sisop[i % strlen(sisop)] - 65);
				else
				kode[i] += 26 - (sisop[i % strlen(sisop)] - 64) + 1;
				//else
				//kode[i] += 
				
				//printf("%d\n", kode[i]);
			}
			else if(isupper(kode[i]))
			{
				if(kode[i] - (sisop[i % strlen(sisop)] - 65) >= 65)
				kode[i] -= (sisop[i % strlen(sisop)] - 65);
				else
				kode[i] += 26 - (sisop[i % strlen(sisop)] - 64) + 1;
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
	//for(j; j >= 0; j--)
	while(j >= 0)
	{
		if(biner[j] != 0)
		{
			angka += pow(2, k);
			//printf("%d\n", angka);
		}
		k++;
		j--;
	}
	itoa(angka, angkachar, 10);
	strcat(kode, ".");
	strcat(kode, angkachar);
//	printf("%d\n", angka);
}


static  int  xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];

    sprintf(fpath,"%s%s",dirpath,path);

    res = lstat(fpath, stbuf);

    if (res == -1) return -errno;

    return 0;
}



static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];

    if(strcmp(path,"/") == 0)
    {
        path=dirpath;
        sprintf(fpath,"%s",path);
    } else sprintf(fpath, "%s%s",dirpath,path);

    int res = 0;

    DIR *dp;
    struct dirent *de;
    (void) offset;
    (void) fi;

    dp = opendir(fpath);

    if (dp == NULL) return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;

        memset(&st, 0, sizeof(st));

        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        res = (filler(buf, de->d_name, &st, 0));

        if(res!=0) break;
    }

    closedir(dp);

    return 0;
}



static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    if(strcmp(path,"/") == 0)
    {
        path=dirpath;

        sprintf(fpath,"%s",path);
    }
    else sprintf(fpath, "%s%s",dirpath,path);

    int res = 0;
    int fd = 0 ;

    (void) fi;

    fd = open(fpath, O_RDONLY);

    if (fd == -1) return -errno;

    res = pread(fd, buf, size, offset);

    if (res == -1) res = -errno;

    close(fd);

    return res;
}



static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
};

int main(int argc, char const *argv[]) {
  umask(0);
  return fuse_main(argc, argv, &xmp_oper, NULL);
  return 0;
}
