
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long long timestamp;
    char sensor[20];
    char valor[20];
} Leitura;

void bubbleSort(Leitura *v, int n) {
    Leitura temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (v[j].timestamp > v[j+1].timestamp) {
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    FILE *arq = fopen(argv[1], "r");
    if (!arq) return 1;

    Leitura *v = NULL;
    int total = 0;
    char sensores[100][20];
    int qtd_sensores = 0;

    unsigned long long ts;
    char id[20], val[20];

    while (fscanf(arq, "%llu %s %s", &ts, id, val) == 3) {
        v = realloc(v, (total + 1) * sizeof(Leitura));
        v[total].timestamp = ts;
        strcpy(v[total].sensor, id);
        strcpy(v[total].valor, val);
        total++;

        int existe = 0;
        for (int i = 0; i < qtd_sensores; i++) {
            if (strcmp(sensores[i], id) == 0) existe = 1;
        }
        if (!existe) {
            strcpy(sensores[qtd_sensores], id);
            qtd_sensores++;
        }
    }
    fclose(arq);

    for (int i = 0; i < qtd_sensores; i++) {
        Leitura *filtro = NULL;
        int cont = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(v[j].sensor, sensores[i]) == 0) {
                filtro = realloc(filtro, (cont + 1) * sizeof(Leitura));
                filtro[cont] = v[j];
                cont++;
            }
        }
        bubbleSort(filtro, cont);

        char nome_out[30];
        sprintf(nome_out, "%s.txt", sensores[i]);
        FILE *out = fopen(nome_out, "w");
        for (int j = 0; j < cont; j++) {
            fprintf(out, "%llu %s %s\n", filtro[j].timestamp, filtro[j].sensor, filtro[j].valor);
        }
        fclose(out);
        free(filtro);
    }
    free(v);
    return 0;
}
