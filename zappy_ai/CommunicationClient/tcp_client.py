import asyncio

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
        self.socket_reader: asyncio.StreamReader | None = None
        self.socket_writer: asyncio.StreamWriter | None = None
        self.buffer = b''

    async def connect_to_server(self, host: str, port: int) -> bool:
        """
        @brief Connects to the server.

        @param host The hostname or IP address of the server.
        @param port The port number of the server.
        @return True on successful connection, False otherwise.
        """
        try:
            self.socket_reader, self.socket_writer = await asyncio.open_connection(host, port)
            return True
        except Exception:
            return False

    async def send_cmd(self, message: str) -> bool:
        """
        @brief Sends a single line (terminated by '\n') to the server.

        @param message The message to send (without newline).
        @return True on success, False on failure.
        """
        try:
            if self.socket_writer is None:
                return False
            self.socket_writer.write((message + '\n').encode())
            await self.socket_writer.drain()
            return True
        except Exception:
            return False

    async def receive_cmd(self) -> str:
        """
        @brief Receives a full line from the server.

        Waits until a full line (ending with '\n') is available in the buffer.

        @return The received line without the newline character, or an empty string on failure or disconnection.
        """
        try:
            if self.socket_reader is None:
                return ''
            line = await self.socket_reader.readline()
            return line.decode().rstrip('\n')
        except Exception:
            return ''

    async def close_connection(self):
        """
        @brief Closes the connection to the server.
        Safely shuts down the socket and resets internal state.
        """
        if self.socket_writer:
            self.socket_writer.close()
            await self.socket_writer.wait_closed()
            self.socket_reader = None
            self.socket_writer = None
