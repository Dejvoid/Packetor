#include <iostream>

int subset_count(bool* signature, size_t count){
    int ctr = 0;
    for (size_t i = 0; i < count; i++){
        if(!signature[i])
            ctr++;
    }
    return ctr;
}

void print_subset(const char* items, size_t count, bool* signature){
    int ctr = subset_count(signature, count);
    std::cout << "{ ";
    int temp = 0;
    for (size_t i = 0; i < count; i++){
        if(!signature[i]){
            std::cout << items[i];
            if(++temp < ctr)
                std::cout << ",";
            std::cout << " ";
        }
    }
    std::cout << "}" <<std::endl;
}

void priv_get_subsets(const char* items, size_t count, bool* signature, size_t layer = 0){
    if(++layer <= count){
        print_subset(items, count, signature);
        for (size_t i = count-1; i >= 0; i--){
            if(!signature[i]){
                signature[i] = true;
                priv_get_subsets(items, count, signature, layer);
            }
            signature[i] = false;
        }
    }
}

void get_subsets(const char* items, size_t count){
    bool* signature = new bool[count];
    priv_get_subsets(items, count, signature); 
    delete[] signature;
}

int main(int argc, char** argv){
    const char items[] = {'A','B','C','D'};
    const size_t count = sizeof(items) / sizeof(items[0]);
    get_subsets(items, count);
}