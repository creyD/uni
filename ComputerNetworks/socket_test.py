import socket

HOST = ""
PORT = 8085
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

conns, addr = s.accept()
print('Connected by' + str(addr))

while True:
    data = conns.recv(1024)

    if not data:
        break

    conns.send(data)
conns.close()
