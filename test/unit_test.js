QUnit.test( "WebSocket Support Checker", function( assert ) {
	assert.expect( 2 );
	backupWebSocket = undefined;
	if(WebSocket !== "undefined") {
		backupWebSocket = WebSocket; //Backup real WebSocket function if it exists
	}
	WebSocket = function (){;} // Fake Support for WebSockets
	detectWebSockets(); // run WebSocket Support Checker
	assert.equal( 
		document.getElementById("WebSocketSupport").innerHTML,
		"Support Confirmed",
		"We expect value to be 'Support Confirmed' when support faked" 
	);
	WebSocket = 0; // Disable WebSockets temporarily
	detectWebSockets(); // run WebSocket Support Checker again
	assert.equal( 
		document.getElementById("WebSocketSupport").innerHTML,
		"Not Supported",
		"We expect value to be 'Not Supported' when support disabled" 
	);
	if(backupWebSocket !== "undefined") {
		WebSocket = backupWebSocket;
	}
	detectWebSockets(); // Reset to true value
});

QUnit.test( "WebSocket Connection Generator", function( assert ) {
	assert.expect(2);
	var ipAddress = "x.x.x.x";
	var count = 2000;
	makeWebSocketConnections(count, ipAddress); //make test run
	assert.equal( 
		document.getElementById("IPAddress").innerHTML,
		ipAddress,
		"IP Address is set properly to '" + ipAddress + "' on the display" 
	);
	//Expected to fail until we set up makeWebSocketConnections() properly
	assert.equal( 
		document.getElementById("ConnectionCount").innerHTML,
		count,
		"Connection count was set properly to '" + count + "'" 
	);
});
