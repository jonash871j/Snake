#include "Import.h"
#include <fstream>
char fileformat[3] = { 0 };

void Import::ImportACXSPR(std::string filename)
{
	int width, height;
	// Opens and checks if file is valid
	std::ifstream inFile;
	inFile.open(filename + ".acxspr");
	if (inFile.fail())
		return;

	// Checks the filefomat if it's valid
	for (int i = 0; i < 3; i++)
		fileformat[i] = '0';
	inFile.read(fileformat, 3);
	std::string fileCheck(fileformat);
	if (fileCheck != "ACX") return;

	// Reads sprite infomation
	inFile >> width;
	inFile.ignore(1, ' ');
	inFile >> height;

	// Reads the chracter array
	for (int i = 0; i < height; i++)
		inFile.read(characterArray[i], width);

	// Reads the color array
	for (int i = 0; i < height; i++)
		inFile.read(colorArray[i], width);

	// Closes file
	inFile.close();
}

void Import::ImportMAP(std::string filename)
{
	int width, height;
	// Opens and checks if file is valid
	std::ifstream inFile;
	inFile.open("./Map/" + filename + ".acxspr");
	if (inFile.fail())
		return;

	// Checks the filefomat if it's valid
	for (int i = 0; i < 3; i++)
		fileformat[i] = '0';
	inFile.read(fileformat, 3);
	std::string fileCheck(fileformat);
	if (fileCheck != "ACX") return;

	// Reads sprite infomation
	inFile >> width;
	inFile.ignore(1, ' ');
	inFile >> height;
	inFile.ignore(1, ' ');

	// Reads the chracter array
	for (int i = 0; i < height; i++)
		inFile.read(mapArray[i], width);
	inFile.close();
}

void Import::ImportACCPAL(std::string filename)
{
	char accpalFormat[4] = { 'A', 'C', 'C', 'P' };
	char fileCheck[4];

	// Opens and checks if file is valid
	std::ifstream inFile;
	inFile.open(filename + ".accpal");
	if (inFile.fail())
		return;

	// Reads ACCP in the start as a file identifier
	inFile.read(fileCheck, 4);
	for (int i = 0; i < 4; i++)
		if (fileCheck[i] != accpalFormat[i])
			return;

	// Begins to read the colorArray from file
	for (int y = 0; y < 16; y++)
		inFile.read(colorPaletteArray[y], 3);

	inFile.close();
}