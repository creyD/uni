import socket

HOST = ""
PORT = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

connection_obj, addr = s.accept()

history = {}

while True:
    data = connection_obj.recv(1024)

    if not data:
        break

    if data in history:
        history[data] += 1
    else:
        history[data] = 1

    connection_obj.send(str.encode(str(history[data])))

connection_obj.close()
