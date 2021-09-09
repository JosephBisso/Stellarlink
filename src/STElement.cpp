#ifndef M_G
#define M_G (9.807)
#endif

enum struct STElement {
    Ball,
    Floor,
    BonusBox
};

enum struct FloorType {
    Grass,
    Glas,
    Normal
};

enum FieldSizes {
    Height = 750,
    Width = 1000,
    BallXStartPosition = 100,
    BallYStartPosition = 400,
    BallXPosition = 250,
    XSpaceRightOfBall = Width - BallXPosition,
    FloorMittelPosition = 600
};
