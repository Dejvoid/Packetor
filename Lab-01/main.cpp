#include <iostream>

void print_subset(const char* items, size_t count, bool* signature ){
    std::cout << "{ ";
    for (size_t i = 0; i < count; i++){
        if(signature[i]){
            std::cout << items[i] << " ";
        }
    }
    std::cout << "}" <<std::endl;
}

void priv_get_subsets(const char* items, size_t count, bool* signature, size_t offset = 0){
    print_subset(items, count, signature);
    for (size_t i = offset; i < count; i++){
        if(!signature[i]){
            signature[i] = true;
            priv_get_subsets(items, count, signature, i);
        }
    }
    signature[offset] = false;
}

void get_subsets(const char* items, size_t count){
    bool* signature = new bool[count];
    priv_get_subsets(items, count, signature); 
    delete[] signature;
}

int main(int argc, char** argv){
    const char items[] = {'A','B','C','D'};
    const size_t count = sizeof(items) / sizeof(items[0]);
    const size_t subset_count = 1 << count;
    get_subsets(items, count);
}