import QtQuick 2.0
import QtQuick.Controls 2.15
import "JScript.js" as JS

Rectangle {
    id: root
    property int mWidth: 150
    property int mHeigth: 75
    property string mText: "Button"
    property bool mVisible: true

    width: mWidth
    height: mHeigth
    radius: 20
    color: "blue"
    visible: mVisible

    border {
        width: 10
        color: Qt.lighter(root.color, 1.3)
    }

    signal clicked()

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {JS.hoverButton(root)}
        onExited: {JS.notHoverAnymore(root)}
        onClicked:
            (event) => {
                if (event.button === Qt.LeftButton) {
                    root.clicked()
                    event.accepted = true;
                }
            }
    }

    Label {
        id: label
        anchors.centerIn: parent
        text: mText
        font.pixelSize: 20
        font.weight: 14
        color: "white"

    }

    Behavior on scale {NumberAnimation {duration: 100}}
    Behavior on color {ColorAnimation {duration: 100}}

}
