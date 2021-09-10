import QtQuick 2.12

Item {
    id: fielRoot
    anchors.fill: parent
    focus: true

    Keys.onEnterPressed: {
        console.log("Enter pressed")
        if (!stellarEngine.engineOn) {
            console.log("Start")
            stellarEngine.start()
            runner.start()
        }
    }

    Keys.onSpacePressed: {
        console.log("Paused")
        stellarEngine.pause()
        mainFloor.refresh()
        runner.stop()
    }

    Keys.onBacktabPressed: {
        console.log("New Start")
        stellarEngine.stop()
        floorLogik.resetFloorLine()
        mainFloor.refresh()
        runner.stop()
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
