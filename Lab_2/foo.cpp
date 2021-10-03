#include "foo.h"

void test1_1(int n, double &time) { ///типовая задача (тест)
  int a[n][n], b[n][n], c[n][n];
  // Заполнение матриц. Матрицу a и b будем перемножать.
  // с - матрица-результат перемножения
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % 10;
      b[i][j] = rand() % 10;
    }
  }
  clock_t start, stop;
  start = clock();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      c[i][j] = 0;
      for (int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  stop = clock();
  time = ((double)(stop - start)) / CLOCKS_PER_SEC;

}

void test1_2(int n, double &time) { ///типовая задача с другим типом данных
  double a[n][n], b[n][n], c[n][n];
  // Заполнение матриц. Матрицу a и b будем перемножать.
  // с - матрица-результат перемножения
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % 10;
      b[i][j] = rand() % 10;
    }
  }
  clock_t start, stop;
  start = clock();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      c[i][j] = 0;
      for (int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  stop = clock();
  time = ((double)(stop - start)) / CLOCKS_PER_SEC;
}

void test1_3(int n, double &time) { ///типовая задача с другим типом данных
  float a[n][n], b[n][n], c[n][n];
  // Заполнение матриц. Матрицу a и b будем перемножать.
  // с - матрица-результат перемножения
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % 10;
      b[i][j] = rand() % 10;
    }
  }
  clock_t start, stop;
  start = clock();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      c[i][j] = 0;
      for (int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  stop = clock();
  time = ((double)(stop - start)) / CLOCKS_PER_SEC;
}
// Производительность процессора
void benchmark(int num_test, int n, int matrix_size,
               double &avg_time, double &dispersion,
               double &abs_error, double &rel_error)
{
    double summand1 = 0, summand2 = 0;
    double x; ///время выполнения только типовой задачи

    for (int i = 0; i < n; i++) {
        switch (num_test) { ///выбор типовой задачи (теста)
            case 0:
                test1_1(matrix_size, x);
                break;
            case 1:
                test1_2(matrix_size, x);
                break;
            case 2:
                test1_3(matrix_size, x);
                break;
            default:
                printf("ERROR: wrong \"num_test\" in benchmark() \n");
                break;
        } ///конец switch
        summand1 += x * x; ///первое слагаемое для дисперсии
        summand2 += x; ///2-ое слагаемое
    }
    summand1 /= n;
    summand2 /= n;
    avg_time = summand2; ///sum(x[i]) / n == среднее время
    summand2 *= summand2;
    dispersion = summand1 - summand2; ///дисперсия (точность измерения времени)
    abs_error = sqrt(dispersion); ///среднее квадратическое отклонение (погрешность)
    rel_error = dispersion / avg_time; ///относительная погрешность
}
// имя процессора
void get_cpu_name(char cpuname[]) {
    FILE *fcpu;
    if ((fcpu = fopen("/proc/cpuinfo", "r")) == NULL) {
        printf("Can't open /proc/cpuinfo \n");
        return;
    }
    size_t m = 0;
    char *line = NULL;
    /* getline - считываем строку из входного потока
     * line - переменная в которую запишется строка
     * m - содержит размер вхоного буфера
     * fcpu - файл из которого будет считана строка
    */
    while (getline(&line, &m, fcpu) > 0) {
      // strstr() - поиск первого вхождения строки "model name"
        if (strstr(line, "model name")) {
            strcpy(cpuname, &line[13]);
            break;
        }
    }
    for (int i = 0; i < 50; i++) {
        if (cpuname[i] == '\n')
            cpuname[i] = '\0';
    }
    fclose(fcpu);
}
