#include "Expression.h"


int main(int argc, char **argv){
    Expression e1 (
        new MultiplicationNode(
            new AdditionNode(
                new NumberNode(2), new NumberNode(3)),
            new NumberNode(4)
        )
    );
    e1.print_infix();
    e1.print_postfix();
    std:: cout<< e1.evaluate() << std::endl;
    return 0;
}
