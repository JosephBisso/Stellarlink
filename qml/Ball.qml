import QtQuick 2.0


Rectangle {
    x: ballLogik.pos_x < 250 ? ballLogik.pos_x : 250
    y: ballLogik.pos_y % parent.height
    width: ballLogik.radius
    height: width
    color: "red"
    border {
        color: "black"
        width: 3
    }
    radius: width * 0.5

}
