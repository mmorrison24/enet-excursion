var enet = require("enet");
var host_ip = "192.168.55.55",
    host_ip = "127.0.0.1",
    host_port = 33333,
    client_port = 33340;

var client = enet.createClient({
    peers: 1, /* outgoing connections */
    channels: 2, /* allow up to 2 channels to be used, 0 and 1 */
    down: 0, /* downstream bandwidth */
    up: 0 /* upstream bandwidth */
});
client.start();

/* connect to server */
var server_addr = new enet.Address(host_ip,host_port);

/* Initiate the connection, allocating the two channels 0 and 1. */
var peer = client.connect(server_addr, 2, /* channels */ 1337, /* data to send with connect */
    function(err,peer){ /* on connect callback function */
        if(err){
            console.error(err);//either connect timeout or maximum peers exceeded
            return;
        }
    });

//connect event can also be handled with an event handler
peer.on("connect",function(){

    var packet = new enet.Packet( new Buffer("hello, world"),enet.Packet.FLAG_RELIABLE);

    peer.send(0 /*channel*/, packet, function(err){
        //callback when packet is sent 'err' will be 'undefined'
        //If error occurs trying to queue the packet err be an instance of Error()
    });

});





