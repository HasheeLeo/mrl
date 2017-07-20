#ifndef AST_HPP
#define AST_HPP

enum ASTType
{
	DUMMY,
	DATUM,
	FUNCTION,
	LITERAL,
	OPERATOR,
	VARIABLE
};

class AST
{
private:
	AST* root;
	AST** branches;
	unsigned int capacity;
	unsigned int size;

	const ASTType dataType;
	char* dataValue;

	void Reallocate(unsigned int newSize);

public:
	AST();
	AST(ASTType type, const char* value, AST* _root = 0);
	~AST();

	AST* Add(ASTType type, const char* value);
	void Destroy();

	ASTType GetType() const;
	const char* GetValue() const;

	AST*& operator[](int index);
};

#endif // AST_HPP
