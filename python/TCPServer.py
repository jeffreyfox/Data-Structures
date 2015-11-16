from socket import *
serverPort = 12000
#serverSocket will be the welcoming socket
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print "The server is ready to receive"
while 1:
    connectionSocket, clientAddress = serverSocket.accept()
    message = connectionSocket.recv(2048)
    print "Received message: ", message
    modifiedMessage = message.upper()
    connectionSocket.send(modifiedMessage)
    connectionSocket.close()
