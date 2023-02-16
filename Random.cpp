//
// Created by Sam Carozzi on 12/4/22.
//

#include "Random.h"
using namespace std;

mt19937 Random::random(time(0));

int Random::Int(int min, int max) {

    uniform_int_distribution<int> dist(min,max);
    return dist(random);
}

float Random::Float(int min, int max) {
    uniform_int_distribution<float> dist(min,max);
    return dist(random);
}
