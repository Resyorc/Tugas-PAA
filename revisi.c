#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max_size 100

int bf_penukaran_uang(){

}

int greedy_penukaran_uang(){
}

void penukaran_uang(){
    int method, coin, nilai_tukar, hasilBF, hasilGreedy;
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