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
            context.strokeStyle = "red";
            context.lineWidth = 5;
            context.path = myPath;
            context.fillStyle = "blue"
            context.fill()
            context.stroke();
        }
    }
}
