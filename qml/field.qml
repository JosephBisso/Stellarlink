import QtQuick 2.15
//import stellarLink.ball 1.0

Item {
    id: fielRoot
    anchors.fill: parent
    focus: true

    Keys.onPressed:
        (event) => {
            if (!event.isAutoRepeat) {
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
                        ball1.resetState()
                        runner.stop()
                        break
                    case Qt.Key_Backtab:
                        console.log("New Start")
                        stellarEngine.stop()
                        floorLogik.resetFloorLine()
                        mainFloor.refresh()
                        ball1.resetState()
                        runner.stop()
                        break
                    case Qt.Key_Right:
                        console.log("accelerate")
                        stellarEngine.accelerate()
                        ball1.accelerate()
                        break
                    case Qt.Key_Down:
                        console.log("Haft")
                        stellarEngine.stick()
                        ball1.stick()
                        break
                    case Qt.Key_Left:
                        console.log("deccelerate")
                        ball1.decelerate()
                        stellarEngine.brake()
                        break
                }
                event.accepted = true;
            }
        }

    Keys.onReleased: (event) => {
        if (!event.isAutoRepeat) {
            if (event.key === Qt.Key_Down || event.key === Qt.Key_Right || event.key === Qt.Key_Left) {
                console.log("Reseting ball state")
                ball1.resetState()
                stellarEngine.freeBall()
                event.accepted = true;
            }
        }
    }

    Timer {
        id: runner
        interval: 30; running: false; repeat: true
        onTriggered: {
            stellarEngine.step()
            mainFloor.refresh()
            ballTrail1.refresh()

        }
    }

    LWXdevGrid {
        id: lwxDevGrid
        z: -2
        x_interval: 25
        y_interval: 25
    }

    Ball {
        id: ball1

    }

    BallTrail {
        id: ballTrail1
        trailColor: ball1.trailColor
        z: -1
    }

    Floor {
        id: mainFloor
    }

}
