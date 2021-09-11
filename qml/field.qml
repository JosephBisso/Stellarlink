import QtQuick 2.15

Item {
    id: fielRoot
    anchors.fill: parent
    focus: true

    Keys.onPressed:
        (event) => {
            switch (event.key) {
                case Qt.Key_Enter:
                    if (!stellarEngine.engineOn) {
                        console.log("Start")
                        stellarEngine.start()
                        runner.start()
                    }
                    break
                case Qt.Key_Space:
                    console.log("Paused")
                    stellarEngine.pause()
                    mainFloor.refresh()
                    runner.stop()
                    break
                case Qt.Key_Backtab:
                    console.log("New Start")
                    stellarEngine.stop()
                    floorLogik.resetFloorLine()
                    mainFloor.refresh()
                    runner.stop()
                    break
                case Qt.Key_Right:
                    console.log("accelerate")
                    stellarEngine.accelerate()
                    ball1.accelerate()
                    break
                case Qt.Key_Down:
                    console.log("Haft")
                    stellarEngine.haften()
                    ball1.stick()
                    break
                case Qt.Key_Left:
                    console.log("Brake")
                    stellarEngine.brake()
                    break
            }
            event.accepted = true;
        }

    Keys.onReleased: (event) => {
        if (event.key === Qt.Key_Righ || Qt.Key_Left ||Qt.Key_Down ) {
            console.log("Reseting ball state")
            ball1.resetState()
            event.accepted = true;
        }
}

    Timer {
        id: runner
        interval: 30; running: false; repeat: true
        onTriggered: {
            stellarEngine.step()
            mainFloor.refresh()
        }
    }

    LWXdevGrid {
        id: lwxDevGrid
        z: -1
        x_interval: 25
        y_interval: 25
    }

    Ball {
        id: ball1

    }

    Floor {
        id: mainFloor
    }

}
