/**
 * Main Method to be called on Window load
 */
function suedeMain() {
	var support = detectWebSockets();
	if(!support){
		return false;
	}
	makeWebSocketConnections(SuedeConfig.numberOfConnections, SuedeConfig.serverHost);
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
 * Creates designated number of connections with designated IP Address
 * Has side-effects of updating DOM with result
 * @param {Number} numberOfConnections
 * @param {String} ipAddress
 * @returns {Boolean} success of WebSocket connection
 */
function makeWebSocketConnections(numberOfConnections, ipAddress) {
	document.getElementById("IPAddress").innerHTML = ipAddress;
	for (var i = 1; i <= numberOfConnections; i++) {
		//TODO Build Some WebSocket Connections
		//document.getElementById("ConnectionCount").innerHTML = i.toString();
	}
}

/** Bootstrap main*/
window.onload = suedeMain;