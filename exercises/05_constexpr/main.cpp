#include "../exercise.h"

constexpr unsigned long long fibonacci(int n) {
    unsigned long long a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        unsigned long long temp = a;
        a = b;
        b += temp;
    }
    return a;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    constexpr auto ANS_N = 100;
    constexpr auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
