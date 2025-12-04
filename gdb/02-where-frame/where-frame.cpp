#include <cstdlib>
#include <cmath>
#include <ctime>


void func5() {
    long long var5 = 5;
    return;
}

void func4() {
    short var4 = 4;
    func5();
}

void func3() {
    double var3 = 3;
    func4();
}
void func2() {
    float var2 = 2;
    func3();
}

void func1() {
    int var1 = 1;
    func2();
}

int main() {
    int var_main = 0;
    srand(time(NULL));
    func1();
    return 0;
}
