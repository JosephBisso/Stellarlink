import QtQuick 2.15

Item {
    id: rootItem
    property double maxHeigth: 100

    Rectangle {
        id: meter
        width: 25
        height: 100
        color: "transparent"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop{position: 0.0; color: "darkred"}
            GradientStop{position: 1/10; color: "red"}
            GradientStop{position: 1/4; color: meter.color}
            GradientStop{position: 1.0; color: meter.color}
        }

        border {
            color: "white"
            width: 5
        }

        radius: 5
    }

    Rectangle {
        id: needle
        y: 60 * (meter.height - 13) / maxHeigth
        anchors{
            left: meter.left
        }
        width: meter.width + meter.border.width * 2
        height: 5
        radius: 5

        Behavior on y {NumberAnimation {duration: 300}}

        Rectangle {
            id: indicator
            anchors{
                left: needle.right
                leftMargin: - indicator.width / 2
                verticalCenter: needle.verticalCenter
            }
            width: meter.border.width * 2
            height: width
            radius: width / 2

        }
    }

    function moveNeedle(actualHeigth) {
        let converted = actualHeigth > 0 ? actualHeigth : 0
        let y = (meter.height * 9/10) * (1 - converted / maxHeigth)
        needle.y = y <= 0 ? meter.height * 1/10 :  y
    }

    function reset() {
        moveNeedle(400)
    }

}
