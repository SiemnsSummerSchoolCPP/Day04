#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>

const int nbPadding = 10;
const int nbPrecision = 7;

double* requestMatrix(int& width, int& height)
{
	double*	matrix;

	std::cout << "Enter the width and height: " << std::endl;
	std::cin
		>> width
		>> height;

	if (width <= 0 || height <= 0)
	{
		std::cerr << "Invalid dimensions." << std::endl;
		throw EXIT_FAILURE;
	}

	matrix = new double[width * height];

	for (int i = 0; i < width * height; i++)
    {
		if (!(std::cin >> matrix[i]))
        {
            std::cerr << "Unexpected EOF." << std::endl;
            throw EXIT_FAILURE;
        }
    }
	std::cout << std::endl;
	return matrix;
}

static void printSqrBracedInt(std::ostream& o, int nb, int padding)
{
	std::stringstream ss;

    ss << "[" << nb << "]";
    o << std::setw(padding) << ss.str();
}

static void printColumnIndexes(
	std::ostream& o,
	const int matrixWidth,
	const int padding)
{
	std::cout << std::setw(padding) << "";
	for (int j = 0; j < matrixWidth; j++)
	{
		printSqrBracedInt(o, j, padding);
	}
	o << std::endl;
}

void printMatrix(
	const double* matrix,
	const int width,
	const int height)
{
	printColumnIndexes(std::cout, width, nbPadding);
    for (int i = 0; i < height; i++)
    {
        printSqrBracedInt(std::cout, i, nbPadding);
        for (int j = 0; j < width; j++)
        {
            auto index = i * width + j;
            std::cout
                << std::setw(nbPadding)
                << std::setprecision(nbPrecision)
                << matrix[index];
        }
        std::cout << std::endl;
    }
}

int main()
{
	double*	matrix;
	int		width;
	int		height;

	try
	{
		matrix = requestMatrix(width, height);
	}
	catch (const int e)
	{
		return e;
	}
	printMatrix(matrix, width, height);

	delete[] matrix;
	return EXIT_SUCCESS;
}
