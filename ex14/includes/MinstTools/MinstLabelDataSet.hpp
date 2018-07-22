#pragma once

#include <inttypes.h>

namespace MinstTools
{
	class MinstLabelDataSet
	{
	public:
		uint8_t getTypeOfData() const { return typeOfData; }
		uint8_t getNbOfDimensions() const { return nbOfDimensions; }
		int32_t getNbOfItems() const { return nbOfItems; }
		uint8_t const* getLabels() const { return labels; }
	
		MinstLabelDataSet(const char* filePath);
		~MinstLabelDataSet();

	private:
		uint8_t typeOfData;
		uint8_t nbOfDimensions;
		int32_t nbOfItems;
		uint8_t* labels = nullptr;
	};
}
