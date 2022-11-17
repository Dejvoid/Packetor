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
    return 0;
}
// +-*/() prirozena cisla + 0
// stromova struktura vyrazu
