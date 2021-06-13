# soal-shift-sisop-modul-4-F10-2021

### Soal 1
Jika ada direktori dibuat atau direname dengan awalan AtoZ_, direktori dan isinya ter-encode Atbash. Jika diubah, akan ter-decode. Ini dilakukan secara rekursif jika ada direktori di dalam direktori tersebut

## Fungsi Atbash
```
static char atbash_cipher(char ch)
{
  if(isupper(ch)) {
    return upper_case[ch - 65];
  } else {
    return lower_case[ch - 97];
  }
}
```
Digunakan array upper_case yang berisi huruf besar dan lower_case yang berisi huruf kecil
Untuk membalikan stringnya, bisa dipanggil fungsinya lagi, karena sandinya bisa berjalan secara dua arah

### Soal 2
a. Jika direktori dibuat dengan awalan RX_, direktori dan isinya tersebut diencode pertama Atbash, lalu diikuti dengan ROT13
Sandi ROT13 intinya hanya memindahkan masing-masing char 13 huruf ke arah kanan dari susunan alphabet (Atau ASCII). Untuk mengubahnya dengan sandi ROT13 dapat menggunakan fungsi ini

## Fungsi ROT13
```
static char rot_13_cipher(char ch)
{
  if (isupper(ch)) {
    if (ch < 'N') {
      ch += 13;
    } else if (ch >= 'N') {
      ch -= 13;
    }
  } else if (islower(ch)) {    
    if (ch >= 'n') {
      ch -= 13;
    } else if (ch < 'n') {
      ch += 13;
    }
  }

  return ch;
}
```

Karena ini merupakansandi ganda, maka ada penggabungan sandi Atbash dan ROT13, yang bisa menggunakan fungsi ini
##Fungsi sandi rangkap Atbash dan ROT13
```
static void en_de_crypt_12(char * str, bool with_rot)
{
  char item_name[PATH_MAX];
  strcpy(item_name, str);
  char ext[PATH_MAX];

  int size = strlen(str);
  for (int i = strlen(str); i >= 0; i--) {
    if (str[i] == '.') {
      size = i;
      break;
    }
  }

  for (int i = 0; i < size; i++) {
    if(!isalpha(str[i])) {
      continue;
    }

    str[i] = atbash_cipher(str[i]);
    if (with_rot) {
      str[i] = rot_13_cipher(str[i]);
    }
  }
}
```

b. Jika direktori di-rename dengan awalan RX_, direktori dan isinya diencode pertama dengan Atbash, lalu dengan Vigenere dengan key "SISOP"
Sandi Viginere mengubah masing-masing huruf ke arah kanan sebanyak sandi angka dari masing-masing huruf di key satu per satu dari kiri, lalu dikurangi 1.

## Fungsi Viginere
```
static char * vigenere_cipher(char * str)
{
  char * key = "SISOP";
  char new_key[strlen(str)];

  for(int i = 0, j = 0; i < strlen(str); i++, j++) {
    if (j == strlen(key)) {
      j = 0;
    }

    new_key[i] = key[j];
  }

  for(int i = 0; i < strlen(str); ++i) {
    if(!isalpha(str[i])) {
      continue;
    }
    
    str[i] = ((str[i] + new_key[i]) % 26) + 'A';
  }

  return str;
}
```
c. Jika direktori di-rename dengan menghapuskan RX_, direktori kembali menjadi aslinya, tergantung jenis encodingnya, mengingat ada dua cara

Untuk mengecek apakah sebuah direktori atau file terenkode, dapat menggunakan fungsi pengecekan apakah string path direktori atau file terenkode
##Fungsi Pengecekan
```
static bool is_encrypted(char * path, char * by)
{
  if (strstr(path, by)) {
    return true;
  }

  return false;
}
```
```
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
```
d. Setiap encode, akan tercatap dalam log file
e. File-file dalam direktori dipecah menjadi 1024 bytes, tapi jika diakses, akan menjadi normal

### Soal 3
Jika ada direktori dibuat atau di-rename dengan awalan A_is_a_, maka nama direktori tersebut akan menjadi direktori spesial. Jika dihapus A_is_a-nya, maka direktori tersebu menjadi normal. Semua folder di-dalamnya akan di-lowercase-kan dan ditambahkan sebuah angka yang menjadi hasil desimal dari biner dari huruf-huruf yang kapital
Baru bisa membuat fungsi untuk mengubah nama file menjadi lowercase dan menambah angka di belakangnya
```
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
	sprintf(angkachar, "%d", angka);
	strcat(kode, ".");
	strcat(kode, angkachar);
//	printf("%d\n", angka);
}
```
Belum ada fungsi pembaliknya, karena menemui beberapa masalah yang berhubungan dengan string

Untuk fungsi-fungsi fusenya copas dari modul

### Masalah yang dihadapi
1. Kurangnya referensi dari internet dan pemahamannya
2. Kurangnya pemahaman dari isi-isi dari fungsi-fungsi fuse
3. Sulitnya membaca, oleh manusia bukan laptop, hasil dari file dan directory yang dibaca oleh fungsi-fungsi fuse agar dapat mengetahui cara kerjanya fuse
