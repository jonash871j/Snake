#pragma once
#include "EngineCore.h"

class Import
{
protected:
	char** characterArray;
	char** colorArray;
	char colorPaletteArray[16][3];
	char** mapArray;

	void ImportACXSPR(std::string filename);
	void ImportACCPAL(std::string filename);
	void ImportMAP(std::string filename);
};

