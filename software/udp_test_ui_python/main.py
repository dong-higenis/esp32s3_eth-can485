import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QLineEdit, QPushButton, QLabel
from PySide6.QtCore import Qt
from udp_helper import UdpHelper

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.udp_helper = UdpHelper()

        self.setWindowTitle("UDP Example")

        self.ip_input = QLineEdit(self)
        self.ip_input.setPlaceholderText("Enter IP Address")
        
        self.port_input = QLineEdit(self)
        self.port_input.setPlaceholderText("Enter Port")
        
        self.message_input = QLineEdit(self)
        self.message_input.setPlaceholderText("Enter Message")
        
        self.send_button = QPushButton("Send UDP Message", self)
        self.send_button.clicked.connect(self.send_message)

        self.receive_port_input = QLineEdit(self)
        self.receive_port_input.setPlaceholderText("Enter Receive Port")

        self.start_receive_button = QPushButton("Start UDP Receiver", self)
        self.start_receive_button.clicked.connect(self.start_receiver)

        self.received_label = QLabel("Received Message: ", self)

        layout = QVBoxLayout()
        layout.addWidget(self.ip_input)
        layout.addWidget(self.port_input)
        layout.addWidget(self.message_input)
        layout.addWidget(self.send_button)
        layout.addWidget(self.receive_port_input)
        layout.addWidget(self.start_receive_button)
        layout.addWidget(self.received_label)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

    def send_message(self):
        ip = self.ip_input.text()
        port = int(self.port_input.text())
        message = self.message_input.text()

        if ip and port and message:
            self.udp_helper.send(ip, port, message)
            print(f'Message sent: {message} to {ip}:{port}')
    
    def start_receiver(self):
        port = int(self.receive_port_input.text())
        if port:
            self.udp_helper.bind(port, self.display_message)
            print(f'Listening on port {port}')
    
    def display_message(self, message):
        self.received_label.setText(f"Received Message: {message}")
    
    def closeEvent(self, event):
        self.udp_helper.close()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec())