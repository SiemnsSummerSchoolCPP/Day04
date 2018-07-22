#pragma once

#include <inttypes.h>
#include <istream>

namespace MinstTools
{
	class MinstImgDataSet
	{
	public:
		uint8_t getTypeOfData() const { return typeOfData; }
		int32_t getNbOfImages() const { return nbOfImages; }
		int32_t getWidth() const { return nbOfColumns; }
		int32_t getHeight() const { return nbOfRows; }
		uint8_t**  getImages() const { return images; }
	
		inline int totalNbOfPixels() const;

		MinstImgDataSet(const char* filePath);
		~MinstImgDataSet();
	
	private:
		uint8_t typeOfData;
		uint8_t nbOfDimensions;
		int32_t nbOfImages;
		int32_t nbOfRows;
		int32_t nbOfColumns;
		uint8_t** images = nullptr;
	
		void loadImages(std::istream& inStream);
	};
};

