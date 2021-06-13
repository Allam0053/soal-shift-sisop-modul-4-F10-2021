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
## Fungsi sandi rangkap Atbash dan ROT13, serta kebalikannya, untuk Atbash dan ROT13
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
Fungsi diatas juga akan mengecek apakah sandi yang digunakan menggunakan Vigenere atau ROT13, dengan menggunakan argumen with_rot

b. Jika direktori di-rename dengan awalan RX_, direktori dan isinya diencode pertama dengan Atbash, lalu dengan Vigenere dengan key "SISOP"
Sandi Viginere mengubah masing-masing huruf ke arah kanan sebanyak sandi angka dari masing-masing huruf di key satu per satu dari kiri, lalu dikurangi 1.
Fungsi ini menggabungkan sandi Atbash dan Vigenere dengan manipulasi ASCII

## Fungsi Vigenere
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

## Fungsi Pengecekan
```
static bool is_encrypted(char * path, char * by)
{
  if (strstr(path, by)) {
    return true;
  }

  return false;
}
```
Jika terkode, maka akan dikodekan kembali seperti semula dengan menggunakan fungsi ini, sekaligus fungsi memulai penyandian
## Fungsi persandian
```
static void pass_path(char * path, char * fpath, bool with_check)
{
  if (strcmp(path, "/") == 0) {
    sprintf(fpath, "%s", dirpath);
  } else {
    if (with_check) {
      if (is_encrypted(path, "/RX_")) {
        char temp_path[PATH_MAX];
        strcpy(temp_path, path);
        char child_path[PATH_MAX];
        split_path(temp_path, child_path, "RX_");

        en_de_crypt_12(child_path, true);
        sprintf(fpath, "%s%s%s", dirpath, temp_path, child_path);
      } else if (is_encrypted(path, "/AtoZ_")) {
        char temp_path[PATH_MAX];
        strcpy(temp_path, path);
        char child_path[PATH_MAX];
        split_path(temp_path, child_path, "AtoZ_");

        en_de_crypt_12(child_path, false);
        sprintf(fpath, "%s%s%s", dirpath, temp_path, child_path);
      } else {
        sprintf(fpath, "%s%s", dirpath, path);
      }
    } else {
      sprintf(fpath, "%s%s", dirpath, path);
    }
  }
}
```
Diantara fungsi di bagian fungsi diatas, ada pemisahan path string, karena yang akan disandi sebagian dari path tersebut.
## Fungsi pemisahan path string
```
static void split_path(char * parent, char * child, char * by)
{
  char fpath[PATH_MAX];
  strcpy(fpath, parent);
  char * substr = strtok(fpath, "/");

  int counter = 0;
  int marker = 0;
  while(substr != NULL) {
    counter++;
    counter += strlen(substr);

    if (!strncmp(substr, by, strlen(by))) {
      marker = counter;
    }

    if (substr != NULL) {
      substr = strtok(NULL, "/");
    }
  }

  strcpy(child, &parent[marker]);
  parent[marker] = '\0';
}
```
d. Setiap encode, akan tercatap dalam log file. Cara penulisannya sama seperti pada soal nomor 4
## Fungsi log file encoding
```
static void write_log(char level[], char cmd[], char arg1[], char arg2[])
{
  char message[PATH_MAX];

  time_t t_o = time(NULL);
  struct tm tm_s = * localtime(&t_o);
  sprintf(message, "%s::%02d%02d%d-%02d:%02d:%02d::%s", 
    level, tm_s.tm_mday, tm_s.tm_mon + 1, tm_s.tm_year + 1900,
    tm_s.tm_hour, tm_s.tm_min, tm_s.tm_sec, cmd);

  if (strlen(arg1) != 0) {
    strcat(message, "::");
    strcat(message, arg1);
  }

  if (strlen(arg2) != 0) {
    strcat(message, "::");
    strcat(message, arg2);
  }

  char * file_name = "SinSeiFS.log";
  FILE * log_file;
  log_file = fopen(file_name, "a");
  fprintf(log_file, "%s\n", message);

  fclose(log_file);
}
```
e. File-file dalam direktori dipecah menjadi 1024 bytes, tapi jika diakses, akan menjadi normal. Untuk sekarang, belum ada karena belum bisa mengetahui cara membaginya

### Soal 3
Jika ada direktori dibuat atau di-rename dengan awalan A_is_a_, maka nama direktori tersebut akan menjadi direktori spesial. Jika dihapus A_is_a-nya, maka direktori tersebu menjadi normal. Semua folder di-dalamnya akan di-lowercase-kan dan ditambahkan sebuah angka yang menjadi hasil desimal dari biner dari huruf-huruf yang kapital. (Untuk yang ini belum bisa mengembalikan nama file dengan biner)


Fungsi khusus soal ini terletak di salah satu fungsi fuse : xmp_readdir
```
static int xmp_readdir(const char * path, void * buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info * fi)
{
  (void)offset;
  (void)fi;

	printf("readdir:\n");
	printf("%s\n", path);

  char fpath[PATH_MAX];
  pass_path(path, fpath, true);

	printf("%s\n", fpath);

  DIR *dp;
  dp = opendir(fpath);
  if (dp == NULL) {
    return -errno;
  }

  bool is_special = false;
  if (is_encrypted(path, "/A_is_a_")) {
    char temp_path[PATH_MAX];
    strcpy(temp_path, path);
    char child_path[PATH_MAX];
    split_path(temp_path, child_path, "RX_");
    if (!strcmp(child_path, "")) {
      is_special = true;
    }
  }

  struct dirent *de;
  while ((de = readdir(dp)) != NULL) {
    if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
      continue;
    }
  
    struct stat st;
    memset(&st, 0, sizeof(st));
    st.st_ino = de->d_ino;
    st.st_mode = de->d_type << 12;

    int res = 0;
    if (!is_special) {
      if (is_encrypted(path, "/RX_") && strncmp(de->d_name, "A_is_a_", 8)) {
        char item_name[PATH_MAX];
        strcpy(item_name, de->d_name);
        
        printf("item_name: %s\n", item_name);

        en_de_crypt_12(item_name, true);
        
        printf("item_name: %s\n", item_name);

        res = (filler(buf, item_name, &st, 0));
      } else if (is_encrypted(path, "/AtoZ_") && strncmp(de->d_name, "A_is_a_", 8)) {
        char item_name[PATH_MAX];
        strcpy(item_name, de->d_name);
        
        printf("item_name: %s\n", item_name);

        en_de_crypt_12(item_name, false);
        
        printf("item_name: %s\n", item_name);

        res = (filler(buf, item_name, &st, 0));
      } else {
        res = (filler(buf, de->d_name, &st, 0));
      }
    } else {
      res = (filler(buf, de->d_name, &st, 0));
    }

    if (res != 0) {
      break;
    }
  }

  closedir(dp);
  write_log("INFO", "READDIR", path, "");
  return 0;
}
```
Untuk fungsi-fungsi fusenya diambil dari Modul 4 Sisop dan situs referensinya

Proses-proses yang terjadi
1. Setelah FUSE di-mount, fungsi fuse akan membaca direktori yang dituju

### Masalah yang dihadapi
1. Sering gagal mount pada directory tertentu
2. Pemahaman FUSE masih perlu diperdalam
3. Tidak dapat memecahkan sebuah file
4. Soal 3 cukup kompleks
