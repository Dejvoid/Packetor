#include <iostream>

void print_subsets(){
    // { A, B, C, D }
    // { A, B, C }

}

void int_get_subsets(const char* items, size_t count, bool* signature, int offset = 0){
    
    for (size_t i = 0; i < count; i++){
        if(!signature[i]){
            signature[i] = true;
        }
    }
    
}

void get_subsets(const char* items, size_t count){
    bool* signature = new bool[count];
    int_get_subsets(items, count, signature);
    delete[] signature;
}

int main(int argc, char** argv){
    const char items[] = {'A','B','C','D'};
    const size_t count = sizeof(items) / sizeof(items[0]);
    get_subsets(items, count);
}