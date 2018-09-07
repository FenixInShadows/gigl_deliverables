#include "GiglConfig.h"

GiglConfig::GiglConfig()
	: num_vars(0), num_funcs(0), total_var_size(0), var_sizes(0), var_storage(0), vars(0), funcs(0), moved(true)
{
}

GiglConfig::GiglConfig(unsigned int n_p, unsigned int n_f, int total_p_size, const SizeVec& p_sizes, const VarPtrVec& ps, const IndexVec& f_indices, const FuncPtrVec& fs)
	: num_vars(n_p), num_funcs(n_f), total_var_size(total_p_size), var_sizes(new size_t[num_vars]), var_storage(malloc(total_var_size)), vars(new VarPtr[num_vars]), funcs(new FuncPtr[num_funcs]), moved(false)
{
	memcpy(var_sizes, p_sizes.data(), num_vars*sizeof(size_t));
	
	// force vars be stored in a contiguous memory for performance
	char* j = (char*)var_storage;
	for (unsigned int i = 0; i < num_vars; i++)
	{
		vars[i] = (VarPtr)j;
		memcpy((VarPtr)j, ps[i], var_sizes[i]);
		free(ps[i]);
		j += var_sizes[i];
	}

	memset(funcs, 0, num_funcs*sizeof(FuncPtr)); // initialize as nullptr
	unsigned int actual_num_funcs = f_indices.size();
	for (unsigned int i = 0; i < actual_num_funcs; i++)
		funcs[f_indices[i]] = fs[i];
}

GiglConfig::GiglConfig(const GiglConfig& config)
	: num_vars(config.num_vars), num_funcs(config.num_funcs), total_var_size(config.total_var_size), var_sizes(new size_t[num_vars]), var_storage(malloc(total_var_size)), vars(new VarPtr[num_vars]), funcs(new FuncPtr[num_funcs]), moved(false)
{
	memcpy(var_sizes, config.var_sizes, num_vars*sizeof(size_t));

	memcpy(var_storage, config.var_storage, total_var_size);	
	
	char* j = (char*)var_storage;
	for (unsigned int i = 0; i < num_vars; i++)
	{
		vars[i] = (VarPtr)j;
		j += var_sizes[i];
	}

	memcpy(funcs, config.funcs, num_funcs*sizeof(FuncPtr));
}

GiglConfig::GiglConfig(GiglConfig&& config)
	: num_vars(config.num_vars), num_funcs(config.num_funcs), total_var_size(config.total_var_size), var_sizes(config.var_sizes), var_storage(config.var_storage), vars(config.vars), funcs(config.funcs), moved(false)
{
	// prevent unwanted deallocation	
	config.moved = true;
}

void GiglConfig::operator = (const GiglConfig& config)
{
	Destruct(); // remove original content, if any
	
	num_vars = config.num_vars;
	num_funcs = config.num_funcs;
	total_var_size = config.total_var_size;
	var_sizes = new size_t[num_vars];
	var_storage = malloc(total_var_size);
	vars = new VarPtr[num_vars];
	funcs = new FuncPtr[num_funcs];
	moved = false;

	memcpy(var_sizes, config.var_sizes, num_vars*sizeof(size_t));

	memcpy(var_storage, config.var_storage, total_var_size);

	char* j = (char*)var_storage;
	for (unsigned int i = 0; i < num_vars; i++)
	{
		vars[i] = (VarPtr)j;
		j += var_sizes[i];
	}

	memcpy(funcs, config.funcs, num_funcs*sizeof(FuncPtr));
}

void GiglConfig::operator = (GiglConfig&& config)
{	
	Destruct(); // remove original content, if any

	num_vars = config.num_vars;
	num_funcs = config.num_funcs;
	total_var_size = config.total_var_size;
	var_sizes = config.var_sizes;
	var_storage = config.var_storage;
	vars = config.vars;
	funcs = config.funcs;
	moved = false;
	
	// prevent unwanted deallocation	
	config.moved = true;
}

GiglConfig::~GiglConfig()
{
	Destruct();
}

void GiglConfig::Destruct()
{
	if (!moved)
	{
		delete[] var_sizes;
		free(var_storage);
		delete[] vars;
		delete[] funcs;
	}
}
