import QtQuick 2.0
import QtQuick.Controls 2.15
import "JScript.js" as JS

Frame {
    id: rootFrame
    width: 75
    height: width
    opacity: 0.5

    background: Rectangle {
        id: rectangleBackgroung
        anchors.fill: parent
        color: "blue"
        radius: 25
        border {
            width: 10
            color: "blue"
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {JS.ligth(rootFrame); JS.hoverButton(rectangleBackgroung)}
        onExited: {JS.resetLigth(rootFrame); JS.notHoverAnymore(rectangleBackgroung)}
        onClicked: (event) => {
                       if (event.button === Qt.LeftButton) {
                           field.pause()
                           drawer.open()
                           event.accepted = true;
                       }
                   }
    }

    Column {
        id: bars
        anchors.centerIn: parent
        spacing: 7.5
        Repeater {
            model: 3
            Rectangle {
                width:  rootFrame.width - 25
                height: bars.spacing
                color: "white"
                radius: 5
            }
        }
    }

    Behavior on opacity {NumberAnimation{duration: 50}}
}
