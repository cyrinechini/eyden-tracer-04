#pragma once

#include "SampleGenerator.h"
#include <time.h>
#include <stdlib.h> 

class CSampleGeneratorRandom : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
        int m = std::sqrt(n);
        int x;
        srand (time(NULL));
        for (int i = 0; i < n; i++) {
            u[i] = (float) rand()/RAND_MAX;
            v[i] = (float) rand()/RAND_MAX;
            weight[i] = 1.0f / n;
        }
	}
};


