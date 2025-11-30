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


int rand_in_range(int a, int b) {
    if (b < a) { int tmp = a; a = b; b = tmp; }
    return a + (rand() % (b - a + 1));
}


void timestr_now(char *buf, size_t n) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (tm != NULL) {
        strftime(buf, n, "%Y-%m-%d %H:%M:%S", tm);
    } else {
        strncpy(buf, "1970-01-01 00:00:00", n);
        buf[n-1] = '\0';
    }
}

int main(void) {
    const int updates = 30;
    double price = 100.0;
    double old_price;
    int longest_rising = 0, current_rising = 0;
    double highest_price = price;
    int drops = 0;


    srand((unsigned) time(NULL));

    printf("Real-Time Stock Price Tracker (TechCorp)\n\n");

    for (int i = 1; i <= updates; i++) {
        old_price = price;
        int delta = rand_in_range(-5, 5);
        price += delta;
        if (price < 0.0) price = 0.0;

        if (price > highest_price) highest_price = price;

        if (price > old_price) {
            current_rising++;
            if (current_rising > longest_rising) longest_rising = current_rising;
        } else {
            if (price < old_price) drops++;
            current_rising = 0;
        }

        char ts[64];
        timestr_now(ts, sizeof(ts));

        printf("[%s] Iter %2d: %.2f -> %.2f (delta %+d)\n", ts, i, old_price, price, delta);

        
        SLEEP_SEC(1);
    }

    printf("\nSUMMARY:\n");
    printf("Highest Price: %.2f\n", highest_price);
    printf("Total Drops  : %d\n", drops);
    printf("Longest Rising Streak : %d\n", longest_rising);

    return 0;
}
