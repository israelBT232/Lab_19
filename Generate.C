#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate.h"
#define RANDMAX 100

int generateMatrixFile1() {
    FILE *input_file;
    int n, i, j;

    // Открыть файл для записи
    input_file = fopen("input.txt", "w");
    if (input_file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    // Сгенерировать случайное число для порядка матрицы
    srand(time(0));
    n = rand() % 5 + 2; // Генерируем число от 2 до 6

    // Записать порядок матрицы в файл
    fprintf(input_file, "%d\n", n);

    // Записать элементы матрицы в файл
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(input_file, "%d ", rand() % 10); // Генерируем случайные элементы от 0 до 9
        }
        fprintf(input_file, "\n");
    }

    // Закрыть файл
    fclose(input_file);

    return EXIT_SUCCESS;
}


int generateMatrixFile2() {
    FILE *outputFile;

    // Открываем файл для записи
    outputFile = fopen("floating_numbers.txt", "w");

    // Проверяем, успешно ли открыли файл
    if (outputFile == NULL) {
        printf("Ошибка открытия файла для записи.");
        return 1;
    }

    // Генерируем и записываем случайные числа в файл
    srand(time(NULL)); // Инициализируем генератор случайных чисел
    for (int i = 0; i < 10; i++) {
        float num = (float)rand() / (float)(RANDMAX) * 100; // Генерируем случайное число от 0 до 100
        fprintf(outputFile, "%.2f\n", num); // Записываем число с двумя знаками после запятой
    }

    // Закрываем файл
    fclose(outputFile);

    return 0;
}
