import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Frame {
    anchors.fill: parent

    background: Rectangle {
        anchors.fill: parent
        color: "black"
        radius: 25
        border {
            width: 10
            color: "white"
        }
    }

    Label {
        id: title
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 25
        }

        text: "StellarLINK"
        color: "white"
        font.pointSize: 60
        font.bold: true
        style: Text.Outline
        styleColor: "blue"
    }

    StackView {
        id: stackView
        anchors {
            top: title.bottom
            bottom: footer.top
            margins: 25
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width / 1.75

        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
            radius: 25
            border {
                width: 5
                color: "white"
            }
        }

        initialItem: RunningStats{
                        id: stats
                        mColor: "white"
                        anchors.fill: parent
                     }
    }

    RowLayout {
        id: footer
        anchors{
            bottom: parent.bottom
            right: parent.right
            left: parent.left
        }

        height: 150

        spacing: 50

        CustomButton {
            mText: "New Game"
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                field.stop()
                drawer.close()
                field.start()
                continueButton.mVisible = true
            }
        }

        CustomButton {
            id: continueButton
            mText: "Continue"
            mVisible: false
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                drawer.close()
                field.start()
            }
        }

        CustomButton {
            mText: "Quit"
            Layout.alignment: Qt.AlignHCenter

            onClicked: rootWindow.close()
        }
    }

    Keys.onPressed:
        (event) => {
            if (!event.isAutoRepeat && event.key === Qt.Key_Space) {
                drawer.close()
                event.accepted = true;
            }
        }

    function loadStats() {
        stats.loadStats(stellarLink.health, stellarLink.score, stellarLink.speed, stellarLink.height)
    }

    function noContinue() {
        continueButton.mVisible = false
    }
}
