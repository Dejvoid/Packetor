#include <iostream>

int subset_count(bool* signature, const size_t count){
    int ctr = 0;
    for (size_t i = 0; i < count; i++){
        if(!signature[i])
            ctr++;
    }
    return ctr;
}

void print_subset(const char* items, const size_t count, bool* signature, bool* shouldEnd){
    int ctr = subset_count(signature, count);
    if(ctr == 0){
        *shouldEnd = true;
    }
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

void priv_get_subsets(const char* items, const size_t count, bool* signature, bool* shouldEnd){
    if(*shouldEnd)
        return;
    print_subset(items, count, signature, shouldEnd);
    for (size_t i = count; i > 0; i--){
        if(!signature[i-1]){
            signature[i-1] = true;
            priv_get_subsets(items, count, signature, shouldEnd);
        }
        signature[i-1] = false;
    }
}

void get_subsets(const char* items, const size_t count){
    bool* signature = new bool[count];
    bool shouldEnd = false;
    priv_get_subsets(items, count, signature, &shouldEnd); 
    delete[] signature;
}

int main(int argc, char** argv){
    const char items[] = {'A','B','C','D'};
    const size_t count = sizeof(items) / sizeof(items[0]);
    get_subsets(items, count);
}