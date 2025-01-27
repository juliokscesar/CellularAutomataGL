#pragma once

#include <stdint.h>

enum class GridImgFmt {
    GRAY,
    RGB
};

class Grid {
public:
    Grid(uint32_t rows, uint32_t cols);

    

private:
    uint32_t m_rows, m_cols;
    GridImgFmt m_fmt;
    uint8_t* m_gridImage;
    bool** m_gridCells;
};
