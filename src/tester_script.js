function main() {
	var support = detectWebSockets();
	if(!support){
		return false;
	}
	makeWebSocketConnections();
}
function detectWebSockets() {
	if( typeof(WebSocket) == "function" ) {
		document.getElementById("WebSocketSupport").innerHTML = "Support Confirmed";
		return true;
	}else{
		document.getElementById("WebSocketSupport").innerHTML = "Not Supported";
		return false;
	}
}

function makeWebSocketConnections() {
	var numberOfConnections = 1000;
	var ipAddress = "x.x.x.x";
	document.getElementById("IPAddress").innerHTML = ipAddress;
	for (i = 1; i <= numberOfConnections; i++) {
		//TODO Build Some WebSocket Connections
		//document.getElementById("ConnectionCount").innerHTML = i.toString();
	}
}

window.onload = main;