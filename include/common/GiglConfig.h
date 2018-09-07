#pragma once

#include <cstdlib>
#include <cstring>
#include "CommonTypeDefs.h"

class GiglConfig
{
public:
	GiglConfig(); // uninitialized constructor; yield error or undefined behavior when copied/moved to another object
	GiglConfig(unsigned int n_p, unsigned int n_f, int total_p_size, const SizeVec& p_sizes, const VarPtrVec& ps, const IndexVec& f_indices, const FuncPtrVec& fs);
	GiglConfig(const GiglConfig& config); // copy constructor
	GiglConfig(GiglConfig&& config); // move constructor
	void operator = (const GiglConfig& config); // copy operator
	void operator = (GiglConfig&& config); // move operator
	~GiglConfig();
private:
	void Destruct();
	unsigned int num_vars;
	unsigned int num_funcs;
	unsigned int total_var_size;
	size_t* var_sizes;
	VarPtr var_storage;
	bool moved;

public:
	VarPtrPtr vars;
	FuncPtrPtr funcs;
};
