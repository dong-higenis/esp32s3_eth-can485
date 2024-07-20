import socket
import threading

class UdpHelper:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.receive_thread = None
        self.running = False
        self.callback = None

    def bind(self, port, callback):
        self.sock.bind(("0.0.0.0", port))
        self.callback = callback
        self.running = True
        self.receive_thread = threading.Thread(target=self.receive)
        self.receive_thread.daemon = True
        self.receive_thread.start()

    def receive(self):
        while self.running:
            try:
                data, addr = self.sock.recvfrom(1024)
                if data:
                    message = data.decode('utf-8')
                    if self.callback:
                        self.callback(message)
            except socket.error:
                break

    def send(self, ip, port, message):
        self.sock.sendto(message.encode('utf-8'), (ip, port))

    def close(self):
        self.running = False
        self.sock.close()
        if self.receive_thread and self.receive_thread.is_alive():
            self.receive_thread.join()