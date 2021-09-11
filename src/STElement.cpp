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
    BallAcceleration = 2,
    BallDecelerationX = BallAcceleration * 6/5,
    BallDecelerationY = BallAcceleration * 2/3,
    BallFreeDeceleration = 1,
    BallMovingVelocity = 3,
    FloatingFrom = 15,
    MaxVelocity = 25,
    MaxFallingVelocity = MaxVelocity * 2 / 5
};

enum struct BallStates {
    None,
    Accelerating,
    Decelerating,
    Sticking
};

enum struct BallLocation {
    Launching,
    Falling,
    Ground
};
