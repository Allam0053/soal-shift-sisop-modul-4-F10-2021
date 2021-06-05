# soal-shift-sisop-modul-4-F10-2021

### Soal 1
Jika ada direktori dibuat atau direname dengan awalan AtoZ_, direktori dan isinya ter-encode Atbash. Jika diubah, akan tet-decode.
Untuk sementara, saya baru bisa membuat fungsi untuk mengubah string, bukan direktori, dengan sandi Atbash
```
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
```
Untuk membalikan stringnya, bisa dipanggil fungsinya lagi, karena sandinya bisa berjalan secara dua arah

### Soal 2
a. Jika direktori dibuat dengan awalan RX_, direktori dan isinya tersebut diencode pertama Atbash, lalu diikuti dengan ROT13
Sandi ROT13 intinya hanya memindahkan masing-masing char 13 huruf ke arah kanan dari susunan alphabet (Atau ASCII). Sama seperti nomor 1, baru bisa membuat fungsinya saja
```
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
```
b. Jika direktori di-rename dengan awalan RX_, direktori dan isinya diencode pertama dengan Atbash, lalu dengan Vigenere dengan key "SISOP"
Sandi Viginere mengubah masing-masing huruf ke arah kanan sebanyak sandi angka dari masing-masing huruf di key satu per satu dari kiri, lalu dikurangi 1. Masih baru bisa membuat fungsinya
```
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

```
c. Jika direktori di-rename dengan menghapuskan RX_, direktori kembali menjadi aslinya, tergantung jenis encodingnya
Masih belum tahu caranya membedakan jenis encodingnya. Fungsi yang dibuat baru bisa mengembalikan sandi ROT13, tapi bukan Vigenere
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
``
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
``
Belum ada fungsi pembaliknya, karena menemui beberapa masalah yang berhubungan dengan string
### Masalah yang dihadapi
1. Kurangnya referensi dari internet dan pemahamannya
2. Kurangnya pemahaman dari isi-isi dari fungsi-fungsi fuse
3. Sulitnya membaca, oleh manusia bukan laptop, hasil dari file dan directory yang dibaca oleh fungsi-fungsi fuse agar dapat mengetahui cara kerjanya fuse
