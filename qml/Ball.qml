import QtQuick 2.0


Rectangle {
    id: ball
    x: ballLogik.pos_x < 250 ? ballLogik.pos_x - width / 2 : 250 - width / 2
    y: ballLogik.pos_y - 0.8 * width
    width: ballLogik.radius * 2
    height: width
    color: "pink"
    border {
        color: "black"
        width: 3
    }
    radius: width * 0.5

    property color trailColor: accelerationGlow.color
    property double actualSpeed: ballLogik.velocityX
    property double maxSpeed: stellarEngine.maxVelocity
    property double actualHeigth: ballLogik.heigth
    property double maxHeigth: stellarEngine.maxHeigth
    property double health: ballLogik.health

    Rectangle {
        id: kreuzMitte
        anchors.centerIn: parent
        z: 1
        height: 25
        width: 2
        color: "black"

        RotationAnimation on rotation {
            id: rolling
            running: ball.actualSpeed > 3
            loops: Animation.Infinite
            from: 0
            to: 360
        }
    }

    Rectangle {
        id: accelerationGlow
        x: -(width - ball.width) / 2
        y: x
        z: -1
        opacity: 0
        width: ball.width + ball.border.width + 4
        height: width
        radius: width * 0.5
        color: "transparent"
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
                    PropertyChanges { target: accelerationGlow; color: "transparent"; opacity: 0}
                },
                State {
                    name: "Accelerate"
                    PropertyChanges { target: accelerationGlow; color: "darkred"; opacity: 75}
                },
                State {
                    name: "Decelerate"
                    PropertyChanges { target: accelerationGlow; color: "lightsteelblue"; opacity: 80}
                },
                State {
                    name: "Stick"
                    PropertyChanges { target: accelerationGlow; color: "darkblue"; opacity: 50}
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
    }

    function resetState() {
        accelerationGlow.state = "Default"
        accelerationGlow.color = "transparent"
    }

    function decelerate() {
        accelerationGlow.state = "Decelerate"
    }

    function stick() {
        accelerationGlow.state = "Stick"
    }

}
