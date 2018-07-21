#ifndef _SECRETMSGGENERATOR_H_
# define _SECRETMSGGENERATOR_H_

# include <fstream>
# include <iostream>

using OffsetType = uint16_t;

const bool kSeedRandom = false;
const int kSeedValue = 0;

typedef struct SecretCodifierModel
{
	std::ofstream*	outStream;
	const char*		secretMsg;

	SecretCodifierModel();
	~SecretCodifierModel();
} SecretCodifierModel;

void writeCodifiedText(SecretCodifierModel& model);

#endif