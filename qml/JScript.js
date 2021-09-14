function ligth(object) {
    object.opacity = 0.9
}

function resetLigth(object) {
    object.opacity = 0.5
}

function hoverButton(object) {
    let oldColor = object.border.color
    object.border.color = Qt.lighter(oldColor, 1.2)

    object.scale = 1.1
    hoverSound.play()
}

function notHoverAnymore(object) {
    let oldColor = object.border.color
    object.border.color = Qt.darker(oldColor, 1.2)

    object.scale = 1
    hoverSound.stop()
}

function startGame() {
    if (!stellarEngine.engineOn) {
        stellarEngine.start()
        runner.start()
    }
}

function pauseGame() {
    stellarEngine.pause()
    mainFloor.refresh()
    ball1.resetState()
    runner.stop()
    if (drawer.opened) {drawer.close()}
    else {drawer.open()}
}

function stopGame() {
    stellarEngine.stop()
    ballLogik.resetBallPath()
    ballTrail1.refresh()
    ball1.resetState()
    floorLogik.resetFloorLine()
    mainFloor.refresh()
    board.reset()
    runningStats.reset()
    runner.stop()
    drawer.open()
}
