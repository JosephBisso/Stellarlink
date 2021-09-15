import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15

Frame {
    id: rootFrame
    anchors.fill: parent

    signal quit()

    background: Rectangle {
        anchors.fill: parent
        color: rootWindow.ligthColor
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
        font.pointSize: 62
        font.bold: true
        style: Text.Outline
        styleColor: rootWindow.darkColor
    }

    Frame {
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

        GameControls {
            id: gameControls
            visible: true
            anchors.fill: parent
        }

        RunningStats{
            id: stats
            mColor: "white"
            visible: !gameControls.visible
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
                gameControls.visible = false
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

            onClicked: rootFrame.quit()
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
