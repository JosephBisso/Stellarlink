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

enum Konstante {
    Feder,
    L0,
    Daempfer,
    Delta,
    Lambda1,
    Lambda2,
    C0,
    C1,
    C2
};

enum LevelParameter {
    BallMovingVelocity = 5,
    FloatingFrom = 15,
    MaxVelocity_1 = 25,
    MaxFallingVelocity_1 = MaxVelocity_1 * 3 / 5
};
