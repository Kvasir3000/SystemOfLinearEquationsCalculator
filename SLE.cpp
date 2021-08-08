#include "SLE.h"
#include <iostream>


int SLE::findBorder(std::string* eq, int lBorder) 
{
	int border = eq->find('+', lBorder);
	if (border == -1)
	{
		border = eq->find('-', lBorder);
		return (border < eq->find('=')) ? border : -1;
	}
	else
	{
		int temp = eq->find('-', lBorder);
		if (temp == -1)
			return border;

		return (border < temp) ? border : temp;
	}
};

bool SLE::setNegFlag(std::string* arr, int& lBorder)
{
	if (arr[lBorder] == "-")
		return true;

	else if (lBorder != 0 && arr->substr(lBorder - 1, 1) == "-")
		return true;

	else
		return false;
};

void SLE::extractNumbersAndVariables(
	std::string& subString,
	std::vector <double>* numbers,
	std::vector<std::string>& variables,
	bool negSign)
{
	std::string str;
	for (int j = 0; j < subString.size(); j++)
	{
		if (!isdigit(subString[j]) && subString[j] != '.')
		{
			str = subString.substr(j, subString.size() - j);
			if ((j - 1) < 0)
			{
				variables.emplace_back(str);
				if (negSign)
				{
					numbers->emplace_back(-1.0);
					break;
				}
				else
				{
					numbers->emplace_back(1.0);
					break;
				}
			}

			variables.emplace_back(str);
			std::string number = subString.substr(0, j);
			if (negSign)
			{
				numbers->emplace_back(-std::stod(number));
				break;
			}
			else
			{
				numbers->emplace_back(std::stod(number));
				break;
			}
		}
	}
};

void SLE::equalSignBorderAnalysis(
	int& index,
	int& rBorder,
	int& lBorder,
	bool& negFlag,
	std::string subString,
	int& length)
{
	rBorder = equations[index].equation.find('=');
	length = rBorder - lBorder;
	subString = equations[index].equation.substr(lBorder, length);
	negFlag = setNegFlag(&equations[index].equation, lBorder);
	extractNumbersAndVariables(subString, &equations[index].coefficients, equations[index].variables, negFlag);
	lBorder = rBorder + 1;

	rBorder = equations[index].equation.size();
	length = rBorder - lBorder;
	subString = equations[index].equation.substr(lBorder, length);
	equations[index].coefficients.push_back(atoi(subString.c_str()));
	lBorder = rBorder = 0;
};

void SLE::equationParser()
{
	int lBorder = 0, rBorder = 0, length = 0;
	bool flag = true, negFlag;
	std::string subString;
	for (int i = 0; i < numberOfEquations; i++)
	{
		negFlag = false;
		length = rBorder = findBorder(&equations[i].equation, 0);
		if (rBorder == -1 && equations[i].equation.find('=') == -1)
		{
			std::cout << "Error! Examine the input and try again";
			break;
		}
		else if (rBorder == -1) equalSignBorderAnalysis(i, rBorder, lBorder, negFlag, subString, length);
		else
		{
			while (flag)
			{
				subString = equations[i].equation.substr(lBorder, length);
				negFlag = setNegFlag(&equations[i].equation, lBorder);
				extractNumbersAndVariables(subString, &equations[i].coefficients, equations[i].variables, negFlag);

				lBorder = rBorder + 1;
				rBorder = findBorder(&equations[i].equation, lBorder);

				if (rBorder == -1)
					flag = false;
				else
					length = rBorder - lBorder;
			}

			equalSignBorderAnalysis(i, rBorder, lBorder, negFlag, subString, length);
			flag = true;
		}
	}
};

int SLE::longestEquation()
{
	int index = 0, maxVar = 0;
	for (int i = 0; i < numberOfEquations; i++)
	{
		if (equations[i].coefficients.size() > maxVar)
		{
			maxVar = equations[i].coefficients.size();
			index = i;
		}
	}
	return index;
};

void SLE:: createAugmentedMatrix()
{
	bool emplace;
	int longest = longestEquation();

	for (int i = 0; i < numberOfEquations; i++)
	{
		if (i == longest);
		else
		{
			for (int j = 0; j < equations[i].variables.size(); j++)
			{
				emplace = true;
				for (int k = 0; k < equations[longest].variables.size(); k++)
				{
					if (equations[longest].variables[k] == equations[i].variables[j])
					{
						emplace = false;
						break;
					}
				}
				if (emplace)
				{
					equations[longest].variables.emplace_back(equations[i].variables[j]);
					equations[longest].coefficients.insert(equations[longest].coefficients.end() - 1, 0);
				}
			}
		}

		for (int i = 0; i < numberOfEquations; i++)
		{
			if (i == longest);
			else
			{
				for (int j = 0; j < equations[longest].variables.size(); j++)
				{
					emplace = true;
					for (int k = 0; k < equations[i].variables.size(); k++)
					{
						if (equations[longest].variables[j] == equations[i].variables[k])
						{
							emplace = false;
							break;
						}
					}
					if (emplace)
					{
						equations[i].variables.emplace_back(equations[longest].variables[j]);
						equations[i].coefficients.insert(equations[i].coefficients.end() - 1, 0);
					}
				}
			}
		}
	}
	sortMatrix();

	augmentedMatrix = new double* [equations.size()];
	for (int i = 0; i < equations.size(); i++)
	{
		augmentedMatrix[i] = new double[equations[i].coefficients.size()];
		for (int j = 0; j < equations[i].coefficients.size(); j++)
			augmentedMatrix[i][j] = equations[i].coefficients[j];
	}
};

void SLE::sortMatrix()
{
	for (int i = 0; i < numberOfEquations; i++)
	{
		for (int j = 0; j < equations[i].variables.size() - 1; j++)
		{
			for (int k = 0; k < equations[i].variables.size() - j - 1; k++)
			{
				if (equations[i].variables[k] > equations[i].variables[k + 1])
				{
					swap(equations[i].variables[k], equations[i].variables[k + 1]);
					swap(equations[i].coefficients[k], equations[i].coefficients[k + 1]);
				}
			}
		}
	}
};

void SLE::swapRows(int& row1Index, int& row2Index)
{
	for (int i = 0; i < equations[0].coefficients.size(); i++)
		swap(augmentedMatrix[row1Index][i], augmentedMatrix[row2Index][i]);
};

void SLE::findFirstNonZeroColumn(int& firstRowIndex)
{
	bool nonZero = false;
	int temp = 0;
	for (int i = 0; i < equations[0].coefficients.size(); i++)
	{
		for (int j = firstRowIndex; j < numberOfEquations; j++)
		{
			if (augmentedMatrix[j][i] != 0)
			{
				nonZero = true;
				temp = j;
				break;
			}
		}
		if (nonZero)
		{
			if (temp != firstRowIndex) swapRows(firstRowIndex, temp);
			break;
		}
	}
};

void SLE:: leadingOne(int& rowIndex)
{
	double factor = 1.0;
	for (int i = 0; i < equations[0].coefficients.size(); i++)
	{
		if (augmentedMatrix[rowIndex][i] != 0)
		{
			factor = augmentedMatrix[rowIndex][i];
			break;
		}
	}

	for (int i = 0; i < equations[0].coefficients.size(); i++)
		augmentedMatrix[rowIndex][i] /= factor;
};

void SLE::addRows(int& rowIndex)
{
	int columnIndex = 0;
	double factor = 1;
	for (int i = 0; i < equations[0].coefficients.size(); i++)
	{
		if (augmentedMatrix[rowIndex][i] != 0)
		{
			columnIndex = i;
			break;
		}
	}

	for (int i = rowIndex + 1; i < numberOfEquations; i++)
	{
		if (augmentedMatrix[i][columnIndex] != 0)
		{
			factor = -augmentedMatrix[i][columnIndex];
			for (int j = columnIndex; j < equations[0].coefficients.size(); j++)
				augmentedMatrix[i][j] += (augmentedMatrix[rowIndex][j] * factor);
		}
	}
};

void SLE::addRowsReverse(int& rowIndex)
{
	int columnIndex = -1;
	double factor = 1;
	for (int i = 0; i < equations[0].coefficients.size() - 1; i++)
	{
		if (augmentedMatrix[rowIndex][i] != 0)
		{
			columnIndex = i;
			break;
		}
	}

	if (columnIndex != -1)
	{
		for (int i = rowIndex - 1; i > -1; i--)
		{
			if (augmentedMatrix[i][columnIndex] != 0)
			{
				factor = -augmentedMatrix[i][columnIndex];
				for (int j = columnIndex; j < equations[0].coefficients.size(); j++)
				{
					double var = (augmentedMatrix[rowIndex][j] * factor);
					augmentedMatrix[i][j] += var;
				}
			}
		}
	}
};

void SLE::gausianElimination()
{
	for (int i = 0; i < numberOfEquations; i++)
	{
		findFirstNonZeroColumn(i);
		leadingOne(i);
		addRows(i);
	}
};

void SLE::gaussJordanElimination()
{
	gausianElimination();
	for (int i = numberOfEquations - 1; i > -1; i--)
		addRowsReverse(i);
};

void SLE::hasSolutions()
{
	int size = equations[0].coefficients.size();
	for (int i = numberOfEquations - 1; i > -1; i--)
	{
		noSolutionsFlag = true;
		for (int j = 0; j < size - 1; j++)
		{
			int n = augmentedMatrix[i][j];
			if (augmentedMatrix[i][j] != 0)
			{
				noSolutionsFlag = false;
				break;
			}
		}
		if (noSolutionsFlag && augmentedMatrix[i][size - 1] != 0)
			break;
		else
			noSolutionsFlag = false;
	}
};

void SLE::generateSolutionStr()
{
	bool leadingOneFlag = false;
	std::string equation;
	int size = equations[0].coefficients.size();
	if (!noSolutionsFlag)
	{
		for (int i = 0; i < numberOfEquations; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (augmentedMatrix[i][j] == 1 && !leadingOneFlag)
				{
					leadingOneFlag = true;
					equation = equations[0].variables[j] + "=";
					if (augmentedMatrix[i][size - 1] != 0)
						equation += std::to_string(augmentedMatrix[i][size - 1]);
				}
				else if (leadingOneFlag && augmentedMatrix[i][j] != 0)
				{
					if (equation[equation.size() - 1] == '=')
						equation += std::to_string(-augmentedMatrix[i][j]) + equations[0].variables[j];
					else
					{
						equation += (augmentedMatrix[i][j] < 0) ? "+" + std::to_string(-augmentedMatrix[i][j]) : std::to_string(-augmentedMatrix[i][j]);
						equation += equations[0].variables[j];
					}
				}
			}

			if (augmentedMatrix[i][size - 1] == 0 && equation[equation.size() - 1] == '=')
				equation += std::to_string(augmentedMatrix[i][size - 1]);

			solution.emplace_back(equation);
			equation = " ";
			leadingOneFlag = false;
		}
	}
	else
		solution.emplace_back("There are no solutions for this system");
};


SLE::SLE(int numberOfEquations) { this->numberOfEquations = numberOfEquations; };

std::vector<std::string> SLE::operator << (std::string* arr)
{
	for (int i = 0; i < numberOfEquations; i++)
	{
		Equation equation;
		equations.emplace_back(equation);
		equations[i].equation = arr[i];
	}
	equationParser();
	createAugmentedMatrix();
	gaussJordanElimination();
	hasSolutions();
	generateSolutionStr();
	return solution;
};

Equation& SLE::operator [] (int index) { return equations[index]; };

std::vector<std::string> SLE::getSolution() { return solution; };

SLE::~SLE() { delete augmentedMatrix; };