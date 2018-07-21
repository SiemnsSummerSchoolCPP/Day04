#include "SecretMsgGenerator.h"

SecretCodifierModel::SecretCodifierModel()
{
	srand(kSeedRandom ? kSeedValue : time(NULL));
}

SecretCodifierModel::~SecretCodifierModel()
{
	if (outStream != &std::cout)
	{
		outStream->flush();
		outStream->close();
		delete outStream;
	}
}