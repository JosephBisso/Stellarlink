import QtQuick 2.15

Item {
    id: rootItem
    property double maxSpeed: 100

    Rectangle {
        id: circle
        width: 150
        height: width
        color: "transparent"
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop{position: 0.0; color: circle.color}
            GradientStop{position: 3/4; color: circle.color}
            GradientStop{position: 9/10; color: "red"}
            GradientStop{position: 1.0; color: "darkred"}
        }

        border {
            color: "white"
            width: 4
        }
        radius: width * 0.5
        clip:true
    }

    Rectangle {
        id: mask
        y: circle.y + circle.width / 2
        z:1
        width: circle.width + circle.border.width + 2
        height: circle.height / 2
        color: "black"
        anchors.horizontalCenter: circle.horizontalCenter

    }

    Rectangle {
        width: 20
        height: width
        radius: width/2
        anchors.centerIn: circle
    }

    Rectangle {
        id: needle
        anchors{
            bottom: parent.bottom
            left: parent.left
            bottomMargin: -circle.radius
            leftMargin: circle.radius / 2 - 2 * circle.border.width - 2 * height

        }
        width: circle.radius - 25
        height: 2
        radius: 2
        transformOrigin: Item.BottomRight

        Behavior on rotation { RotationAnimation { direction: RotationAnimation.Shortest; duration: 600 } }
    }



    function moveNeedle(actualSpeed) {
        if (actualSpeed > rootItem.maxSpeed) {rootItem.maxSpeed = +actualSpeed.toFixed(1)}
        let angle = actualSpeed === 0 ? 20 : Math.abs(actualSpeed) * 160 / rootItem.maxSpeed
        needle.rotation = angle <= 160 ? angle : 160
    }

    function reset() {
        needle.rotation = Math.abs(3) * 160 / rootItem.maxSpeed
    }
}
