#include"ResetData.h"

void ResetAllData()
{
	for (unsigned int row = 0; row < height; row++)
	{
		for (unsigned int col = 0; col < width; col++)
		{
			map[row][col] = ' ';
			fog[row][col] = ' ';
		}
	}

}