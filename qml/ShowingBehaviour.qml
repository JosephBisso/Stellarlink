import QtQuick 2.15

Behavior {
    id: root
    property Item fadeTarget: targetProperty.object
    SequentialAnimation {
        ColorAnimation {
            target: root.fadeTarget
            property: "color"
            to: Qt.lighter("green", 1.5)
            duration: 200
        }
        NumberAnimation {
            target: root.fadeTarget
            property: "scale"
            to: 1.5
            easing.type: Easing.InCubic
        }

        PropertyAction { }
        NumberAnimation {
            target: root.fadeTarget
            property: "scale"
            to: 1
            easing.type: Easing.OutQuad
        }
        ColorAnimation {
            target: root.fadeTarget
            property: "color"
            to: "white"
            duration: 500
        }
    }
}
