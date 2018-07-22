#include <fstream>
#include <iostream>
#include <climits>
#include <utility>
#include "MinstTools/MinstImgDataSet.hpp"
#include "MinstTools/MinstLabelDataSet.hpp"
#include "BMPTools/BMPGrayscaleImg.hpp"
#include "BMPTools/Utils.h"

static inline std::string getFileName(
	std::string dir,
	uint8_t label,
	size_t index)
{
	return
		dir + "/" + std::to_string(label) + "_" +
		std::to_string(index) + ".bmp";
}

void convertMINSTImages(
	MinstTools::MinstImgDataSet& imgDataset,
	const MinstTools::MinstLabelDataSet& labelDataSet,
	const std::string resultDir,
	size_t maxNbOfImgs)
{
	for (size_t i = 0; i < maxNbOfImgs && i < imgDataset.getNbOfImages(); i++)
	{
		const auto label = labelDataSet.getLabels()[i];
		const auto flipedImg =
			flipBMPPixels(
				imgDataset.getImages()[i],
				imgDataset.getWidth(),
				imgDataset.getHeight());

		const auto grayscaleImg = BMPTools::BMPGrayscaleImg(
			imgDataset.getWidth(),
			imgDataset.getHeight(),
			flipedImg);

		try
		{
			grayscaleImg.print(getFileName(resultDir, label, i).c_str());
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void convertMINSTImages(
	const char* imgDatasetFilePath,
	const char* labelDatasetFilePath,
	const std::string resultDir,
	size_t maxNbOfImgs)
{
	try
	{
		auto imgDataset = MinstTools::MinstImgDataSet(imgDatasetFilePath);
		auto labelDataSet = MinstTools::MinstLabelDataSet(labelDatasetFilePath);
		
		if (imgDataset.getNbOfImages() != labelDataSet.getNbOfItems())
		{
			std::cerr <<
				"Number of images and labels don't match." << std::endl;
			exit(EXIT_FAILURE);
		}
		
		convertMINSTImages(imgDataset, labelDataSet, resultDir, maxNbOfImgs);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

static inline void printInvalidArgimentsMsg(std::ostream& o)
{
	o <<
		"Invalid arguments" << std::endl <<
		"arg 1) MINST image data set" << std::endl <<
		"arg 2) MINST label data set" << std::endl <<
		"arg 3) result directory" << std::endl <<
		"arg 4) [optional] max number of images to convert" << std::endl;
}

static inline size_t getMaxNbOfImgs(int argc, const char* strNb)
{
	if (argc > 4)
	 	return std::stoi(strNb);
	else
	 	return std::numeric_limits<size_t>::max();
}

int main(const int argc, const char** argv)
{
	if (argc < 3)
	{
		printInvalidArgimentsMsg(std::cerr);
		exit(EXIT_FAILURE);
	}

	auto resultDir = std::string(argv[3]);
	auto maxNbOfImgs = getMaxNbOfImgs(argc, argv[4]);
	convertMINSTImages(argv[1], argv[2], resultDir, maxNbOfImgs);
	
	return EXIT_SUCCESS;
}
