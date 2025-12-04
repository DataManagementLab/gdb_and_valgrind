#include <cstdlib>
#include <cmath>
#include <ctime>


void func5() {
    long long var5;
}

void func4() {
    short var4;
}

void func3() {
    double var3;
}
void func2() {
    float var2 = sin(0.5) * 10000;
}

void func1() {
    int var1 = sin((double)rand() * 2) * 10000;
    func2();
    var1 = sin(var1) * 10000;
}

int main() {
    srand(time(NULL));
    func1();
    return 0;
}
