#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max_size 100

int bf_penukaran_uang(int nilai_coin[], int length, int jumlah, int coin_digunakan[]){
    int minCoin[jumlah + 1];
    for (int i = 0; i <= jumlah; i++){
        minCoin[i] = INT_MAX;
    }

    minCoin[0] = 0;

    for (int i = 0; i <= jumlah; i++){
        for (int j = 0; j < length; j++){
            if (nilai_coin[j] <= i && minCoin[i - nilai_coin[j]] != INT_MAX && minCoin[i - nilai_coin[j]] + 1 < minCoin[i]){
                minCoin[i] = minCoin[i - nilai_coin[j]] + 1;
            }
        }   
    }

    if (minCoin[jumlah] == INT_MAX){
        return -1;
    }

    int sisa_koin = jumlah;
    while (sisa_koin > 0){
        for (int k = 0; k < length; k++){
            if (nilai_coin[k] <= sisa_koin && minCoin[sisa_koin - nilai_coin[k]] + 1 == minCoin[sisa_koin]){
                coin_digunakan[k]++;
                sisa_koin -= nilai_coin[k];
                break;
            }
        }
    }
    
    return minCoin[jumlah];
}

int greedy_penukaran_uang(){

}

void penukaran_uang(){
    int method, coin, nilai_tukar, hasilBF;
    int nilai_coin[max_size];
    printf("Pilih metode: \n");
    printf("1. Brute Force\n");
    printf("2. Greedy\n");
    printf("Silahkan pilih metode: ");
    scanf("%d", &method);
    system("cls");
    printf("Masukkan jumlah koin: ");
    scanf("%d", &coin);
    printf("Masukkan nilai koin: ");
    for (int i = 1; i <= coin; i++){
        scanf("%d", &nilai_coin[i]);
    }
    printf("Masukkan jumlah penukaran: ");
    scanf("%d", &nilai_tukar);
    int length = coin + 1;
    int coin_digunakan[length];
    for (int i = 0; i < length; i++){
        coin_digunakan[i] = 0;
    }
    if (method == 1){
        hasilBF = bf_penukaran_uang(nilai_coin, length, nilai_tukar, coin_digunakan);
        if (hasilBF == -1){
            printf("Tidak ada kombinasi");
        } else{
            printf("Hasil minimal jumlah coin adalah %d\n", hasilBF);
            for (int i = 0; i < length-1; i++){
                printf("%d coin bernilai %d\n", nilai_coin[i+1], coin_digunakan[i+1]);
            }   
        }
        system("pause");
        system("cls");
    } else if(method == 2){
        
    }
    
}

void penjadwalan(){
    int method;
    printf("Pilih metode: \n");
    printf("1. Brute Force\n");
    printf("2. Greedy\n");
    printf("Silahkan pilih metode: ");
    scanf("%d", &method);
}

void knapsack_problem(){
    int method;
    printf("Pilih metode: \n");
    printf("1. Brute Force\n");
    printf("2. Greedy\n");
    printf("Silahkan pilih metode: ");
    scanf("%d", &method);
}

void pilihan(int input){
    switch (input)
    {
    case 1:
        penukaran_uang();
        break;
    case 2:
        penjadwalan();
        break;
    case 3:
        knapsack_problem();
        break;
    default:
        break;
    }
}

void menu(){
    int input_menu;
    char buffer[100];
    do{
        printf("================================\n");
        printf("Pilih menu dibawah ini: \n");
        printf("================================\n");
        printf("1. Penukaran uang\n");
        printf("2. Penjadwalan\n");
        printf("3. Knapsack Problem\n");
        printf("4. Keluar\n");
        printf("\n");
        printf("Silahkan pilih menu: ");
        scanf("%d", &input_menu);
        if (input_menu != 1){
            if (input_menu > 4 || input_menu <= 0){
            system("cls");
            printf("Masukkan menu yang valid (1-4)\n");
            fgets(buffer, sizeof(buffer), stdin);
            system("pause");
            }
        }
        system("cls");
        pilihan(input_menu);
    }while (input_menu != 4);
}

int main(){
    menu();
}