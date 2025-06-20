
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    unsigned long long timestamp;
    char sensor[20];
    char valor[20];
} Leitura;

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

int busca_binaria(Leitura *v, int n, unsigned long long alvo) {
    int ini = 0, fim = n - 1;
    int mais_prox = 0;
    unsigned long long menor_dif = -1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        unsigned long long dif = v[meio].timestamp > alvo ? v[meio].timestamp - alvo : alvo - v[meio].timestamp;
        if (dif < menor_dif) {
            menor_dif = dif;
            mais_prox = meio;
        }
        if (v[meio].timestamp < alvo) ini = meio + 1;
        else fim = meio - 1;
    }
    return mais_prox;
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    char arquivo[30];
    sprintf(arquivo, "%s.txt", argv[1]);
    FILE *arq = fopen(arquivo, "r");
    if (!arq) return 1;

    Leitura *v = NULL;
    int total = 0;
    unsigned long long ts;
    char id[20], val[20];

    while (fscanf(arq, "%llu %s %s", &ts, id, val) == 3) {
        v = realloc(v, (total + 1) * sizeof(Leitura));
        v[total].timestamp = ts;
        strcpy(v[total].sensor, id);
        strcpy(v[total].valor, val);
        total++;
    }
    fclose(arq);

    int d, m, a, h, min, s;
    sscanf(argv[2], "%d %d %d %d %d %d", &d, &m, &a, &h, &min, &s);
    unsigned long long alvo = gerarTimestamp(d, m, a, h, min, s);

    int pos = busca_binaria(v, total, alvo);
    printf("%llu %s %s\n", v[pos].timestamp, v[pos].sensor, v[pos].valor);
    free(v);
    return 0;
}
