import QtQuick 2.0


Rectangle {
    x: ballLogik.pos_x
    y: ballLogik.pos_y
    width: ballLogik.radius
    height: width
    color: "red"
    border {
        color: "black"
        width: 3
    }
    radius: width * 0.5

}
