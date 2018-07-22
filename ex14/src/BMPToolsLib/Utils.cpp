#include <cstddef>
#include <cstdint>

uint8_t* flipBMPPixels(uint8_t* pixels, size_t widht, size_t height)
{
	for (size_t i = 0; i < height / 2; i++)
	{
		for (size_t j = 0; j < widht; j++)
		{
			const auto index1 = i * widht + j;
			const auto index2 = (height - i - 1) * widht + j;
			std::swap(pixels[index1], pixels[index2]);
		}
	}
	
	return pixels;
}
