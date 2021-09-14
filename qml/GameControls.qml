import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Frame {
    id: rootPane
    anchors.fill: parent
    clip: true

    property color mColor: "black"

    background: Rectangle {
        radius: 25
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: rootWindow.darkColor
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 50

        Label {
            id: title
            Layout.alignment: Qt.AlignHCenter
            text: "Game Controls"
            color: "white"
            font.pointSize: 30
            font.bold: true
            style: Text.Outline
            styleColor: "blue"
            z:1
        }


        Image {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: -30
            source: "qrc:/img/Stellar_Controls.png"
            scale: 1.7
        }
    }


}
