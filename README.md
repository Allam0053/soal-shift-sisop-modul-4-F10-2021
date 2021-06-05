# soal-shift-sisop-modul-4-F10-2021

### Soal 1
Jika ada direktori dibuat atau direname dengan awalan AtoZ_, direktori dan isinya ter-encode Atbash. Jika diubah, akan tet-decode.
Untuk sementara, saya baru bisa membuat fungsi untuk mengubah string, bukan direktori, dengan sandi Atbash

### Soal 2
a. Jika direktori dibuat dengan awalan RX_, direktori dan isinya tersebut diencode pertama Atbash, lalu diikuti dengan ROT13
Sandi ROT13 intinya hanya memindahkan masing-masing char 13 huruf ke arah kanan dari susunan alphabet (Atau ASCII). Sama seperti nomor 1, baru bisa membuat fungsinya saja
b. Jika direktori di-rename dengan awalan RX_, direktori dan isinya diencode pertama dengan Atbash, lalu dengan Vigenere dengan key "SISOP"
Sandi Viginere mengubah masing-masing huruf ke arah kanan sebanyak sandi angka dari masing-masing huruf di key satu per satu dari kiri, lalu dikurangi 1. Masih baru bisa membuat fungsinya
c. Jika direktori di-rename dengan menghapuskan RX_, direktori kembali menjadi aslinya, tergantung jenis encodingnya
Masih belum tahu caranya membedakan jenis encodingnya. Fungsi yang dibuat baru bisa mengembalikan sandi ROT13, tapi bukan Vigenere
d. Setiap encode, akan tercatap dalam log file
e. File-file dalam direktori dipecah menjadi 1024 bytes, tapi jika diakses, akan menjadi normal

### Soal 3
Jika ada direktori dibuat atau di-rename dengan awalan A_is_a_, maka nama direktori tersebut akan menjadi direktori spesial. Jika dihapus A_is_a-nya, maka direktori tersebu menjadi normal. Semua folder di-dalamnya akan di-lowercase-kan dan ditambahkan sebuah angka yang menjadi hasil desimal dari biner dari huruf-huruf yang kapital
Baru bisa membuat fungsi untuk mengubah nama file menjadi lowercase dan menambah angka di belakangnya

### Masalah yang dihadapi
1. Kurangnya referensi dari internet dan pemahamannya
2. Kurangnya pemahaman dari isi-isi dari fungsi-fungsi fuse
3. Sulitnya membaca, oleh manusia bukan laptop, hasil dari file dan directory yang dibaca oleh fungsi-fungsi fuse
