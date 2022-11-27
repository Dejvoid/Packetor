#include "Parser.h"

bool Parser::is_literal(unsigned char val){
    return std::isalpha(val);
};

bool Parser::is_binary_operator(char val){
    return val == CONCAT_OP || ALTER_OP;
};

bool Parser::is_unary_operator(char val){
    return val == ITER_OP;
};

Node* Parser::pop_operand(std::stack<Node*>& operands){
    Node* ret = operands.top();
    operands.pop();
    return ret;
};

char Parser::pop_operator(std::stack<char>& operators){
    char op = operators.top();
    operators.pop();
    return op;
};

Node* Parser::process_binary_op(std::stack<Node*>& operands, char op){
    Node* r = pop_operand(operands);
    Node* l = pop_operand(operands);
    switch (op){
    case CONCAT_OP:
        return new ConcatNode(l,r);
        break;
    case ALTER_OP:
        return new AlterNode(l,r);
        break;
    }
    return nullptr;
};

Node* Parser::process_unary_op(std::stack<Node*>& operands, char op){
    switch (op){
    case ITER_OP:
        Node* n = pop_operand(operands);
        return new IterNode(n);
        break;
    }
    return nullptr;
};

bool Parser::is_lower_equal_precedence(char l, char r){
    return l == r || 
    (l == ALTER_OP && (r == ALTER_OP || r == CONCAT_OP));
}

Node* Parser::parse_from_str(const std::string& expr){
    int index = 0;
    std::stack<Node*> operands;
    std::stack<char> operators;
    bool implicit_concat = false;
    for(auto it = expr.begin(); it != expr.end(); ++it){
        if (is_literal(*it)){
            printf("found literal\n");
            operands.push(new LiteralNode((char)*it, ++index));
            if (implicit_concat){
                operators.push(CONCAT_OP);
                printf(" concat ");
            }
            implicit_concat = true;
        }
        else if (*it == LEFT_PARENTHESIS){
            printf("found left parenthesis\n");
            if (implicit_concat){
                operators.push(CONCAT_OP);
            }
            operators.push(*it);
            implicit_concat = false;
        }
        else if (*it == RIGHT_PARENTHESIS){
            printf("found right parenthesis\n");
            while(!operators.empty()){
                char op = pop_operator(operators);
                if (op == LEFT_PARENTHESIS)
                    break;
                operands.push(process_binary_op(operands, op));
            }
            implicit_concat = true;
        }
        else if (is_unary_operator(*it)){
            printf("found unary operator\n");
            operands.push(process_unary_op(operands, *it));
            implicit_concat = true;
        }
        else if (is_binary_operator(*it)){
            printf("Found binary operator\n");
            while (!operators.empty() && is_lower_equal_precedence(*it, operators.top())){
                char op = pop_operator(operators);
                operands.push(process_binary_op(operands, op));
            }
            operators.push(*it);
            implicit_concat = false;
        }
        else{ // is constant

        }
    }
    while (!operators.empty()){
        char op = pop_operator(operators);
        operands.push(process_binary_op(operands, op));
    }
    return pop_operand(operands);
};