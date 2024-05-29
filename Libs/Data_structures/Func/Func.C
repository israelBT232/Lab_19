
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include <time.h>


int Task1() {
    FILE *input_file, *output_file;
    int n, i, j;
    int **matrix;

    // Открыть исходный файл
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        perror("Ошибка открытия исходного файла");
        return EXIT_FAILURE;
    }

    // Открыть выходной файл
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        perror("Ошибка открытия выходного файла");
        return EXIT_FAILURE;
    }

    // Считать порядок матрицы
    fscanf(input_file, "%d", &n);

    // Выделить память для матрицы
    matrix = (int **) malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matrix[i] = (int *) malloc(n * sizeof(int));
    }

    // Считать элементы матрицы по строкам
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(input_file, "%d", &matrix[i][j]);
        }
    }

    // Записать элементы матрицы по столбцам
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            fprintf(output_file, "%d ", matrix[i][j]);
        }
        fprintf(output_file, "\n");
    }
    // Вывести элементы матрицы на экран
    printf("Матрица после обработки:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Освободить память
    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    // Закрыть файлы
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}

int Task2() {
    // Открыть исходный файл
    FILE *in_file = fopen("floating_numbers.txt", "r");
    if (in_file == NULL) {
        perror("Ошибка открытия исходного файла");
        return EXIT_FAILURE;
    }

    // Открыть файл для записи
    FILE *out_file = fopen("fixed_numbers.txt", "w");
    if (out_file == NULL) {
        perror("Ошибка открытия файла для записи");
        return EXIT_FAILURE;
    }

    // Читать числа из исходного файла
    double number;
    while (fscanf(in_file, "%lf", &number) == 1) {
        // Преобразовать число в форму с плавающей точкой
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%.2e", number);

        // Записать число в файл для записи
        fprintf(out_file, "%s\n", buffer);
    }

    // Закрыть файлы
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}

int Task3() {

    // Открыть файл для записи
    FILE *file = fopen("expression.txt", "w");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    // Сгенерировать случайное арифметическое выражение
    int num1 = rand() % 10;
    int num2 = rand() % 10;
    char op = rand() % 2 == 0 ? '+' : '-';

    // Записать выражение в файл
    fprintf(file, "%d %c %d\n", num1, op, num2);

    // Вычислить значение выражения
    int result;
    if (op == '+') {
        result = num1 + num2;
    } else {
        result = num1 - num2;
    }

    // Дописать результат в конец файла
    fprintf(file, "%d\n", result);

    // Закрыть файл
    fclose(file);

    return EXIT_SUCCESS;
}

int Task4() {
    // Открываем входной и выходной файлы
    FILE *f_in = fopen("String_in", "r");
    if (f_in == NULL) {
        f_in = fopen("String_in", "w+"); // Создаем файл для чтения и записи
        if (f_in == NULL) {
            perror("fopen");
            return EXIT_FAILURE;
        }
    }

    FILE *f_out = fopen("String_out", "a");
    if (f_out == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Читаем входной файл построчно
    char line[1024];
    while (fgets(line, sizeof(line), f_in)) {
        // Разбиваем строку на слова
        char *word = strtok(line, " ");

        // Перебираем слова
        while (word != NULL) {
            // Проверяем, содержит ли слово заданную последовательность символов
            if (strstr(word, "sequence") != NULL) {
                // Если да, записываем слово в выходной файл
                fprintf(f_out, "%s\n", word);
            }

            // Переходим к следующему слову
            word = strtok(NULL, " ");
        }
    }
    // Закрываем файлы
    fclose(f_in);
    fclose(f_out);

    return EXIT_SUCCESS;
}


void Task5(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    char line[1000];

    while (fgets(line, sizeof(line), file)) {
        char longestWord[1000] = "";
        char tempWord[1000] = "";
        int longestLength = 0;

        char *token = strtok(line, " \n");

        while (token != NULL) {
            if (strlen(token) > longestLength) {
                strcpy(longestWord, token);
                longestLength = strlen(token);
            }
            token = strtok(NULL, " \n");
        }

        printf("%s\n", longestWord);
    }

    fclose(file);
}

// Структура для представления одного члена многочлена
typedef struct {
    int degree;           // Степень члена
    float coefficient;    // Коэффициент члена
} PolynomialTerm;

void Task6(float x, const char *filename) {
    FILE *file = fopen(filename, "rb+");

    if (file == NULL) {
        printf("Ошибка открытия файла.");
        return;
    }

    PolynomialTerm term; // Используем структуру PolynomialTerm для чтения и записи данных многочлена

    // Читаем структуру из файла
    while (fread(&term, sizeof(PolynomialTerm), 1, file) == 1) {
        // Если коэффициент при x в многочлене равен 0, то пропускаем запись
        if (!((int)(x + 0.5) == 0 && term.degree == 0 && term.coefficient == 0)) {
            fseek(file, -sizeof(PolynomialTerm), SEEK_CUR); // Переходим обратно на начало текущей структуры
            fwrite(&term, sizeof(PolynomialTerm), 1, file); // Записываем обновленную структуру обратно в файл
        }
    }

    // Усекаем файл до новой длины
    fflush(file);
    strcat((char *) fileno(file), (const char *) ftell(file));

    // Закрываем файл
    fclose(file);
}

void Task7(const char *filename, int i) {
    FILE *file = fopen(filename, "rb+"); // Открываем файл для чтения и записи

    if (file == NULL) {
        printf("Ошибка открытия файла.");
        return;
    }

    // Находим размер файла
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Вычисляем количество чисел в файле
    int numbersCount = fileSize / sizeof(int);

    // Выделяем память под массив чисел
    int *numbers = (int*)malloc(numbersCount * sizeof(int));
    if (numbers == NULL) {
        printf("Ошибка выделения памяти.");
        fclose(file);
        return;
    }

    // Читаем числа из файла
    fread(numbers, sizeof(int), numbersCount, file);

    // Сортируем числа: сначала положительные, потом отрицательные
    int positiveIndex = 0;

    for (int i = 0; i < numbersCount; i++) {
        if (numbers[i] >= 0) {
            int temp = numbers[i];
            numbers[i] = numbers[positiveIndex];
            numbers[positiveIndex] = temp;
            positiveIndex++;
        }
    }

    // Перезаписываем файл с новым порядком чисел
    rewind(file);
    fwrite(numbers, sizeof(int), numbersCount, file);

    free(numbers); // Освобождаем выделенную память
    fclose(file);
}

void Task8(const char *filename, int n) {
    FILE *file = fopen(filename, "rb+"); // Открываем файл для чтения и записи

    if (file == NULL) {
        printf("Ошибка открытия файла.");
        return;
    }

    // Определяем размер матрицы
    int matrixSize = n * n;

    // Определяем количество матриц в файле
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    int matricesCount = fileSize / (sizeof(int) * matrixSize);

    // Выделяем память для одной матрицы
    int *matrix = (int*)malloc(matrixSize * sizeof(int));

    // Читаем и обрабатываем каждую матрицу в файле
    for (int i = 0; i < matricesCount; i++) {
        fread(matrix, sizeof(int), matrixSize, file);

        // Проверяем, является ли матрица симметричной
        int isSymmetric = 1;

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (matrix[row * n + col] != matrix[col * n + row]) {
                    isSymmetric = 0;
                    break;
                }
            }
            if (!isSymmetric) break;
        }

        // Если матрица не симметрична, транспонируем ее
        if (!isSymmetric) {
            for (int row = 0; row < n; row++) {
                for (int col = row + 1; col < n; col++) {
                    int temp = matrix[row * n + col];
                    matrix[row * n + col] = matrix[col * n + row];
                    matrix[col * n + row] = temp;
                }
            }

            // Возвращаем указатель обратно на начало текущей матрицы в файле
            fseek(file, -matrixSize * sizeof(int), SEEK_CUR);

            // Перезаписываем транспонированную матрицу в файл
            fwrite(matrix, sizeof(int), matrixSize, file);
        }
    }

    free(matrix); // Освобождаем выделенную память
    fclose(file);
}

typedef struct {
    char name[50];
    int bestResult;
} Athlete;
// Функция для формирования команды из n лучших спортсменов
void Task9(char* filename, int n) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    Athlete athletes[100]; // Предполагаем, что в файле не более 100 спортсменов

    // Чтение данных из файла
    int numAthletes = 0;
    while (fread(&athletes[numAthletes], sizeof(Athlete), 1, file)) {
        numAthletes++;
    }

    // Сортировка спортсменов по результатам
    for (int i = 0; i < numAthletes - 1; i++) {
        for (int j = 0; j < numAthletes - i - 1; j++) {
            if (athletes[j].bestResult < athletes[j + 1].bestResult) {
                Athlete temp = athletes[j];
                athletes[j] = athletes[j + 1];
                athletes[j + 1] = temp;
            }
        }
    }

    // Запись информации о членах команды в файл
    FILE* teamFile = fopen("team.txt", "wb");
    if (teamFile == NULL) {
        printf("Ошибка создания файла команды.\n");
        return;
    }

    for (int i = 0; i < n && i < numAthletes; i++) {
        fwrite(&athletes[i], sizeof(Athlete), 1, teamFile);
    }

    fclose(file);
    fclose(teamFile);
}
// Структура для хранения информации о товаре на складе
typedef struct {
    char name[50];
    float price;
    float totalCost;
    int quantity;
} Product;

// Структура для хранения информации о заказе
typedef struct {
    char name[50];
    int quantity;
} Order;

// Функция для обновления файла с учетом отпущенных товаров
void Task10(char* fileF, char* fileG) {
    FILE* fileFPtr = fopen(fileF, "rb+");
    if (fileFPtr == NULL) {
        printf("Ошибка открытия файла F.\n");
        return;
    }

    FILE* fileGPtr = fopen(fileG, "rb");
    if (fileGPtr == NULL) {
        printf("Ошибка открытия файла G.\n");
        fclose(fileFPtr);
        return;
    }

    Product product;
    Order order;

    // Чтение информации о товарах из файла F
    while (fread(&product, sizeof(Product), 1, fileFPtr)) {
        fseek(fileGPtr, 0, SEEK_SET); // Переходим в начало файла G для каждого товара из F
        int found = 0;

        // Обработка каждого заказа из файла G
        while (fread(&order, sizeof(Order), 1, fileGPtr)) {
            if (strcmp(product.name, order.name) == 0) {
                found = 1;
                if (order.quantity < product.quantity) {
                    product.quantity -= order.quantity;
                    product.totalCost -= product.price * order.quantity;
                } else {
                    product.quantity = 0;
                    product.totalCost = 0;
                    break; // Товар отпущен полностью, выходим из цикла
                }
            }
        }

        // Если товар не был найден в заказах, оставляем его без изменений
        if (!found) {
            fseek(fileFPtr, -sizeof(Product), SEEK_CUR);
        } else {
            fwrite(&product, sizeof(Product), 1, fileFPtr);
        }
    }

    fclose(fileFPtr);
    fclose(fileGPtr);
}



