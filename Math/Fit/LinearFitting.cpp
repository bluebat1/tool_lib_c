#include "LinearFitting.h"

// 计算集合平均值
static inline float ArrayMean(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    // 返回平均值
    return sum / (float)size;
}

/// @brief 集合相乘 inA * inB
/// @param out 结果输出
/// @param inA 输入集合A
/// @param inB 输入集合B
/// @param size 输入集合长度
static inline void ArrayMultiply(float *out, float* inA, float* inB, int size){
    for (int i = 0; i < size; i++)
    {
        out[i] = inA[i] * inB[i];
    }
}

/// @brief 集合元素 * x
/// @param out 输出的集合
/// @param in 输入的集合
/// @param size 集合大小
/// @param x 乘数
static inline void ArrayMultiplyNum(float *out, float* in, int size, float x ){
    for (int i = 0; i < size; i++)
    {
        out[i] = in[i] * x;
    }   
}

/// @brief 集合元素相减 out = inA - inB
/// @param out 输出集合
/// @param inA 输入集合 被减数
/// @param inB 输入集合 减数
/// @param size 集合大小
static inline void ArraySubtract(float *out, float *inA, float* inB, int size){
    for (int i = 0; i < size; i++)
    {
        out[i] = inA[i] - inB[i];
    }
} 

/// @brief 集合每个元素 - x
/// @param out 输出的集合
/// @param in 输入的集合
/// @param size 集合大小
/// @param x 减数
static inline void ArraySubtractNum(float *out, float *in, int size, float x){
    for (int i = 0; i < size; i++)
    {
        out[i] = in[i] - x;
    }
} 

/// @brief 集合元素 + x
/// @param out 输出的集合
/// @param in 输入的集合
/// @param size 集合大小
/// @param x 加数
static inline void ArrayAddNum(float *out, float *in, int size, float x){
    for (int i = 0; i < size; i++)
    {
        out[i] = in[i] + x;
    }
}

/// @brief 集合元素开平方
/// @param out 输出集合
/// @param in 输入集合
/// @param size 集合大小 
static inline void ArraySquare(float *out, float*in, int size){
    for (int i = 0; i < size; i++)
    {
        out[i] = in[i]*in[i];
    }
}

/// @brief 集合元素求和
/// @param in 输入集合
/// @param size 集合大小
/// @return 输出元素和
static inline float ArraySum(float *in, int size) {
    float sum = 0.0f;
    for (int i = 0; i < size; i++)
    {
        sum += in[i];
    }
    return sum;
}


/// @brief 线性回归拟合直线
/// @param x X集合
/// @param y Y集合
/// @param size 集合大小
/// @param a 系数输出
/// @param b 系数输出
/// @param RSquare R方 相关性
void LineFitting(float* x, float* y, int size, float *a, float *b, float *RSquare){
    static float x_mean, y_mean, numerator, denominator, slope, intercept, ss_total, ss_residual;
    float cacheA[size];
    float cacheB[size];
    
    // # 计算数据点的均值
    x_mean = ArrayMean(x, size);
    y_mean = ArrayMean(y, size);
    
    // # 计算最小二乘法的斜率和截距
    // numerator = ∑((x - mean_x) * (y - mean_y))
    ArraySubtractNum(cacheA, x, size, x_mean);
    ArraySubtractNum(cacheB, y, size, y_mean);
    ArrayMultiply(cacheB, cacheA, cacheB, size);
    numerator = ArraySum(cacheB, size);
    // denominator = ∑((x - mean_x) ^ 2)
    ArraySquare(cacheB, cacheA, size);
    denominator = ArraySum(cacheB, size);
    slope = numerator/denominator;
    intercept = y_mean - slope * x_mean;

    // # 计算总体平方和和回归平方和
    // y_pred = slope * x + intercept
    ArrayMultiplyNum(cacheB, x, size, slope);
    ArrayAddNum(cacheB, cacheB, size, intercept);
    // ss_total = ∑((y - mean_y) ** 2)
    ArraySubtractNum(cacheA, y, size, y_mean);
    ArraySquare(cacheA, cacheA, size);
    ss_total = ArraySum(cacheA, size);
    // ss_residual = ∑((y - y_pred) ** 2)
    ArraySubtract(cacheA, y, cacheB, size);
    ArraySquare(cacheA, cacheA, size);
    ss_residual = ArraySum(cacheA, size);
    
    // 计算 R方 相似度
    // R^2 = 1 - (ss_residual / ss_total)
    *RSquare = 1-(ss_residual/ss_total); 
    *a = slope;
    *b = intercept;
}



