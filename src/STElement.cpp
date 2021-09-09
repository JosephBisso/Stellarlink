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
    BallXPosition = 250,
    BallYStartPosition = 400,
    FloorMittelPosition = 600
};
