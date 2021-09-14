import QtQuick 2.15
import QtQuick.Controls 2.15
import "JScript.js" as JS

Frame {
    id: fielRoot
    anchors.fill: parent
    focus: true
    clip: true

    signal gameOver()

    background: Rectangle {
        anchors.fill: parent
        color: "black"
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

    MenuButton {
        id: menuButton
        x: 900
        y: 25
    }

    Image {
        id: backgroundImage
        source: "qrc:/img/Stellar_Background.png"
        x: -20 -ballLogik.pos_x / width
        y: -20
        z: -3
        fillMode: Image.PreserveAspectCrop

        Behavior on x {NumberAnimation{ duration: 500}}
    }

//    DevGrid {
//        id: lwxDevGrid
//        z: -3
//        x_interval: 25
//        y_interval: 25
//    }

    Ball {
        id: ball1

        onActualSpeedChanged:{ board.updateSpeed(ball1.actualSpeed);}
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
            ballHitSound.play()
            if (ball1.health <= 0) {
                console.log("Game Over")
                pause()
                fielRoot.gameOver()
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
        mColor: "white"
    }

    Board {
        id: board
        x: 400
        y: 25
        z: -1
    }

    Keys.onPressed:
        (event) => {
            if (!event.isAutoRepeat) {
                switch (event.key) {
                    case Qt.Key_Enter:
                        JS.startGame()
                        break
                    case Qt.Key_Space:
                        pause()
                        break
                    case Qt.Key_Escape:
                        pause()
                        break
                    case Qt.Key_Backtab:
                        JS.pause()
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

    function start() {
        JS.startGame()
    }
    function pause() {
        [stellarLink.health, stellarLink.score, stellarLink.speed, stellarLink.height] = runningStats.keepTrack()
        JS.pauseGame()
    }
    function stop() {
        JS.stopGame()
    }
}
