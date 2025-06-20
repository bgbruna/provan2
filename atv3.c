
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long gerarTimestamp(int d, int m, int a, int h, int min, int s) {
    struct tm t = {0};
    t.tm_year = a - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d;
    t.tm_hour = h;
    t.tm_min = min;
    t.tm_sec = s;
    return (unsigned long long)mktime(&t);
}

void gerarValor(char *tipo, char *saida) {
    if (strcmp(tipo, "int") == 0) sprintf(saida, "%d", rand() % 1000);
    else if (strcmp(tipo, "float") == 0) sprintf(saida, "%.2f", ((float)rand() / RAND_MAX) * 100.0);
    else if (strcmp(tipo, "bool") == 0) strcpy(saida, rand() % 2 ? "true" : "false");
    else if (strcmp(tipo, "string") == 0) {
        int tam = rand() % 15 + 1;
        for (int i = 0; i < tam; i++) saida[i] = 'A' + rand() % 26;
        saida[tam] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5 || (argc - 3) % 2 != 0) return 1;

    int d1, m1, a1, h1, min1, s1;
    int d2, m2, a2, h2, min2, s2;
    sscanf(argv[1], "%d %d %d %d %d %d", &d1, &m1, &a1, &h1, &min1, &s1);
    sscanf(argv[2], "%d %d %d %d %d %d", &d2, &m2, &a2, &h2, &min2, &s2);

    unsigned long long inicio = gerarTimestamp(d1, m1, a1, h1, min1, s1);
    unsigned long long fim = gerarTimestamp(d2, m2, a2, h2, min2, s2);
    unsigned long long range = fim - inicio;

    FILE *out = fopen("entrada.txt", "w");
    if (!out) return 1;

    srand(time(NULL));

    for (int i = 3; i < argc; i += 2) {
        char *sensor = argv[i];
        char *tipo = argv[i + 1];
        for (int j = 0; j < 2000; j++) {
            unsigned long long ts = inicio + (rand() % (range + 1));
            char valor[20];
            gerarValor(tipo, valor);
            fprintf(out, "%llu %s %s\n", ts, sensor, valor);
        }
    }
    fclose(out);
    return 0;
}
