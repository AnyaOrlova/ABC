#include "foo.h"

int main() {
  // инициализирует случайные числа
    srand(time(0));
    int num_test = 3; ///количество тестов
    int n = 10;
    /*
     * avg_time - , среднее время выполнения типовой
       задачи из всех испытаний[секунды];
     * dispersion - дисперсия
     * abs_error - абсолютная погрешность измерения
       времени в секундах;
     * rel_error - относительная погрешность измерения времени в %;
    */
    double avg_time[num_test], dispersion[num_test];
    double abs_error[num_test], rel_error[num_test];
    int matrix_size = 100;

    for (int i = 0; i < num_test; i++) {
        benchmark(i, n, matrix_size, avg_time[i], dispersion[i], abs_error[i], rel_error[i]);
    }

    ///получение названия процессора
    char cpuname[50] = {'\0'};
    get_cpu_name(cpuname);
    //printf("%s %d \n", cpuname, (int)sizeof(cpuname));

    ///запись в output.csv
    FILE *fout;
    if ((fout = fopen("output.csv", "w")) == NULL) {
        printf("Can't open output.csv \n");
        return 1;
    }
    //fprintf(fout, "PModel;Task;OpType;Opt;LNum;InsCount;Timer;AvTime;AbsErr;RelErr;TaskPerf\n");
    for (int i = 0; i < num_test; i++) {
        fprintf(fout, cpuname); ///proc
        fprintf(fout, ";");
        switch (i) {
            case 0:
                fprintf(fout, "matrixA * matrixB;int;None;");
                break;
            case 1:
                fprintf(fout, "matrixA * matrixB;double;None;");
                break;
            case 2:
                fprintf(fout, "matrixA * matrixB;float;None;");
                break;
            default:
                printf("Error writing to file.\n");
                break;
        }

        /* ??????????????????????????????????????????????????
        switch (i) { ///instruction count
            case 0:
                fprintf(fout, "%d;", matrix_size * 3 + 2);
                break;
            case 1:
                fprintf(fout, "%d;", matrix_size * 3 + 2);
                break;
            case 2:
                fprintf(fout, "%d;", matrix_size * 3 + 2);
                break;
        }*/

        fprintf(fout, "clock();"); ///Timer
        fprintf(fout, "%d;", n); ///lanch number
        fprintf(fout, "%g;", avg_time[i]);
        fprintf(fout, "%g;", abs_error[i]);
        fprintf(fout, "%g%%;", rel_error[i] * 100); ///относительная погрешность в %
        fprintf(fout, "%g;", 1 / avg_time[i]); // P = 1sec / ср. время выполнения задачи
        fprintf(fout, "\n");
    }


    fclose(fout);
    return 0;
}
