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
double timerResult3;
double timerResult4;
double timerResult5;
double timerResult6;
double timerResult7;
double timerResult8;

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

void f3() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult3 = stopwatch.elapsed();
}

void f4() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult4 = stopwatch.elapsed();
}

void f5() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult5 = stopwatch.elapsed();
}

void f6() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult6 = stopwatch.elapsed();
}

void f7() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult7 = stopwatch.elapsed();
}

void f8() {
    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < count);
    timerResult8 = stopwatch.elapsed();
}

int main() {
    std::cout.precision(6); 
    std::cout << std::fixed;
    f1(); 
    std::cout << "Serial execution time " << timerResult1 << std::endl;
    timer stopwatch;
    {
        std::thread thread1(f1);
        std::thread thread2(f2);
        std::thread thread3(f3);
        std::thread thread4(f4);
        std::thread thread5(f5);
        std::thread thread6(f6);
        std::thread thread7(f7);
        std::thread thread8(f8);
        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        thread5.join();
        thread6.join();
        thread7.join();
        thread8.join();
    }
    double elapsed = stopwatch.elapsed();
    std::cout << "thread f1 execution time " << timerResult1 << std::endl;
    std::cout << "thread f2 execution time " << timerResult2 << std::endl;
    std::cout << "thread f3 execution time " << timerResult3 << std::endl;
    std::cout << "thread f4 execution time " << timerResult4 << std::endl;
    std::cout << "thread f5 execution time " << timerResult5 << std::endl;
    std::cout << "thread f6 execution time " << timerResult6 << std::endl;
    std::cout << "thread f7 execution time " << timerResult7 << std::endl;
    std::cout << "thread f8 execution time " << timerResult8 << std::endl;
    std::cout << "f1 - f8 execution time " << elapsed << std::endl;
 }