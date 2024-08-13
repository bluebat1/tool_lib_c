/*
 * Defer.h
 *
 *  Created on: 2023年12月12日
 *      Author: work-1
 */

#ifndef JNI_UTIL_DEFER_H_
#define JNI_UTIL_DEFER_H_

template <typename F>
struct privDefer {
    F f;
    privDefer(F f) : f(f) {}
    ~privDefer() { f(); }
};

template <typename F>
privDefer<F> defer_func(F f) {
    return privDefer<F>(f);
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x)    DEFER_2(x, __COUNTER__)
#define defer(code)   auto DEFER_3(_defer_) = defer_func(code)

// 示例
//buffer = malloc()
//if(buffer == NULL) {
//		return;
//}
//defer([](){
//		// 增加一次断言，避免定义被编译器优化到malloc前面
//		if(buffer != NULL) {
//			free(buffer);
//		}
//});


#endif /* JNI_UTIL_DEFER_H_ */
