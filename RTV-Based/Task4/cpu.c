#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  #define SLEEP_SEC(x) Sleep((x) * 1000)
#else
  #include <unistd.h>
  #define SLEEP_SEC(x) sleep(x)
#endif

int main(void) {
    const int readings = 50;
    int cpu[readings];
    int overload_count = 0;
    int stable_count = 0;    // CPU between 40–60%
    double sum = 0.0;

    srand((unsigned) time(NULL));

    printf("Real-Time CPU Usage Simulator\n");
    printf("Collecting %d readings...\n\n", readings);

    for (int i = 0; i < readings; i++) {

        cpu[i] = rand() % 101;  // 0 to 100
        sum += cpu[i];

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char ts[64];

        if (tm != NULL) {
            strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", tm);
        } else {
            strncpy(ts, "1970-01-01 00:00:00", sizeof(ts));
            ts[sizeof(ts) - 1] = '\0';   // FIXED null terminator
        }

        printf("[%s] Iter %2d: CPU = %3d%%\n", ts, i + 1, cpu[i]);

        if (cpu[i] > 85) overload_count++;
        if (cpu[i] >= 40 && cpu[i] <= 60) stable_count++;

        SLEEP_SEC(1);   // simulate 1 second delay
    }

    double avg = sum / readings;

    printf("\nOverload events (>85%%):\n");
    for (int i = 0; i < readings; i++) {
        if (cpu[i] > 85) {
            printf(" - Iter %2d: %3d%%\n", i + 1, cpu[i]);
        }
    }

    printf("\nSUMMARY:\n");
    printf("Average CPU Usage             : %.2f%%\n", avg);
    printf("Overload Events (>85%%)        : %d\n", overload_count);
    printf("Stable CPU (40–60%%)           : %d\n", stable_count);

    return 0;
}
