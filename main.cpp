#include <iostream>

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "Hello, World!" << std::endl;
    return 0;
}