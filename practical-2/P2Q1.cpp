#include <thread>
#include <iostream>

// stopwatch. Returns time in seconds
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

// for exposition clarity, generally avoid global varaibles.
const int count = 1000000;

double timerResult1;
double timerResult2;

void f1() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult1 = stopwatch.elapsed();
}
void f2() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult2 = stopwatch.elapsed();
}

int main() {
    std::cout.precision(6); 
    std::cout << std::fixed;
    f1(); 
    std::cout << "f1 execution time " << timerResult1 << std::endl;
    timer stopwatch;
    {
        std::thread thread1(f1);
        std::thread thread2(f2);
        thread1.join();
        thread2.join();
    }
    double elapsed = stopwatch.elapsed();
    std::cout << "thread f1 execution time " << timerResult1 << std::endl;
    std::cout << "thread f2 execution time " << timerResult2 << std::endl;
    std::cout << "f1 with f2 execution time " << elapsed << std::endl;
 }