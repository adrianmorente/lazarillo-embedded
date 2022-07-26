const ws = require("ws");

function heartbeat() {
    this.isAlive = true;
}

const wss = new ws.WebSocketServer({ port: 8080 });

wss.on("connection", function connection(ws, req) {
    ws.isAlive = true;
    ws.on("pong", heartbeat);

    const ip = req.socket.remoteAddress;
    console.log("New connection from " + ip);
});

const interval = setInterval(function ping() {
    wss.clients.forEach(function each(ws) {
        if (ws.isAlive === false) return ws.terminate();

        ws.isAlive = false;
        ws.ping();
    });
}, 30000);

wss.on("close", function close() {
    clearInterval(interval);
});
