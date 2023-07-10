#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

void* f_count(void* v) {
    (*(int*)v)++;

    return NULL;
}

int main() {
    int* count = new int(0);

    vector<pthread_t> vt;

    pthread_t t;

    for (int i = 0; i < 100; i++)
        vt.push_back(t);

    // for (pthread_t x : vt)
    //     pthread_create(&x, NULL, &f_count, count),
    //     pthread_join(x, NULL);
    for (size_t i = 0; i < vt.size(); i++) {
        pthread_t x = vt[i];
        pthread_create(&x, NULL, &f_count, count);
        pthread_join(x, NULL);
    }

    cout << *count;

    return 0;
}