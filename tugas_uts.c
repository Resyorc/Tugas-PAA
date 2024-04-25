#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define max_size 100

struct Penukaran {
    int nilaiTukar;
    int* nilaiKoin;
};

struct Penjadwalan {
    char name[20];
    int durasi;
    int tunggu;
};

struct Knapsack {
    int weight;
    int profit;
    double density;
};
int minKoin = INT_MAX;
int *minKoinKombinasi;

int minTunggu = INT_MAX;
struct Penjadwalan bestOrder[100];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi Brute Force Coin Exchange
void rekursif(int index, int jumlah, int n, int *count, struct Penukaran *pnkr){
    if (jumlah == 0){
        int hasil = 0;
        for (int i = 0; i < n; i++){
            hasil += count[i];
        }
        if (hasil < minKoin){
            minKoin = hasil;
            for (int i = 0; i < n; i++){
                minKoinKombinasi[i] = count[i];
            }
        }
        return;
    }
    if (index == n || jumlah < 0){
        return;
    }
    for (int i = 0; i <= jumlah / pnkr->nilaiKoin[index]; i++){
        count[index] = i;
        rekursif(index + 1, jumlah - pnkr->nilaiKoin[index] * i, n, count, pnkr);
    }
    count[index] = 0;
}

void bf_penukaran_koin(struct Penukaran *pnkr, int n){
    int *jumlahKoin = malloc(n * sizeof(int));
    minKoinKombinasi = malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++){
        jumlahKoin[i] = 0;
        minKoinKombinasi[i] = 0;
    }

    rekursif(0, pnkr->nilaiTukar, n, jumlahKoin, pnkr);
    if (minKoin == INT_MAX){
        printf("Tidak ada kombinasi koin yang mungkin untuk nilai %d\n", pnkr->nilaiTukar);
    } else {
        printf("Hasil minimal dari jumlah koin %d adalah %d\n", pnkr->nilaiTukar, minKoin);
        for (int i = 0; i < n; i++){
            printf("%d koin bernilai %d\n", minKoinKombinasi[i], pnkr->nilaiKoin[i]);
        }
        printf("\n");
    }

    free(jumlahKoin);
    free(minKoinKombinasi);
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void greedy_penukaran_koin(struct Penukaran *pnkr, int n){
    int totalKoin = 0;
    minKoinKombinasi = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        minKoinKombinasi[i] = 0;
    }

    int jumlahKoin = pnkr->nilaiTukar;
    for (int i = n - 1; i >= 0; i--) {
        while (jumlahKoin >= pnkr->nilaiKoin[i]) {
            minKoinKombinasi[i]++;
            jumlahKoin -= pnkr->nilaiKoin[i];
            totalKoin++;
        }
    }

    if (jumlahKoin != 0) {
        printf("Tidak ada kombinasi dengan jumlah coin %d\n", pnkr->nilaiTukar);
    } else {
        printf("Hasil minimal jumlah coin dari %d adalah %d\n", pnkr->nilaiTukar, totalKoin);
        for (int i = 0; i < n; i++) {
            printf("%d koin bernilai %d\n", minKoinKombinasi[i], pnkr->nilaiKoin[i]);
        }
    }
    free(minKoinKombinasi);
}

void penukaran_uang() {
    char buffer[100];
    int method, koin;
    struct Penukaran pnkr;
    do
    {
        printf("Pilih metode: \n");
        printf("1. Brute Force\n");
        printf("2. Greedy\n");
        printf("Silahkan pilih metode: ");
        scanf("%d", &method);
        if (method != 1)
        {
            if (method > 2 || method <= 0)
            {
                system("cls");
                printf("Masukkan menu yang valid (1-2)\n");
                fgets(buffer, sizeof(buffer), stdin);
                system("pause");
                system("cls");
            }
        }
    } while (method != 1 && method != 2);
    system("cls");
    printf("Masukkan jumlah koin: ");
    scanf("%d", &koin);
    printf("Masukkan nilai koin: ");
    int length = koin;
    pnkr.nilaiKoin = malloc(length * sizeof(int));
    for (int i = 0; i < koin; i++)
    {
        scanf("%d", &pnkr.nilaiKoin[i]);
    }
    printf("Masukkan jumlah uang yang perlu dibayar: ");
    scanf("%d", &pnkr.nilaiTukar);
    switch (method)
    {
    case 1:
        bf_penukaran_koin(&pnkr, length);
        break;

    case 2:
        bubbleSort(pnkr.nilaiKoin, length);
        greedy_penukaran_koin(&pnkr, length);
        break;
    }
    free(pnkr.nilaiKoin);
}

void swapPenjadwalan(struct Penjadwalan* a, struct Penjadwalan* b) {
    struct Penjadwalan temp = *a;
    *a = *b;
    *b = temp;
}

void bf_penjadwalan(struct Penjadwalan pnjd[], int n, int idx, int currentTime) {
    if (idx == n) {
        int totalWaitTime = 0;
        for (int i = 1; i < n; i++) {
            totalWaitTime += pnjd[i].tunggu;
        }
        if (totalWaitTime < minTunggu) {
            minTunggu = totalWaitTime;
            memcpy(bestOrder, pnjd, sizeof(struct Penjadwalan) * n);
        }
        return;
    }
    for (int i = idx; i < n; i++) {
        swapPenjadwalan(&pnjd[i], &pnjd[idx]);
        if (idx > 0) {
            pnjd[idx].tunggu = pnjd[idx-1].tunggu + pnjd[idx-1].durasi;
        } else {
            pnjd[idx].tunggu = 0;
        }
        bf_penjadwalan(pnjd, n, idx + 1, currentTime + pnjd[idx].durasi);
        swapPenjadwalan(&pnjd[i], &pnjd[idx]);
    }
    
}

void display(int n) {
    printf("Optimal Task Order Based on Minimum Total Wait Time:\n");
    for (int i = 0; i < ; i++) {
        printf("%s\n", bestOrder[i].name);
    }
    printf("Total Minimum Wait Time: %d\n", minTunggu);
}

void greedy_penjadwalan(struct Penjadwalan pjdw[], int length)
{
    // Bubble sort to 4sort tasks by duration in ascending order
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (pjdw[j].durasi > pjdw[j + 1].durasi)
            {
                // Swap tasks if they are out of order
                struct Penjadwalan temp = pjdw[j];
                pjdw[j] = pjdw[j + 1];
                pjdw[j + 1] = temp;
            }
        }
    }

    int waktuSekarang = 0;
    int totalWaktuTunggu = 0;
    for (int i = 0; i < length; i++)
    {
        int waktuMulai = waktuSekarang;
        int waktuSelesai = waktuSekarang + pjdw[i].durasi;
        int waktuTunggu = waktuMulai; // Calculate waiting time correctly
        waktuSekarang = waktuSelesai;
        printf("%s\n", pjdw[i].name);
        if (i == length - 1)
        {
            totalWaktuTunggu += waktuTunggu;
            break;
        }
    }
    printf("Waktu tunggu total: %d\n", totalWaktuTunggu);
}


void penjadwalan() {
int method, totalTugas;
    char buffer[100];
    do
    {
        printf("Pilih metode: \n");
        printf("1. Brute Force\n");
        printf("2. Greedy\n");
        printf("Silahkan pilih metode: ");
        scanf("%d", &method);
        if (method != 1)
        {
            if (method > 2 || method <= 0)
            {
                system("cls");
                printf("Masukkan menu yang valid (1-2)\n");
                fgets(buffer, sizeof(buffer), stdin);
                system("pause");
                system("cls");
            }
        }
    } while (method != 1 && method != 2);
    printf("Masukkan jumlah tugas: ");
    scanf("%d", &totalTugas);
    struct Penjadwalan pjdw[totalTugas]; // Mendeklarasikan array struktur dengan ukuran yang cukup
    printf("Masukkan nama tugas dan durasi tugas: ");
    for (int i = 0; i < totalTugas; i++)
    {
        scanf("%s %d", pjdw[i].name, &pjdw[i].durasi);
    }
    int length = totalTugas;
    switch (method)
    {
    case 1:
        bf_penjadwalan(pjdw, length, 0, 0);
        display(length);
        break;

    case 2:
        greedy_penjadwalan(pjdw, length);
        break;
    }
}

void bf_knapsack(struct Knapsack knpk[], int n, int kapasitas) {
    int maxProfit = INT_MIN;
    int bestCombination[n];  // Array untuk menyimpan kombinasi terbaik

    for (int i = 0; i < (1 << n); i++) {
        int currentWeight = 0, currentProfit = 0, currentCombination[n];
        
        for (int j = 0; j < n; j++) {
            currentCombination[j] = 0;  // Reset array kombinasi saat ini
            if (i & (1 << j)) {
                currentWeight += knpk[j].weight;
                currentProfit += knpk[j].profit;
                currentCombination[j] = 1;  // Tandai sebagai bagian dari kombinasi saat ini
            }
        }
        
        if (currentWeight <= kapasitas && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            memcpy(bestCombination, currentCombination, sizeof(bestCombination));  // Simpan kombinasi terbaik
        }
    }

    // Menampilkan hanya kombinasi terbaik
    printf("Optimal combination with maximum profit %d:\n", maxProfit);
    for (int i = 0; i < n; i++) {
        if (bestCombination[i]) {
            printf("Item %d: Weight = %d, Profit = %d\n", i + 1, knpk[i].weight, knpk[i].profit);
        }
    }
}

int compareProfit(const void *a, const void *b) {
    struct Knapsack *knpk1 = (struct Knapsack *)a;
    struct Knapsack *knpk2 = (struct Knapsack *)b;
    return (knpk2->profit - knpk1->profit); // Descending order by profit
}

void greedy_knapsack_profit(struct Knapsack knpk[], int n, int kapasitas) {
    // Mengurutkan knpk berdasarkan profit secara descending
    qsort(knpk, n, sizeof(struct Knapsack), compareProfit);

    int currentWeight = 0;
    int totalProfit = 0;
    
    // Greedy approach: select knpk with the highest profit until capacity is full
    for (int i = 0; i < n; i++) {
        if (currentWeight + knpk[i].weight <= kapasitas) {
            currentWeight += knpk[i].weight;
            totalProfit += knpk[i].profit;
            printf("Item %d: Weight = %d, Profit = %d\n", i + 1, knpk[i].weight, knpk[i].profit);
        }
    }

    printf("Total Profit: %d\n", totalProfit);
}

int compareWeight(const void *a, const void *b) {
    struct Knapsack *item1 = (struct Knapsack *)a;
    struct Knapsack *item2 = (struct Knapsack *)b;
    return (item1->weight - item2->weight); // Ascending order by weight
}

void greedy_knapsack_weight(struct Knapsack knpk[], int n, int kapasitas) {
    // Mengurutkan knpk berdasarkan weight secara ascending
    qsort(knpk, n, sizeof(struct Knapsack), compareWeight);

    int currentWeight = 0;
    int totalProfit = 0;
    printf("Selected knpk (greedy by lightest weight):\n");
    
    // Greedy approach: select knpk with the lightest weight until capacity is full
    for (int i = 0; i < n; i++) {
        if (currentWeight + knpk[i].weight <= kapasitas) {
            currentWeight += knpk[i].weight;
            totalProfit += knpk[i].profit;
            printf("Item %d: Weight = %d, Profit = %d\n", i + 1, knpk[i].weight, knpk[i].profit);
        }
    }

    printf("Total Profit: %d\n", totalProfit);
}

int compareDensity(const void *a, const void *b) {
    struct Knapsack *item1 = (struct Knapsack *)a;
    struct Knapsack *item2 = (struct Knapsack *)b;
    // Descending order by density
    if (item2->density > item1->density) return 1;
    if (item2->density < item1->density) return -1;
    return 0;
}

void greedy_knapsack_density(struct Knapsack knpk[], int n, int kapasitas) {
    // Menghitung density untuk setiap item
    for (int i = 0; i < n; i++) {
        knpk[i].density = (double)knpk[i].profit / knpk[i].weight;
    }

    // Mengurutkan knpk berdasarkan density secara descending
    qsort(knpk, n, sizeof(struct Knapsack), compareDensity);

    int currentWeight = 0;
    int totalProfit = 0;
    printf("Selected knpk (greedy by highest profit density):\n");
    
    // Greedy approach: select knpk with the highest density until capacity is full
    for (int i = 0; i < n; i++) {
        if (currentWeight + knpk[i].weight <= kapasitas) {
            currentWeight += knpk[i].weight;
            totalProfit += knpk[i].profit;
            printf("Item %d: Weight = %d, Profit = %d, Density = %.2f\n", 
                   i + 1, knpk[i].weight, knpk[i].profit, knpk[i].density);
        }
    }

    printf("Total Profit: %d\n", totalProfit);
}

void knapsack_problem() {
    struct Knapsack knpk[max_size];
    int method, kapasitas, n;
    printf("Pilih metode: \n");
    printf("1. Brute Force\n");
    printf("2. Greedy dengan Profit\n");
    printf("3. Greedy dengan Weight\n");
    printf("4. Greedy dengan Density\n");
    printf("Silahkan pilih metode: ");
    scanf("%d", &method);
    printf("Masukkan kapasitas tas: ");
    scanf("%d", &kapasitas);
    printf("Masukkan jumlah barang: ");
    scanf("%d", &n);
    printf("Masukkan harga barang dan berat barang: \n");
    for (int i = 0; i < n; i++){
        scanf("%d %d", &knpk[i].profit, &knpk[i].weight);
    }
    switch (method)
    {
    case 1:
        bf_knapsack(knpk, n, kapasitas);
        break;
    case 2:
        greedy_knapsack_profit(knpk, n, kapasitas);
        break;
    case 3:
        greedy_knapsack_weight(knpk, n, kapasitas);
        break;
    case 4:
        greedy_knapsack_density(knpk, n, kapasitas);
        break;
    }

}

void pilihan(int input) {
    switch (input) {
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

int main() {
    int input_menu;
    do {
        printf("================================\n");
        printf("Pilih menu dibawah ini: \n");
        printf("================================\n");
        printf("1. Penukaran uang\n");
        printf("2. Penjadwalan\n");
        printf("3. Knapsack Problem\n");
        printf("4. Keluar\n");
        printf("\n");
        printf("Silahkan pilih menu: ");
        if (scanf("%d", &input_menu) != 1) {
            printf("Masukkan angka yang valid.\n");
            while(fgetc(stdin) != '\n');
            continue;
        }
        
        if (input_menu < 1 || input_menu > 4) {
            printf("Masukkan menu yang valid (1-4)\n");
            system("pause");
        } else if (input_menu != 4) {
            system("cls");
            pilihan(input_menu);
            printf("Tekan tombol apapun untuk kembali ke menu...\n");
            system("pause");
            system("cls");
        }
    } while (input_menu != 4);

    return 0;
}
