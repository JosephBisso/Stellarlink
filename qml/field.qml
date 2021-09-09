import QtQuick 2.12

Item {
    id: fielRoot
    anchors.fill: parent
    focus: true

    Keys.onEnterPressed: {
        console.log("Enter pressed")
//        fall()
        stellarEngine.start()
        runner.start()
    }

    Keys.onSpacePressed: {
        console.log("Space pressed")
        stellarEngine.pause()
        runner.stop()
    }

    Timer {
        id: runner
        interval: 15; running: false; repeat: true
        onTriggered: stellarEngine.ballFallStep()
    }

    LWXdevGrid {
        id: lwxDevGrid
        z: -1

        x_interval: 25
        y_interval: 25
    }

    Ball {
        id: ball1

        onYChanged: {
            if (ballLogik.touched(floorLogik)){ballLogik.pos_y = 0;}
            checkPosition()
        }


        //x: 50
        //y: -50
    }

    Floor {
        id: mainFloor
    }

    function checkPosition() {
//        ballLogik.move(0, 5)
        console.log("Checking x, y position on screen")
        if (ballLogik.pos_y === parent.height) {ballLogik.pos_y = 0;}
        if (ballLogik.pos_x === parent.width) {ballLogik.pos_x = 0;}
//        console.log("x= " + ballLogik.pos_x + ", y =" + ballLogik.pos_y)
    }

}
