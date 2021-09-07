import QtQuick 2.12

Item {
    id: fielRoot
    anchors.fill: parent

    LWXdevGrid {
        id: lwxDevGrid
        z: -1

        x_interval: 25
        y_interval: 25
    }

    BallQML {
        id: ball1

        //x: 50
        //y: -50
    }

    function fall() {
        while (true) {
            ballLogik.move(5, 5)
            if (ballLogik.pos_y === parent.height) {ballLogik.pos_y = 0;}
            if (ballLogik.pos_x === parent.width) {ballLogik.pos_x = 0;}
            console.log("x= " + ballLogik.pos_x + ", y =" + ballLogik.pos_y)

        }

    }

}
