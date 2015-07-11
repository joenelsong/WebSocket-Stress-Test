/**
 * Main Method to be called on Window load
 */
function suedeMain() {
	var support = detectWebSockets();
	if(!support){
		return false;
	}
    runOneEchoTest(
        SuedeConfig.serverHost,
        SuedeConfig.hostPort
    );
	/*makeWebSocketConnections(
        SuedeConfig.numberOfConnections,
        SuedeConfig.serverHost,
        SuedeConfig.hostPort
    );*/
}

/**
 * Checks for WebSocket support 
 * Has side-effects of updating DOM with result
 * @returns {Boolean} success of WebSocket check
 */
function detectWebSockets() {
	if( WebSocket !== undefined && typeof(WebSocket) == "function" ) {
		document.getElementById("WebSocketSupport").innerHTML = "Support Confirmed";
		return true;
	}else{
		document.getElementById("WebSocketSupport").innerHTML = "Not Supported";
		return false;
	}
}

/**
 * Creates a connection with designated IP Address and checks that server echo service is functional
 * Has side-effects of updating DOM with result
 * @param {String} ipAddress
 * @param {Number} portNumber
 * @returns {Boolean} success of WebSocket connection
 */
function runOneEchoTest(ipAddress, portNumber) {
    document.getElementById("IPAddress").innerHTML = ipAddress;
    document.getElementById("PortNumber").innerHTML = portNumber.toString();
    var messageText = "Echo String";
    var connectionString = "ws://" + ipAddress + ":" + portNumber + "/echo";
    var socket = new WebSocket(connectionString);
    socket.onopen = function()
    {
        document.getElementById("EchoResult").innerHTML = "Open";
        socket.send(messageText);
    };
    socket.onmessage = function(msg) {
        if (msg.data == messageText) {
            document.getElementById("EchoResult").innerHTML = "Success";
        } else {
            document.getElementById("EchoResult").innerHTML = "Failed Message Received: \"" + msg.data + "\", should be: \"" + messageText + "\"";
        }
        socket.close();
    }
}

/**
 * Creates designated number of connections with designated IP Address
 * Has side-effects of updating DOM with result
 * @param {Number} numberOfConnections
 * @param {String} ipAddress
 * @param {Number} portNumber
 * @returns {Boolean} success of WebSocket connection
 */
function makeWebSocketConnections(numberOfConnections, ipAddress, portNumber) {
    document.getElementById("IPAddress").innerHTML = ipAddress;
    document.getElementById("PortNumber").innerHTML = portNumber.toString();
    var messageText = "Echo String";
    var connectionString = "ws://" + ipAddress + ":" + portNumber + "/";
    var socketArray = [];

	for (var i = 1; i <= numberOfConnections; i++) {
        (function() {
            var socket = new WebSocket(connectionString);
            socket.onopen = function () {
                socket.send(messageText);
                document.getElementById("ConnectionCount").innerHTML = i.toString();
            };
            socketArray[i] = socket;
        })();
	}
}

/** Bootstrap main*/
window.onload = suedeMain;