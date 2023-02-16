//
// Created by Sam Carozzi on 12/4/22.
//

#pragma once
#include <random>

using namespace std;
class Random{
    static mt19937 random;

public:

    static int Int(int min, int max);
    static float Float(int min, int max);
};
