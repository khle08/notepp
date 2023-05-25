#ifndef _FILTFILT_H_
#define _FILTFILT_H_

#include <vector>

typedef std::vector<int> vectori;
typedef std::vector<double> vectord;

void filter(vectord B, vectord A, const vectord &X, vectord &Y, vectord &Zi);
void filtfilt(vectord B, vectord A, const vectord &X, vectord &Y);

#endif
