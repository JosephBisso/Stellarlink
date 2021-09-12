import QtQuick 2.15

Behavior {
    id: root
    property Item fadeTarget: targetProperty.object
    SequentialAnimation {
        NumberAnimation {
            target: root.fadeTarget
            property: "scale"
            to: 1.4
            easing.type: Easing.InCubic
        }
        PropertyAction { }
        NumberAnimation {
            target: root.fadeTarget
            property: "scale"
            to: 1
            easing.type: Easing.OutQuad
        }
    }
}
