import socket

class CommunicationClient:
    """
    @class TcpClient
    @brief TCP client class for communicating with a Zappy server.

    Handles connection setup, line-based communication, and socket cleanup.
    """

    def __init__(self):
        """
        @brief Constructor.
        Initializes the socket to None and the internal receive buffer.
        """
        self.socket = None
        self.buffer = b''

    def connect_to_server(self, host: str, port: int) -> bool:
        """
        @brief Connects to the server.

        @param host The hostname or IP address of the server.
        @param port The port number of the server.
        @return True on successful connection, False otherwise.
        """
        try:
            self.socket = socket.create_connection((host, port))
            self.socket.setblocking(True)
            return True
        except (socket.error, socket.gaierror):
            return False

    def send_cmd(self, message: str) -> bool:
        """
        @brief Sends a single line (terminated by '\n') to the server.

        @param message The message to send (without newline).
        @return True on success, False on failure.
        """
        try:
            self.socket.sendall((message + '\n').encode())
            return True
        except socket.error:
            return False

    def receive_cmd(self) -> str:
        """
        @brief Receives a full line from the server.

        Waits until a full line (ending with '\n') is available in the buffer.

        @return The received line without the newline character, or an empty string on failure or disconnection.
        """
        while b'\n' not in self.buffer:
            try:
                data = self.socket.recv(1024)
                if not data:
                    return ''
                self.buffer += data
            except socket.error:
                return ''
        line, self.buffer = self.buffer.split(b'\n', 1)
        return line.decode()

    def close_connection(self):
        """
        @brief Closes the connection to the server.
        Safely shuts down the socket and resets internal state.
        """
        if self.socket:
            self.socket.close()
            self.socket = None
