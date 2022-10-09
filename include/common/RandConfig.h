#pragma once

#include <random>

#include "CommonTypeDefs.h"

using namespace std;

namespace rand_utility
{
	extern mt19937_64 rng;
	extern uniform_int_distribution<int> uniform_int_dist;
	extern uniform_real_distribution<double> uniform_real_dist;

	void RandInit(unsigned seed);

	int GetRandInt();

	int GetRandInt(int upper_bound); // 0 ~ upper_bound - 1

	int GetRandInt(int min_val, int max_val); // min_val ~ max_val

	void RandShuffle(int* list, int num); // randomly reorder original elements in the list

	void RandShuffle(int* list, int num, int k); // randomly reorder original elements in the list, but only caring about the LAST k values (when k >= n it behaves the same as the basic version above)

	void IncOrder(int* list, int num); // 0 .. num - 1

	void DecOrder(int* list, int num); // num - 1 .. 0

	void RandOrder(int* list, int num); // a list with randomly ordered 0 .. num - 1

	double GetRandFloat(); // 0.0 ~ 1.0

	double GetRandFloat(double max_val); // 0.0 ~ max_val

	double GetRandFloat(double min_val, double max_val); // min_val ~ max_val

	bool RandomRoll(double succ_prob);

	int GetRandChoiceFromCumProbs(const double* cum_probs, int num);

	int GetRandChoiceFromProbs(const double* probs, int num);

	void NormalizeProbs(double* probs, int num);

	void NormalizeProbsTo(double* probs, int num, double val);

	void NonegativeProbs(double* probs, int num);

	void ForbidProbsExcept(double* probs, int num, const IndexVec& indices, int transfer_dest);
}
