const double cubePos[] = {-1, -1, -1,    // 0
                          -1, -1, 1,     // 1
                          -1, 1, -1,     // 2
                          -1, 1, 1,      // 3
                          1, -1, -1,     // 4
                          1, -1, 1,      // 5
                          1, 1, -1,      // 6
                          1, 1, 1};      // 7
const unsigned int cubeIdx[] = {0, 1, 2, //(-1,y,z) -> left
                                0, 2, 3,
                                4, 5, 6, //(1,y,z) -> right
                                5, 6, 7,
                                0, 2, 4, //(x,y,-1) -> bottom
                                2, 4, 6,
                                1, 3, 5, //(x,y,1) -> up
                                3, 5, 7,
                                0, 1, 4, //(x,-1,z) -> back
                                1, 4, 6,
                                2, 3, 6, //(x,1,z) -> forward
                                3, 6, 7};
const double squarePos[] = {
    1, 1, 0,  // 0
    1, -1, 0, // 1
    -1, 1, 0, // 2
    -1, -1, 0 // 3
};
const unsigned int squareIdx[]{
    0, 1, 2,
    1, 2, 3};