#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define INPUT_FILE "dane.txt"
#define OUTPUT_FILE1 "test_output1.txt"
#define OUTPUT_FILE2 "test_output2.txt"
#define COMMAND "Grafy.exe < " INPUT_FILE

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


//funkcja testująca tryb losowego generowania grafu
void test_random_mode(int verticies) {
    printf("Test funkcjonalności generowania grafu poprzez algorytm losowy\n");
    FILE *input = fopen(INPUT_FILE, "w");
    if(!input) {
        printf("Błąd nie można otworzyc pliku wejsciowego\n"); 
        return;
    }
    fprintf(input,"%s\n1\n%d\n", OUTPUT_FILE1, verticies);
    fclose(input);

    printf("Rozpoczęcie działania programu testowanego\n");
    system(COMMAND);
    printf("Zakończenie działania programu testowanego\n");

    if(file_exist(OUTPUT_FILE1) == 1) {
        printf("Test niepowodzenie: Plik wyjściowy nie został utworzony\n");
    } else {
        printf("Test trybu losowego zakończony sukcesem\n");
    }
}

//funkcja testująca tryb generowania grafu poprzez AI
void test_ai_mode(const char *description) {
    printf("Test funkcjonalności generowania grafu poprzez AI\n");
    FILE *input = fopen(INPUT_FILE, "w");
    if(!input) {
        printf("Błąd nie można otworzyc pliku wejsciowego\n"); 
        return;
    }
    fprintf(input,"%s\n2\n%s\n", OUTPUT_FILE2, description);
    fclose(input);

    printf("Rozpoczęcie działania programu testowanego\n");
    system(COMMAND);
    printf("Zakończenie działania programu testowanego\n");

    if(file_exist(OUTPUT_FILE2) == 1) {
        printf("Test niepowodzenie: Plik wyjściowy nie został utworzony\n");
    } else {
        printf("Test trybu ai zakończony sukcesem\n");
    }
}

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    printf("Uruchamiane testów...\n");
    test_random_mode(5);
    test_ai_mode("Create a graph with 5 nodes");
    return 0;
}