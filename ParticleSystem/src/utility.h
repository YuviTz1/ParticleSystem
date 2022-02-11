#pragma once

#include<random>
#include<chrono>

//generate random number
inline float random_number_between(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	std::mt19937 generator;
	auto tseed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	generator.seed(tseed);
	return distribution(generator);
}