#include <iostream>
#include<thread>
#include<chrono>

using std::this_thread::sleep_for;
using std::chrono::seconds;
using namespace std;

void MakeTop() {
    std::cout<<"Table top is being created ...\n";
    sleep_for(seconds(7));
    std::cout<<" Top done!\n";
}

void MakeLegs() {
    std::cout<<"Table legs are being created ...\n";
    sleep_for(seconds(5));
    std::cout<<" Legs done!\n";
}

int main() {
    std::cout<<"Boss gets a new coffee table order.\n";
    std::cout<<"Boss divides the tasks:\n";   
    std::thread carpenter1(MakeTop);
    std::thread carpenter2(MakeLegs);

    std::cout<<"Boss is waiting for carpenters...\n";
    carpenter1.join();
    carpenter2.join();

    std::cout<<"Boss attaches top and legs of coffee table.";

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    return 0;
}