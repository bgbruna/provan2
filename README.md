# provan2
Atividade avaliativa individual de estrutura de dados
Sistema de Consulta de Sensores Industriais

Este pacote contém três programas em C para organização, consulta e geração de dados de sensores de uma planta industrial.

---
Programas inclusos

1. Organização dos Dados (atv1.c)

Função:  
Lê um arquivo de entrada (formato bruto) com várias leituras de sensores e separa os dados em arquivos individuais por sensor, ordenados por timestamp usando Bubble Sort.

Uso:

Compilar:

gcc atv1.c -o atv1

Executar:
./atv1 entrada.txt

> Onde `entrada.txt` é o arquivo de entrada com as leituras no formato:

<TIMESTAMP> <ID_SENSOR> <VALOR>

Saída: Um arquivo para cada sensor, por exemplo: `TEMP.txt`, `PRES.txt`, etc.

---
2. Consulta por Instante (atv2.c)

Função:
Realiza uma busca binária em um arquivo de sensor (ex: TEMP.txt) para encontrar a leitura mais próxima de um instante de tempo específico.

Uso:

Compilar:

gcc atv2.c -o atv2

Executar:

./atv2 NOME_SENSOR "dd mm aaaa hh mm ss"

Exemplo:

./atv2 TEMP "10 06 2025 12 00 00"

> Isso busca no arquivo `TEMP.txt` a leitura mais próxima de 10/06/2025 às 12h00m00s.

---
3. Geração de Arquivo de Teste (atv3.c)

Função:  
Gera um arquivo de teste chamado `entrada.txt` com 2000 leituras aleatórias para cada sensor, dentro de um intervalo de datas informado.

Uso:

Compilar:

gcc atv3.c -o atv3

Executar:

./atv3 "dd mm aaaa hh mm ss" "dd mm aaaa hh mm ss" SENSOR1 TIPO1 SENSOR2 TIPO2 ...


Exemplo:


./atv3 "10 06 2025 00 00 00" "10 06 2025 23 59 59" TEMP float PRES int UMID bool


> Isso gera 2000 registros para cada sensor: TEMP, PRES e UMID, com tipos de dados `float`, `int` e `bool` respectivamente.

---
