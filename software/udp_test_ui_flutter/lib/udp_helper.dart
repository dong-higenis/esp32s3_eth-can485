import 'dart:async';
import 'dart:io';

class UdpHelper {
  late RawDatagramSocket _socket;
  final _controller = StreamController<String>();

  Stream<String> get messages => _controller.stream;


  Future<void> bind(int port) async {
    _socket = await RawDatagramSocket.bind(InternetAddress.anyIPv4, port);
    _socket.listen((RawSocketEvent event) {
      if (event == RawSocketEvent.read) {    
        Datagram? datagram = _socket.receive();
        if (datagram != null) {
          final message = String.fromCharCodes(datagram.data);
          _controller.add(message);
        }
      }
    });
  }

  Future<void> send(String address, int port, String message) async {
    final data = message.codeUnits;
    await RawDatagramSocket.bind(InternetAddress.anyIPv4, 0).then((socket) {
      socket.send(data, InternetAddress(address), port);
      socket.close();
    });
  }

  void dispose() {
    _socket.close();
    _controller.close();
  }
}