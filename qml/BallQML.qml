import QtQuick 2.0


Rectangle {
    y: ballLogik.pos_y
    x: ballLogik.pos_x
    width: ballLogik.radius
    height: width
    color: "red"
    border {
        color: "black"
        width: 2
    }
    radius: width * 0.5

}
