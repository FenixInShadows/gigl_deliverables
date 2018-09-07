#pragma once

#include <vector>

using namespace std;

typedef void* VarPtr;
typedef void(*FuncPtr)();

typedef VarPtr* VarPtrPtr;
typedef FuncPtr* FuncPtrPtr;

typedef vector<size_t> SizeVec;
typedef vector<VarPtr> VarPtrVec;
typedef vector<unsigned int> IndexVec;
typedef vector<FuncPtr> FuncPtrVec;
