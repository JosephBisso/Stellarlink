import QtQuick 2.0

Item {
    property int health: 100
    property color hitColor: "red"
    Rectangle {
        id: mainBar
        height: 25
        width: 150
        border {
            width: 3;
            color: "black"
        }
        color: Qt.hsla(hitColor.hslHue, hitColor.hslSaturation, hitColor.hslLightness, 0.3)
        radius: 6

        Rectangle {
            id: remainingHealth

            anchors {
                left: parent.left
                top: parent.top
                margins: parent.border.width
            }

            border{width: 1; color: "black"}

            width: (parent.width - 2 * parent.border.width) * health / 100
            height: parent.height - 2 * parent.border.width
//            radius: 4

            color: "green"

            Behavior on width {
                NumberAnimation {
                    duration: 500
                }
            }
        }
    }
}
