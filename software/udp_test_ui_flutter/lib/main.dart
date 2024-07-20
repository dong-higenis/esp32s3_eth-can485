import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'dart:io';
import 'udp_helper.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final int _defaultPort = 1234;
  final TextEditingController _ipController = TextEditingController();
  final TextEditingController _portController = TextEditingController();
  final TextEditingController _messageController = TextEditingController();
  final TextEditingController _receivePortController = TextEditingController();
  final UdpHelper _udpHelper = UdpHelper();
  String _receivedMessage = '';

  @override
  void initState() {
    super.initState();
    _udpHelper.messages.listen((message) {
      setState(() {
        _receivedMessage = message;
      });
    });
  }

  Future<void> _sendMessage() async {
    final String ip = _ipController.text;
    final int port = int.tryParse(_portController.text)??_defaultPort;
    final String message = _messageController.text;

    if (ip.isEmpty || message.isEmpty) {
      if (kDebugMode) {
        print('Invalid IP address, port number, or empty message');
      }
      return;
    }

    _udpHelper.send(ip, port, message);
    if (kDebugMode) {
      print('메시지 전송: $message to $ip:$port');
    }
  }

  Future<void> _startReceiver() async {
    final int port = int.tryParse(_receivePortController.text)??_defaultPort;
    await _udpHelper.bind(port);
    if (kDebugMode) {
      print('Listening on port $port');
    }
  }

  @override
  void dispose() {
    _ipController.dispose();
    _portController.dispose();
    _messageController.dispose();
    _receivePortController.dispose();
    _udpHelper.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Flutter UDP Example'),
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              TextField(
                controller: _ipController,
                decoration: const InputDecoration(
                  labelText: 'Enter IP Address',
                  border: OutlineInputBorder(),
                ),
                keyboardType: TextInputType.text,
              ),
              const SizedBox(height: 20),
              TextField(
                controller: _portController,
                decoration: const InputDecoration(
                  labelText: 'Enter Port',
                  border: OutlineInputBorder(),
                ),
                keyboardType: TextInputType.number,
              ),
              const SizedBox(height: 20),
              TextField(
                controller: _messageController,
                decoration: const InputDecoration(
                  labelText: 'Enter Message',
                  border: OutlineInputBorder(),
                ),
              ),
              const SizedBox(height: 20),
              ElevatedButton(
                onPressed: _sendMessage,
                child: const Text('Send UDP Message'),
              ),
              const SizedBox(height: 20),
              TextField(
                controller: _receivePortController,
                decoration: const InputDecoration(
                  labelText: 'Enter Receive Port',
                  border: OutlineInputBorder(),
                ),
                keyboardType: TextInputType.number,
              ),
              const SizedBox(height: 20),
              ElevatedButton(
                onPressed: _startReceiver,
                child: const Text('Start UDP Receiver'),
              ),
              const SizedBox(height: 20),
              Text(
                'Received Message: $_receivedMessage',
                textAlign: TextAlign.center,
              ),
            ],
          ),
        ),
      ),
    );
  }
}