#pragma once

#include "SampleGenerator.h"

class CSampleGeneratorStratified : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
        int m = std::sqrt(n);
        int x;
        float ei, ej;
        srand (time(NULL));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                ei = (float) rand()/ RAND_MAX ;
                ej = (float) rand()/ RAND_MAX;
                x = i * m + j;
                u[x] = (i + ei) / m;
                v[x] = (j + ej) / m;
                weight[x] = 1.0f / n;
            }
        }
	}
};
