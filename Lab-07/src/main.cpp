#include "Expression.h"

int main(int argc, char **argv){
    std::cout << "BRUH";
    std::string example = "10*2+3*((1+14)-18)-10";
    Expression e2(example);
    //if (e2.is_valid())
        e2.print_infix();
    //else 
        std::cout << "invalid";
    std::cout << std:: endl;
    std:: cout << e2.evaluate() <<std::endl;
/*
    Expression e1 (
        new MultiplicationNode(
            new AdditionNode(
                new NumberNode(2), new NumberNode(3)),
            new NumberNode(4)
        )
    );
    e1.print_infix();
    e1.print_postfix();
    std:: cout<< e1.evaluate() << std::endl;*/
    return 0;
}