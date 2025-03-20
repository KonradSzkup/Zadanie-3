#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

#define INPUT_FILE "dane.txt"
#define OUTPUT_FILE1 "test_output_random"
#define OUTPUT_FILE2 "test_output_AI"
#define COMMAND "Grafy.exe < " INPUT_FILE
#define COMMAND_NON_FILE "Grafy.exe"

//funkcja sprawdzająca czy plik istnieje
int file_exist(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file) {
        return 1;
    } else {
        fclose(file);
        return 0;
    }
}
//funkcja sprawdzajaca poprawność danych wyjściowych
int validate_graph_format(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file) return 1;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strchr(line, ':') == NULL) { // Każda linia powinna zawierać ':'
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Funkcja dodająca sufiks do nazwy pliku
void append_suffix(char *new_name, const char *original, const char *suffix) {
    snprintf(new_name, 256, "%s%s%s", original, suffix, ".txt");
}

//funkcja testująca tryb losowego generowania grafu
void test_random_mode( int verticies, const char *suffix) {
    printf("Test funkcjonalności generowania grafu poprzez algorytm losowy\n");

    char modified_output[512];
    append_suffix(modified_output, OUTPUT_FILE1, suffix);

    FILE *input = fopen(INPUT_FILE, "w");
    if (!input) {
        printf("Błąd: nie można otworzyć pliku wejściowego\n"); 
        return;
    }
    fprintf(input, "%s\n1\n%d\n", modified_output, verticies);
    fclose(input);

    printf("Rozpoczęcie działania programu testowanego w %s\n", modified_output);

    system(COMMAND);

    printf("Zakończenie działania programu testowanego\n");

    if (file_exist(modified_output) == 1) {
        printf("Test niepowodzenie: Plik wyjściowy nie został utworzony\n");
    } else {
        printf("Test trybu losowego zakończony sukcesem\n");
    }
}

//funkcja testująca tryb losowego generowania grafu bez danych
void test_random_mode_non_data( int verticies, const char *suffix) {
    printf("Test funkcjonalności generowania grafu poprzez algorytm losowy\n");

    char modified_output[512];
    append_suffix(modified_output, OUTPUT_FILE1, suffix);

    FILE *input = fopen(INPUT_FILE, "w");
    if (!input) {
        printf("Błąd: nie można otworzyć pliku wejściowego\n"); 
        return;
    }
    fprintf(input, "%s\n%d\n%s",modified_output, 2, "");
    fclose(input);

    printf("Rozpoczęcie działania programu testowanego w %s\n", modified_output);

    system(COMMAND);

    printf("Zakończenie działania programu testowanego\n");

    if (file_exist(modified_output) == 1) {
        printf("Test niepowodzenie: Plik wyjściowy nie został utworzony\n");
    } else {
        printf("Test trybu losowego zakończony sukcesem\n");
    }
}

//funkcja testująca tryb losowego generowania grafu bez danych
void test_random_mode_non_file() { 

    printf("Test funkcjonalności generowania grafu poprzez algorytm losowy\n");

    printf("Rozpoczęcie działania programu testowanego\n");

    system(COMMAND_NON_FILE);

    printf("Zakończenie działania programu testowanego\n");
}

//funkcja testująca tryb generowania grafu poprzez AI
void test_ai_mode(const char *description, const char *suffix ) {
    printf("Test funkcjonalności generowania grafu poprzez AI\n");

    char modified_output[512];
    append_suffix(modified_output, OUTPUT_FILE2, suffix);

    FILE *input = fopen(INPUT_FILE, "w");
    if(!input) {
        printf("Błąd nie można otworzyc pliku wejsciowego\n"); 
        return;
    }
    fprintf(input,"%s\n2\n%s\n", modified_output, description);
    fclose(input);

    printf("Rozpoczęcie działania programu testowanego\n");
    system(COMMAND);
    printf("Zakończenie działania programu testowanego\n");

    if(file_exist(modified_output) == 1) {
        printf("Test niepowodzenie: Plik wyjściowy nie został utworzony\n");
    } else {
        printf("Test trybu ai zakończony sukcesem\n");
    }
}

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    printf("Uruchamiane testów...\n");
    
    int choice;
    bool flaga = false;
    while(!flaga){
        printf("\n-----------------------------------------------------------------------------\n");
        printf("\nWybierz test do uruchomienia:\n");
        printf("0 - koniec programu\n");
        printf("15 - Test losowego generowania grafu z liczba dodatnia\n");
        printf("10 - Test losowego generowania grafu z zerem\n");
        printf("19 - Test losowego generowania grafu z maks int\n");
        printf("-15 - Test losowego generowania grafu z liczba ujemna\n");
        printf("25 - Test generowania grafu poprzez AI z liczba dodatnia\n");
        printf("20 - Test generowania grafu poprzez AI z zerem\n");
        printf("-25 - Test generowania grafu poprzez AI z liczba ujemna\n");
        printf("29 - Test generowania grafu poprzez AI z 100000\n");
        printf("21 - Test generowania grafu poprzez AI z innym poleceniem\n");
        printf("30 - Test losowego generowania grafu bez polecenia\n");
        printf("40 - Test programu bez pliku\n");
        scanf("%d", &choice);

        switch (choice) {
            case 15:
                test_random_mode(7, "_five");
                break;
            case 10:
                test_random_mode(0, "_zero");
                break;
            case 19:
                test_random_mode(INT_MAX, "_max");
                break;
            case -15:
                test_random_mode(-5, "_minus");
                break;
            case 25:
                test_ai_mode("Create a graph with 5 nodes", "_five");
                break;
            case 20:
                test_ai_mode("Create a graph with 0 nodes", "_zero");
                break;
            case -25:
                test_ai_mode("Create a graph with -5 nodes", "_minus");
                break;
            case 29:
                test_ai_mode("Create a graph with 100000 nodes", "_max");
                break;
            case 21:
                test_ai_mode("ifaufweh", "_twor");
                break;
            case 30:
                test_random_mode_non_data(6, "_non_data");
                break;
            case 40:
            test_random_mode_non_file();
                break;
            case 0:
                flaga = true;
                printf("Closing...\n");
                break;
            default:
                printf("Nieprawidłowy wybór\n");
        }
    }

    return 0;
}