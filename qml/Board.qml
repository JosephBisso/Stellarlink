import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Frame {
    id: rootPane
    width: 350
    height: 150
    clip: true

    background: Rectangle {
        id: boardRectangle
        radius: 25
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: rootWindow.darkColor
        border{width: 10; color: Qt.lighter(rootWindow.darkColor, 1.3)}
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2

        Speedometer {
            id: speedometer
            Layout.topMargin: 10
            Layout.leftMargin: 25
        }

        Heightmeter {
            id: heightMeter
//            Layout.topMargin: 50
            Layout.leftMargin: 75
        }

        Rectangle {
            width: 25
            height: 25
            z: 2
            color: "transparent"

            Layout.topMargin: 80
            Layout.leftMargin: 100
            Label {
                id: textForActualSpeed
                text: +(counter.actualSpeed).toFixed(2) + " mph"
                color: "white"
                font.pixelSize: 16
                anchors.centerIn: parent
            }
        }

        Label {
            id: textForActualHeight

            Layout.topMargin: 85
            Layout.leftMargin: 75
            Layout.maximumWidth: 10
            property double actualHeigth: 0
            text: +(actualHeigth).toFixed(2) + " m"
            color: "white"
            font.pixelSize: 16
        }

    }

    Item{
        id: counter
        property  int counter: 1
        property double actualSpeed: 0
    }

    function updateSpeed(actualSpeed) {
        speedometer.moveNeedle(+actualSpeed.toFixed(1))
        counter.actualSpeed = (+actualSpeed.toFixed(1))
    }

    function updateMaxSpeed (maxSpeed) {
        speedometer.maxSpeed = +maxSpeed.toFixed(1)
    }

    function updateHeigth (actualHeigth) {
        heightMeter.moveNeedle(+actualHeigth.toFixed(1))
        textForActualHeight.actualHeigth = actualHeigth / 200

        let distance = ((ballLogik.pos_x - 100) / 1000)
        if ( distance / (25 * counter.counter) >= 1){
            runningStats.addPoint(distance * counter.actualSpeed * 10 / 25)
            counter.counter += 1
        }
    }

    function updateMaxHeigth (maxHeigth) {
        heightMeter.maxHeigth = +maxHeigth.toFixed(1)
    }

    function reset() {
        counter.counter = 1
        counter.actualSpeed = 3
        speedometer.reset()
        heightMeter.reset()
        textForActualHeight.actualHeigth = 1
    }
}
