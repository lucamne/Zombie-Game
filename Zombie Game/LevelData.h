#pragma once

#include <vector>
#include <string>

struct LevelData
{
	// holds tile data for level
	std::vector<std::string> data{};
	// width of each tile
	int block_width{};
	// height of each tile
	int block_height;
};