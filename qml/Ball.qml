import QtQuick 2.15


Rectangle {
    id: ball
    x: ballLogik.pos_x < 250 ? ballLogik.pos_x - width / 2 : 250 - width / 2
    y: ballLogik.pos_y - 0.8 * width
    width: ballLogik.radius * 2
    height: width
    color: Qt.lighter("gray", 1.3)
    border {
        color: "black"
        width: 4
    }
    radius: width * 0.5

    property color trailColor: accelerationGlow.color
    property double actualSpeed: ballLogik.velocityX
    property double maxSpeed: stellarEngine.maxVelocity
    property double actualHeigth: ballLogik.heigth
    property double maxHeigth: stellarEngine.maxHeigth
    property double health: ballLogik.health


//    RotationAnimation on rotation {
//        id: rolling
//        running: ball.actualSpeed > 3
//        loops: Animation.Infinite
//        from: 0
//        to: 360
//    }

    Rectangle {
        id: accelerationGlow
        x: -(width - ball.width) / 2
        y: x
        z: -1
        opacity: 0.25
        width: ball.width + ball.border.width + 4
        height: width
        radius: width * 0.5
        color: ball.color
        border {
            color: Qt.lighter(color, 1.5)
            width: 3
        }

        Behavior on opacity {
            NumberAnimation {duration: 1000}
        }

        Behavior on color {
            ColorAnimation {duration: 1000}
        }


        states: [
                State {
                    name: "Default"
                    PropertyChanges { target: accelerationGlow; color: ball.color; opacity: 0.55}
                },
                State {
                    name: "Accelerate"
                    PropertyChanges { target: accelerationGlow; color: "darkred"; opacity: 0.75}
                },
                State {
                    name: "Decelerate"
                    PropertyChanges { target: accelerationGlow; color: "lightsteelblue"; opacity: 0.80}
                },
                State {
                    name: "Stick"
                    PropertyChanges { target: accelerationGlow; color: "darkblue"; opacity: 0.50}
                }
            ]

        transitions: [
            Transition {
                to: "Accelerate"
                ColorAnimation {duration: 1000}

            },

            Transition {
                to: "Stick"
                ColorAnimation {duration: 750}

            },

            Transition {
                to: "Decelerate"
                ColorAnimation {duration: 750}

            },

            Transition {
                to: "Default"
                NumberAnimation {duration: 750}
                ColorAnimation {duration: 1000}

            }
        ]

    }

    function accelerate() {
        accelerationGlow.state = "Accelerate"
        accelerationSound.play()

    }

    function resetState() {
        accelerationGlow.state = "Default"
        if (accelerationSound.playing){accelerationSound.stop()}
        if (decelerationSound.playing){decelerationSound.stop()}
        if (ballStickSound.playing){ballStickSound.stop()}
    }

    function decelerate() {
        accelerationGlow.state = "Decelerate"
        decelerationSound.play()
    }

    function stick() {
        accelerationGlow.state = "Stick"
        ballStickSound.play()
    }

}
