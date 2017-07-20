#include "AST.hpp"

#include <cassert>

// Prototype
void assign_cstring(char* dest, const char* src);

AST::AST()
	: dataType(DUMMY), dataValue(0), root(0), branches(0), capacity(0), size(0)
{
}

AST::AST(ASTType type, const char* value, AST* _root)
	: dataType(type), dataValue(0), root(_root), branches(0), capacity(0), size(0)
{
	assign_cstring(dataValue, value);

	if (!root) {
		root = this;
	}
}

AST::~AST()
{
	if (dataValue) {
		delete[] dataValue;
		dataValue = 0;
	}

	if (branches) {
		for (unsigned int i = 0; i < size; ++i) {
			if (branches[i]) {
				delete branches[i];
				branches[i] = 0;
			}
		}
		
		delete[] branches;
		branches = 0;
	}
}

AST* AST::Add(ASTType type, const char* value)
{
	if (!branches) {
		branches = new AST*[2];
		capacity = 2;

		branches[0] = new AST(type, value, this);
		branches[1] = 0;
		size = 1;

		return branches[0];
	}

	if (capacity == size) {
		Reallocate(capacity + 2);
	}

	for (unsigned int i = 0; i < capacity; ++i) {
		if (!branches[i]) {
			branches[i] = new AST(type, value, this);
			++size;

			return branches[i];
		}
	}
	return nullptr;
}

void AST::Destroy()
{
	delete root;
	root = 0;
}

ASTType AST::GetType() const
{
	return dataType;
}

const char* AST::GetValue() const
{
	return dataValue;
}

void AST::Reallocate(unsigned int newSize)
{
	assert(branches);
	assert(newSize > capacity);

	AST** oldBranches = branches;
	
	branches = new AST*[newSize];
	capacity = newSize;

	// Copy all the old branches into the new
	// array.
	for (unsigned int i = 0; i < size; ++i) {
		branches[i] = oldBranches[i];
	}

	// Initialize the remaining currently unused
	// space to 0.
	for (unsigned int i = size; i < capacity; ++i) {
		branches[i] = 0;
	}

	delete[] oldBranches;
	oldBranches = 0;
}

AST*& AST::operator[](int index)
{
	assert(index >= 0);
	if (static_cast<unsigned int>(index) >= capacity) {
		throw "array index out of bounds";
	}

	return branches[index];
}
