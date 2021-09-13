import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Frame {
    id: rootPane
    width: 350
    height: 150

    property color mColor: "black"

    background: Rectangle {
        radius: 25
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "transparent"
        border{width: 10; color: "grey"}
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2
//        columnSpacing: 25

        Label {
            text: "HEALTH"
            font.weight: Font.Bold
            font.pixelSize: 14
            color: mColor
        }

        HealthBar {
            id: healthBar
            Layout.leftMargin: -25
            Layout.topMargin: -23
            health: 89
        }

        Label {
            text: "SCORE"
            font.weight: Font.Bold
            font.pixelSize: 14
            color: mColor
        }

        Label {
            id: textForScore
            property int score: 0
            text: score - 13 > 0 ? String(score - 13).padStart(8, '0') : String(0).padStart(8, '0')
            font.pixelSize: 16
            font.italic: true
            color: mColor

            ShowingBehaviour on text{}
        }

        Label {
            text: "MAX. SPEED"
            font.weight: Font.Bold
            font.pixelSize: 14
            color: mColor
        }

        Label {
            id: textForMaxSpeed
            property double maxSpeed: 24.56
            text: String(maxSpeed).padStart(6, '0') + " mph"
            font.pixelSize: 16
            font.italic: true
            color: mColor

            ShowingBehaviour on text{}
        }

        Label {
            text: "MAX. HEIGTH"
            font.weight: Font.Bold
            font.pixelSize: 14
            color: mColor
        }

        Label {
            id:textForMaxHeigth
            property double maxHeigth: 100
            text: String(maxHeigth).padStart(8, '0') + " m"
            font.pixelSize: 16
            font.italic: true
            color: mColor

            ShowingBehaviour on text{}
        }

        Label {
            text: "DISTANCE"
            font.weight: Font.Bold
            font.pixelSize: 14
            color: mColor
        }

        Label {
            id:textForDistance
            Layout.maximumWidth: 20
            property double distance: (ballLogik.pos_x - 100) / 1000
            text: String(+distance.toFixed(2)).padStart(8, '0') + " m"
            font.pixelSize: 16
            font.italic: true
            color: mColor
        }

    }

    function updateMaxSpeed(maxSpeed) {
        textForMaxSpeed.maxSpeed = +maxSpeed.toFixed(2)
        addPoint((maxSpeed / 30) * 10)
    }

    function updateMaxHeigth(maxHeigth) {
        let converted = maxHeigth / 200
        textForMaxHeigth.maxHeigth = +converted.toFixed(2)
        addPoint((converted / 2) * 10)
    }

    function updateHealth(health) {
        healthBar.health = health
    }

    function addPoint(point) {
        textForScore.score += point;
    }

    function reset() {
        textForScore.score = 0;
    }

    function keepTrack() {
        return [healthBar.health, textForScore.text, textForMaxSpeed.text, textForMaxHeigth.text]
    }

    function loadStats(health, score, speed, height) {
        [healthBar.health, textForScore.text, textForMaxSpeed.text, textForMaxHeigth.text] = [health, score, speed, height]
    }
}
