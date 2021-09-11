import QtQuick 2.15

Item {
    Canvas {
        id: ballCanvasRoot
        width: 500; height: 750
        contextType: "2d"

        Path {
            id: myPath2

            PathPolyline {id:polyline;path: ballLogik.ballPath}
        }

        onPaint: {
            polyline.path = ballLogik.ballPath;
            var gradient = context.createLinearGradient(0, 400, 300, 400);
            gradient.addColorStop(0.4, Qt.hsla(trailColor.hslHue, trailColor.hslSaturation, trailColor.hslLightness, 0.05));
            gradient.addColorStop(0.7, Qt.hsla(trailColor.hslHue, trailColor.hslSaturation, trailColor.hslLightness, 0.3));
            gradient.addColorStop(1, trailColor);
            context.strokeStyle = gradient;
            context.lineWidth = ballLogik.radius * 2;
            context.path = myPath2;
            context.stroke();
        }
    }

    function refresh() {
        ballCanvasRoot.context.reset()
        ballCanvasRoot.requestPaint()
    }

    property color trailColor: "red"
}
