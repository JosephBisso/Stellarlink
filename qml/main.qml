import QtQuick 2.12
import QtQuick.Window 2.12
import Stellar.Stellarlink 1.0
import QtQuick.Controls 2.15

Window {
    id: rootWindow
        width: 1000
        height: 750
        maximumWidth: width
        maximumHeight: height
        minimumHeight: maximumHeight
        minimumWidth: maximumWidth
        visible: true
        title: qsTr("StellarLINK")

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
        }

        onOpened: {mainMenu.focus = true; field.focus = false; mainMenu.loadStats()}

        onClosed: {
            mainMenu.focus = false
            field.focus = true
            field.start()
        }
    }

    StellarLink {
        id: stellarLink
        property string health:"100"
        property string score:"00000000"
        property string speed:"00000 mph"
        property string height:"0000000 m"
    }

    Component.onCompleted: drawer.open()
}
