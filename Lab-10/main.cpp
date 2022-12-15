#include "Matrix.h"


int main(int argc, char **argv){
    Matrix <int, 2,2> m = Matrix<int,2,2>(1);
    m.set(0,1, 2);
    m.set(1,0, 3);
    m.set(1,1,4);
    m.print();
    std::cout << std::endl;
    std::cout << (++m).get(1,1) << std::endl;
    std::cout << m[1][1] << std::endl;
    std:: cout << (m++).get(1,1) << std::endl;
    std::cout << m.get(1,1) << std::endl;
    m[1][1] = 10;
    std::cout << m[1][1] << std::endl;
    m.print();
    std::cout << std::endl;
    auto m2 = m + 10;
    auto m3 = m * 10;
    m2.print();
    std::cout << std::endl;
    m3.print();
    std::cout << std::endl;
    (m+m).print();
    std::cout << std::endl;
    Matrix <int, 2,2> m4 = Matrix<int,2,2>(1);
    m4.set(0,1, 2);
    m4.set(1,0, 3);
    m4.set(1,1,4);
    m4.print();
    std::cout << std::endl;
    (m4*m4).print();
    std::cout << std::endl;

}