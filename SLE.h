#ifndef SYSTEM_OF_LINEAR_EQUATIONS 
#define SYSTEM_OF_LINEAR_EQUATIONS

#include <vector>
#include <string>


struct Equation
{
	std::vector<double> coefficients; // vector to store the coefficients of the equation (each coefficient corresponds to each varible in variables vector)
	std::string equation;
	std::vector<std::string> variables; // variables of the equation 
};

class SLE
{

private:
	int numberOfEquations; 
	std::vector<Equation> equations; 
	double** augmentedMatrix; 
	bool noSolutionsFlag = false; // true if equation does not have solutions 
	std::vector<std::string> solution; // vector which stores the solution of the system

	/*
		Each equation of the system is given in a string format, before solving the system, it
		is important to analyse the input data, highlight the essential parts of the equation and convert them to the needed types. To do this, 
		the equation is broken into smaller parts, the parser function contains the lBorder and rBorder integer varriables, which represent the
		indexes of the leftmost and the rightmost elements of the substring respectively. The generated substring has to contain the variable 
		its coefficient, which will be seperated and stored into the coefficients vector and variables vector inside the equation object.  
	*/
	void equationParser();

	/*
		This function is part of the parsing process, used to find the new value of the rBorder for the new substring. 
		Function looks for the first '-' or '+' sign that comes across, starting from the lBorder index, and returns the found index.
	*/
	int findBorder(std::string* eq, int lBorder);
	
	/*
		This function is part of the parsing process, it is used to set the signs of equation coefficients. 
	*/
	bool setNegFlag(std::string* arr, int& lBorder);
	

	/*
		This function is part of the parsing process, it used to extract variables and numbers, which represt the coefficients, from a given substring and 
		save them into corresponding vectors of the eqution variable. 
	*/
	void extractNumbersAndVariables(
		std::string& subString,
		std::vector <double>* numbers,
		std::vector<std::string>& variables,
		bool negSign);


	/*
		This function is part of the parsing process, it used to analyse the last part of the equation, when '=' sign is occured
	*/
	void equalSignBorderAnalysis(
		int& index,
		int& rBorder,
		int& lBorder,
		bool& negFlag,
		std::string subString,
		int& length);

	/*
		This function finds the lngest equation in the system and returns its index 
	*/
	int longestEquation();

	/*
		This function creates the augmented matrix, based on the result of the equation parsing  
	*/
	void createAugmentedMatrix();

	template<typename T>
	void swap(T& var1, T& var2)
	{
		T temp = var1;
		var1 = var2;
		var2 = temp;
	}

	/*
		The same variables in each equation of the system might be positioned in different orders, because of this, the augmented matrix may be  
		constructed wrong and the equation will be solved wrong. To fix this, this function sorts the matrix accordinng to the alpabetic order of the variables 
		in the system.
	*/
	void sortMatrix();

	/*
		This function swaps the rows of the augmented matrix, this operation is needed for gaussian elimination 
	*/
	void swapRows(int& row1Index, int& row2Index);

	void findFirstNonZeroColumn(int& firstRowIndex);

	/*
		This function finds the first non zero element in a given row of and augmented matrix, and divides each element of the row by the found value.
	*/
	void leadingOne(int& rowIndex);

	void addRows(int& rowIndex);

	void addRowsReverse(int& rowIndex);

	void gausianElimination();

	void gaussJordanElimination();

	/*
		This function checks if the system has solution 
	*/
	void hasSolutions();

	void generateSolutionStr();

public:

	SLE(int numberOfEquations);
	
	/*
		This overloaded operator solves the equations and returs the solution as vector of strings 
	*/
	std::vector<std::string> operator << (std::string* arr);

	/*
		This operator is overloaded to get an access to each equation of the system individually
	*/
	Equation& operator [] (int index);

	std::vector<std::string> getSolution();

	~SLE();
};
#endif // !SYSTEM_OF_LINEAR_EQUATIONS 
