//library import
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//jumlah max data 
#define N 100

//informasi club
struct skorSementara{
	char name[31];
	int win;
	int par;
	int lost;
	int skor;
}data[N],sim;
//buat nyimpen jumlah data yang berhasil diread dari file database.txt
int n;
//buat variabel skor
int menang;
int kalah;
int seri;
int a=0;
int b;
int jmlRealData=0;
int ind, temp;

//function declaration
void showMenu();
//void sort();
void scanData();
void updateStat();
void lihatDataPertandingan();
void ambilDataDiFile();
void sortKelasmen();
void viewSortKelasmen();
int search(char[]);


//program's code
//main function
int main(){

	//repetition agar program bisa terus berjalan hingga user memasukkan karakter selain di menu
	while(1){
		//tampilin menunya
		showMenu();
		
		//user input
		scanf("%d", &ind);
		getchar();
		printf("\n");
		
		//menentukan function yang akan dijalankan sesuai user input
		if(ind == 1){
			updateStat();
		}else if(ind == 2){
			lihatDataPertandingan();
		}else if(ind == 3){
			printf("--------Thankyou--------\n");	
			return 0;
		}else{
			printf("Masukan angka yang terdapat dalam pilihan\n\n");
		}
	}
}

//buat nampilin main menu
void showMenu(){
	printf("      Hasil Pertandiang Sepakbola     \n");
    printf("======================================\n");;
    printf(" 1. Tambah hasil pertandingan\n");
    printf(" 2. Lihat data pertandingan\n");
    printf(" 3. Exit\n");
    printf("=======================================\n");
    printf("Masukan pilihan: ");
}
	
void lihatDataPertandingan() {
	ambilDataDiFile();
	sortKelasmen();
	viewSortKelasmen();
	return;
}

void ambilDataDiFile() {
	//variabel
	int i = 0;
	//buka stream dengan mode read
	FILE* fp;
	fp = fopen("database.txt", "r");
	//output
	printf("----------Skor Sementara-----------\n");
	printf("No.|\t    Club   \t|W|P|L|Total Poin\n");

	if (fp == NULL) {
		printf("File cannot be found/opened!");
		exit(1);
	}
	//membaca isi file selama belum end of file.
	while (!feof(fp)) {
		fscanf(fp, "%[^|]|%d|%d|%d|%ld\n", &data[i].name, &data[i].win, &data[i].par, &data[i].lost, &data[i].skor);
		i++;
	}
	jmlRealData = i;
	printf("\n");
	//tutup stream
	fclose(fp);

	return;
}
void sortKelasmen() {
	skorSementara temp;
	for (int i = 0; i < jmlRealData; i++) {
		for (int j = i + 1; j < jmlRealData; j++) {
			if (data[j].skor > data[i].skor) {
				temp.lost = data[i].lost;
				strncpy(temp.name, data[i].name, 31);
				//temp.name = data[i].name;
				temp.par = data[i].par;
				temp.skor = data[i].skor;
				temp.win = data[i].win;
			
				data[i].lost = data[j].lost;
				strncpy(data[i].name, data[j].name, 31);
				//data[i].name = data[j].name;
				data[i].par = data[j].par;
				data[i].skor = data[j].skor;
				data[i].win = data[j].win;

				data[j].lost = temp.lost;
				strncpy(data[j].name, temp.name, 31);
				//data[j].name = temp.name;
				data[j].par = temp.par;
				data[j].skor = temp.skor;
				data[j].win = temp.win;

			}
		}
	}
	return;
}
void viewSortKelasmen() {
	int a = 1;
	for (int i = 0; i < jmlRealData; i++) {
		printf("%d. | %s\t\t|%d|%d|%d|%ld\n", a, data[i].name, data[i].win, data[i].par, data[i].lost, data[i].skor);
		a++;
	}
	printf("\n");
	return;
}


//buat baca data dari file database.txt
void scanData(){
	//variables
	int i = 0;
	//create buffer + open file for read
	FILE *fp;
	fp = fopen("database.txt", "r");
	
	//read data from database.txt
	while(!feof(fp)){
		//kode utama untuk baca data
		fscanf(fp, "%[^|]|%d|%d|%d|%ld\n", &data[i].name, &data[i].win,&data[i].par,&data[i].lost,&data[i].skor);
		
		//biar tau ada berapa data di dalam file database.txt
		i++; n = i;
	}
	
	//close buffer + file
	fclose(fp);
}

int search(char key[31]){
	/*pake algoritma linear search*/
	//variables
	int i;
	
	//searching
	for(i = 0; i < n; i++){
		if(strcmp(key, data[i].name) == 0){
			return i;
		}
	}
	
	//kalo datanya kagak ada sama sekali
	return -1;
}

//buat tambah saldo ke akun
void updateStat(){
	char dep[31]; /*ini buat keyword buat mastiin kalo user mau menambahkan hasil pertandingan ke data club yang emang ada di database.txt, panjangnya disamain sama nama club*/
	int ind; /*buat nampung nilai return dari function search()*/
	unsigned long skorTambahan; /*jumlah data permainan yang ingin di tambahkan*/
	int i;
	int temp;
	int menang;
	int kalah;
	int seri;
	
	//buat baca data dari database.txt sekalian nentuin jumlah datanya
	scanData();
	//informasi
	printf("Nama Club:\n");
	printf(" 1. Taynew\n 2. Ohmnon\n 3. Drakefrank\n 4. Offgun\n 5. Singkit\n 6. Seventeen\n 7. Arohaa\n 8. Melody\n 9. Monbebe\n\n");
	//user input
	printf("Masukkan Nama Club: ");
	scanf("%s", &dep);
	printf("\n");
	getchar();
	//memastikan kalo akun tujuan deposit memang ada
	ind = search(dep);
	
	//kondisi berdasarkan hasil return search()
	if(ind == -1){
		//message
		printf("<< Club tidak ditemukan. >>\n\n");
		
		//reset nilai n ke 0 untuk aksi yang bakal dipilih user selanjutnya dan exit fungsi
		n = 0; return;
		
	} else {
		//user input
		printf("Masukkan Info Terbaru\n");
		printf("Menang: ");
		scanf("%d",&menang);
		data[ind].win += menang;
		getchar();
		printf("Kalah: ");
		scanf("%d",&kalah);
		data[ind].lost += kalah;
		getchar();
		printf("Seri: ");
		scanf("%d",&seri);
		data[ind].par += seri;
		getchar();
		temp = (menang*3)+seri;
		data[ind].skor += temp;
		printf("\n");
		
	
		//manipulasi data
		
		//manipulasi konten database.txt (tulis ulang/overwrite)
		FILE *fp;
		fp = fopen("database.txt", "w");
		
		for(i = 0; i < n; i++){
			fprintf(fp, "%s|%d|%d|%d|%ld\n", data[i].name, data[i].win,data[i].par,data[i].lost,data[i].skor);
		}
		
		fclose(fp);
		
		//message
		printf("<< Skor Club %s sekarang: %ld >>\n\n",data[ind].name, data[ind].skor);
		
		//reset nilai n ke 0 untuk aksi yang bakal dipilih user selanjutnya dan exit fungsi
		n = 0;
	}
}
