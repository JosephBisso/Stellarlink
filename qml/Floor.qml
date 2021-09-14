import QtQuick 2.15

Item {
    Canvas {
        id: canvasRoot
        width: 1000; height: 750
        contextType: "2d"


        Path {
            id: myPath
            startX: 0; startY: canvasRoot.height;

            PathLine {x: 0; y: canvasRoot.height}

            PathPolyline {path: floorLogik.floorLine}

            PathLine {x: canvasRoot.width; y: canvasRoot.height}

            PathLine {x: 0; y: canvasRoot.height}
        }

        onPaint: {
            context.strokeStyle = rootWindow.darkColor;
            context.lineWidth = 5;
            context.path = myPath;
            context.fillStyle = rootWindow.ligthColor
            context.fill()
            context.stroke();
        }
    }

    function refresh() {
        canvasRoot.context.reset()
        canvasRoot.requestPaint()
    }
}
