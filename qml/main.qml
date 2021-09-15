import QtQuick 2.12
import Stellar.Stellarlink 1.0
import QtQuick.Controls 2.15
import QtMultimedia 5.15

ApplicationWindow  {
    id: rootWindow
        width: 1000
        height: 750
        maximumWidth: width
        maximumHeight: height
        minimumHeight: maximumHeight
        minimumWidth: maximumWidth
        visible: true
        title: qsTr("StellarLINK")

        property color darkColor: "#091030"
        property color ligthColor: "#303652"
        property color ligtherColor: "#767c94"


        Field {
            id: field

            onGameOver: {
                drawer.open()
                mainMenu.noContinue()
            }
        }

        Drawer {
            id: drawer
            width: rootWindow.width
            height: rootWindow.height
            opacity: 0.8
            interactive: false

            MainMenu{
                id: mainMenu

                onQuit: Qt.quit()
            }

            onOpened: {
                mainMenu.focus = true;
                field.focus = false;
                mainMenu.loadStats();
                clickSound.play()
                backgroundAudio.pause()
            }

            onClosed: {
                mainMenu.focus = false
                field.focus = true
                field.start()
                backgroundAudio.play()
            }
        }

        StellarLink {
            id: stellarLink
            property string health:"100"
            property string score:"00000000"
            property string speed:"00000 mph"
            property string height:"0000000 m"
        }

        SoundEffect {
            id: hoverSound
            source: "qrc:/sound/buttonHover.wav"
            volume: 0.15
        }

        SoundEffect {
            id: clickSound
            source: "qrc:/sound/buttonClick.wav"
            volume: 0.3
        }

        SoundEffect {
            id: scoreSound
            source: "qrc:/sound/scoreUp.wav"
            volume: 0.03
        }

        SoundEffect {
            id: decelerationSound
            source: "qrc:/sound/ballDecelerating.wav"
            volume: 0.5
        }

        SoundEffect {
            id: accelerationSound
            source: "qrc:/sound/ballAccelerating.wav"
            volume: 0.1
        }

        SoundEffect {
            id: ballStickSound
            source: "qrc:/sound/ballStick.wav"
            volume: 0.15
        }

        SoundEffect {
            id: ballHitSound
            source: "qrc:/sound/ballHit.wav"
            volume: 0.1
        }

        Label {
            id: copyrigth
            text: "By Joseph Bisso"
            color: "Black"
            anchors {
                right: parent.right
                bottom: parent.bottom
            }
        }

        SoundEffect {
            id: lauchingSound
            source: "qrc:/sound/ballLaunchin.wav"
            volume: 0.15
        }

        Audio {
            id: backgroundAudio
            source: "qrc:/sound/stellarBackground.mp3"
            volume: 0.07
            loops: Audio.Infinite
        }


        Component.onCompleted: drawer.open()
}
