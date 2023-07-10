#include <iostream>
#include <vector>
#include <pthread.h>
#include <thread>

using namespace std;

class timer {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    timer() : lastTime(std::chrono::high_resolution_clock::now()) {}
    inline double elapsed() {
        std::chrono::time_point<std::chrono::high_resolution_clock> thisTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(thisTime - lastTime).count();
        lastTime = thisTime;
        return deltaTime;
    }
};

const int counting = 1000;

void* f_count(void* timerResult) {
    volatile int i = 0;
    timer stopwatch;
    while (i++ < counting);
    *(double*)timerResult = stopwatch.elapsed();

    return NULL;
}

#define NUM_THREADS 100

int main() {
    // int* count = new int(0);
    cout << "start" << endl;
    double* timerResult1 = new double(0);
    cout << "Initialise timerResult1 " << timerResult1 << endl;

    vector<pthread_t> vt;
    cout << "Create vector pthread " << endl;

    pthread_t t[2];

    for (int i = 0; i < NUM_THREADS; i++) {
        vt.push_back(t[i]);
    }

    for (size_t i = 0; i < vt.size(); i++) {
        pthread_t x = vt[i];
        pthread_create(&x, NULL, &f_count, timerResult1);
        pthread_join(x, NULL);
    }

    // cout << *count;
    cout << "f1 execution time " << timerResult1 << endl;

    return 0;
}