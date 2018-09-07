#include "RandConfig.h"

mt19937_64 rand_utility::rng;
uniform_int_distribution<int> rand_utility::uniform_int_dist;
uniform_real_distribution<double> rand_utility::uniform_real_dist;

void rand_utility::RandInit(unsigned int seed)
{
	rng.seed(seed);
}

int rand_utility::GetRandInt()
{
	return uniform_int_dist(rng);
}

int rand_utility::GetRandInt(unsigned int upper_bound) // 0 ~ upper_bound - 1
{
	return GetRandInt() % upper_bound;
}

int rand_utility::GetRandInt(int min_val, int max_val)
{
	return min_val + GetRandInt(max_val - min_val + 1);
}

void rand_utility::RandShuffle(int* list, unsigned int num)
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

void rand_utility::IncOrder(int* list, unsigned int num)
{
	for (unsigned int i = 0; i < num; i++)
		list[i] = i;
}

void rand_utility::DecOrder(int* list, unsigned int num)
{
	for (unsigned int i = 0; i < num; i++)
		list[i] = num - i - 1;
}

void rand_utility::RandOrder(int* list, unsigned int num)
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

int rand_utility::GetRandChoiceFromCumProbs(const double* cum_probs, unsigned int num)
{
	double tmp_rand = GetRandFloat();

	for (unsigned int i = 0; i < num; i++)
		if (tmp_rand < cum_probs[i])
			return i;

	return num;
}

int rand_utility::GetRandChoiceFromProbs(const double* probs, unsigned int num)
{
	double tmp_rand = GetRandFloat();
	double cum_prob = 0.0;
	for (unsigned int i = 0; i < num; i++)
	{
		cum_prob += probs[i];
		if (tmp_rand < cum_prob)
			return i;
	}
	return num;
}

void rand_utility::NormalizeProbs(double* probs, unsigned int num)
{
	return NormalizeProbsTo(probs, num, 1.0);
}

void rand_utility::NormalizeProbsTo(double* probs, unsigned int num, double val)
{
	double sum_probs = 0.0;
	for (unsigned int i = 0; i < num; i++)
		sum_probs += probs[i];
	if (sum_probs > 0.0)
	{
		double ratio = val/sum_probs;
		for (unsigned int i = 0; i < num; i++)
			probs[i] *= ratio;
	}
}

void rand_utility::NonegativeProbs(double* probs, unsigned int num)
{
	for (unsigned int i = 0; i < num; i++)
		if (probs[i] < 0.0)
			probs[i] = 0.0;
}

void rand_utility::ForbidProbsExcept(double* probs, unsigned int num, const IndexVec& indices, int transfer_dest)
{
	bool* flags = new bool[num];

	for (unsigned int i = 0; i < num; i++)
		flags[i] = true;
	for (unsigned int i = 0; i < indices.size(); i++)
		flags[indices[i]] = false;
	
	if (transfer_dest < 0 || transfer_dest >= (int)num)
	{
		for (unsigned int i = 0; i < num; i++)
			if (flags[i])
				probs[i] = 0.0;
	}
	else
	{
		for (unsigned int i = 0; i < num; i++)
			if (flags[i])
			{
				probs[transfer_dest] += probs[i];
				probs[i] = 0.0;
			}
	}

	delete flags;
}
