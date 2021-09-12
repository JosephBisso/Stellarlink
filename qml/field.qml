import QtQuick 2.15

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
                            stellarEngine.start()
                            runner.start()
                        }
                        break
                    case Qt.Key_Space:
                        stellarEngine.pause()
                        mainFloor.refresh()
                        ball1.resetState()
                        runner.stop()
                        break
                    case Qt.Key_Backtab:
                        stellarEngine.stop()
                        ballLogik.resetBallPath()
                        ballTrail1.refresh()
                        ball1.resetState()
                        floorLogik.resetFloorLine()
                        mainFloor.refresh()
                        board.reset()
                        runningStats.reset()
                        runner.stop()
                        break
                    case Qt.Key_Right:
                        stellarEngine.accelerate()
                        ball1.accelerate()
                        break
                    case Qt.Key_Down:
                        stellarEngine.stick()
                        ball1.stick()
                        break
                    case Qt.Key_Left:
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
        z: -3
        x_interval: 25
        y_interval: 25
    }

    Ball {
        id: ball1

        onActualSpeedChanged: board.updateSpeed(ball1.actualSpeed)
        onMaxSpeedChanged: {
            runningStats.updateMaxSpeed(ball1.maxSpeed)
            board.updateMaxSpeed(ball1.maxSpeed)
        }

        onActualHeigthChanged: board.updateHeigth(ball1.actualHeigth)
        onMaxHeigthChanged: {
            runningStats.updateMaxHeigth(ball1.maxHeigth)
            board.updateMaxHeigth(ball1.maxHeigth)
        }

        onHealthChanged: {
            runningStats.updateHealth(ball1.health)
            if (ball1.health <= 0) {
                console.log("Game Over")
                runner.stop()
            }
        }
    }

    BallTrail {
        id: ballTrail1
        trailColor: ball1.trailColor
        z: -2
    }

    Floor {
        id: mainFloor
    }

    RunningStats {
        id: runningStats
        x: 25
        y: 25
        z: -2
    }

    Board {
        id: board
        x: 400
        y: 25
        z: -1
    }

}
