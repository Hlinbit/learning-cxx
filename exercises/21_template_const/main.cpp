#include "../exercise.h"
#include <cstring>

// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;
    unsigned int table[N];

    Tensor(unsigned int const shape_[N]): table{1} {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for (int i = 0; i < N; i++) {
            shape[i] = shape_[i];
            table[i] = 1;
            size *= shape_[i];
            for (int j = i + 1; j < N; j++) {
                table[i] *= shape_[j];
            }
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }
    ~Tensor() {
        delete[] data;
    }

    // 禁止拷贝构造函数和赋值运算符
    Tensor(Tensor const &) = delete;
    Tensor& operator=(Tensor const &) = delete;

    // 允许移动构造函数和移动赋值运算符
    Tensor(Tensor &&other) noexcept {
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = other.shape[i];
            table[i] = other.table[i];
        }
        data = other.data;
        other.data = nullptr;
    }

    Tensor& operator=(Tensor &&other) noexcept {
        if (this != &other) {
            delete[] data;

            for (unsigned int i = 0; i < N; ++i) {
                shape[i] = other.shape[i];
                table[i] = other.table[i];
            }
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        
        for (unsigned int i = 0; i < N; i++) {
            ASSERT(indices[i] < shape[i], true);
            index += indices[i] * table[i];
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i0] = 2;
        ASSERT(tensor[i0] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i0] = 2.f;
        ASSERT(tensor[i0] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
