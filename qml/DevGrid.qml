import QtQuick 2.12

Rectangle {
    id: root

    property int gridWidth: 1
    property int labelOffset: 3
    property int numberOfRow: (root.height / y_interval) + 1
    property int numberOfColumn: (root.width / x_interval) + 1
    property int x_interval: 100
    property int y_interval: 100

    anchors.fill: parent
    color: "darkgrey"

    Repeater {
        id: yRepeater

        model: root.numberOfRow

        Rectangle {
            id: gridLineY

            y: index * y_interval -.5 * height
            width: root.width
            height: root.gridWidth
            color: "grey"
        }
    }

    Repeater {
        id: xRepeater

        model: root.numberOfColumn

        Item{
            id: gridItemX

            x: index * x_interval

            Rectangle {
                id: gridLineX

                x: -0.5 * width
                width: gridWidth
                height: root.height
                color: "grey"
            }

            Text {
                id: textForRow

                text: index * root.x_interval
                x: root.labelOffset
                y: root.labelOffset
            }
        }
    }

    Repeater {
        id: yRepeaterLabel

        model: root.numberOfRow

        Text {
            id: textForColumn

            text: index * root.y_interval
            x: root.labelOffset
            y: index * y_interval + root.labelOffset
        }
    }
}

