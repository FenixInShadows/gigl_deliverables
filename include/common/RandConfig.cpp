#include "RandConfig.h"

mt19937_64 rand_utility::rng;
uniform_int_distribution<int> rand_utility::uniform_int_dist;
uniform_real_distribution<double> rand_utility::uniform_real_dist;

void rand_utility::RandInit(unsigned seed)
{
	rng.seed(seed);
}

int rand_utility::GetRandInt()
{
	return uniform_int_dist(rng);
}

int rand_utility::GetRandInt(int upper_bound) // 0 ~ upper_bound - 1; assumes upper_bound is positive
{
	return GetRandInt() % upper_bound;
}

int rand_utility::GetRandInt(int min_val, int max_val)
{
	return min_val + GetRandInt(max_val - min_val + 1);
}

void rand_utility::RandShuffle(int* list, int num)
{
	for (int l = num; l > 1; l--)
	{
		int* target = list + (l - 1);
		int* source = list + GetRandInt() % l;
		int temp = *target;
		*target = *source;
		*source = temp;
	}
}

void rand_utility::RandShuffle(int * list, int num, int k)
{
	int stopping_l = num - k;
	if (stopping_l < 1)
		stopping_l = 1;
	for (int l = num; l > stopping_l; l--)
	{
		int* target = list + (l - 1);
		int* source = list + GetRandInt() % l;
		int temp = *target;
		*target = *source;
		*source = temp;
	}
}

void rand_utility::IncOrder(int* list, int num)
{
	for (int i = 0; i < num; i++)
		list[i] = i;
}

void rand_utility::DecOrder(int* list, int num)
{
	for (int i = 0; i < num; i++)
		list[i] = num - i - 1;
}

void rand_utility::RandOrder(int* list, int num)
{
	IncOrder(list, num);
	RandShuffle(list, num);
}

double rand_utility::GetRandFloat()
{
	return uniform_real_dist(rng);
}

double rand_utility::GetRandFloat(double max_val)
{
	return GetRandFloat() * max_val;
}

double rand_utility::GetRandFloat(double min_val, double max_val)
{
	return min_val + GetRandFloat(max_val - min_val);
}

bool rand_utility::RandomRoll(double succ_prob)
{
	return (GetRandFloat() < succ_prob);
}

int rand_utility::GetRandChoiceFromCumProbs(const double* cum_probs, int num)
{
	double tmp_rand = GetRandFloat();

	for (int i = 0; i < num; i++)
		if (tmp_rand < cum_probs[i])
			return i;

	return num; // normally shouldn't happen, maybe can be used for un-normalized cases, and/or when the last cumulative probability (1.0) not passed in (current usage does potentially have numerical precision issues though)
}

int rand_utility::GetRandChoiceFromProbs(const double* probs, int num)
{
	double tmp_rand = GetRandFloat();
	double cum_prob = 0.0;
	for (int i = 0; i < num; i++)
	{
		cum_prob += probs[i];
		if (tmp_rand < cum_prob)
			return i;
	}
	return num; // normally shouldn't happen, maybe can be used for un-normalized cases, and/or when the last probability not passed in (current usage does potentially have numerical precision issues though)
}

void rand_utility::NormalizeProbs(double* probs, int num)
{
	return NormalizeProbsTo(probs, num, 1.0);
}

void rand_utility::NormalizeProbsTo(double* probs, int num, double val)
{
	double sum_probs = 0.0;
	for (int i = 0; i < num; i++)
		sum_probs += probs[i];
	if (sum_probs > 0.0)
	{
		double ratio = val/sum_probs;
		for (int i = 0; i < num; i++)
			probs[i] *= ratio;
	}
}

void rand_utility::NonegativeProbs(double* probs, int num)
{
	for (int i = 0; i < num; i++)
		if (probs[i] < 0.0)
			probs[i] = 0.0;
}

void rand_utility::ForbidProbsExcept(double* probs, int num, const IndexVec& indices, int transfer_dest)
{
	bool* flags = new bool[num];

	for (int i = 0; i < num; i++)
		flags[i] = true;
	for (int i = 0; i < indices.size(); i++)
		flags[indices[i]] = false;
	
	if (transfer_dest < 0 || transfer_dest >= num)
	{
		for (int i = 0; i < num; i++)
			if (flags[i])
				probs[i] = 0.0;
	}
	else
	{
		for (int i = 0; i < num; i++)
			if (flags[i])
			{
				probs[transfer_dest] += probs[i];
				probs[i] = 0.0;
			}
	}

	delete [] flags;
}
