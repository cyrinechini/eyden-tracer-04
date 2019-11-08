#pragma once

#include "SampleGenerator.h"
#include <math.h>

class CSampleGeneratorRegular : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
        int m = std::sqrt(n);
        int x;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                x = i * m + j;
                u[x] = (i + 0.5) / m;
                v[x] = (j + 0.5) / n;
                weight[x] = 1.0f / n;
            }
        }
	}
};
