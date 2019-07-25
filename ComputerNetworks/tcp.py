import socket

def recieveLine(conn):
    data = ''
    while True:
        d = conn.recv(1024).decode("utf-8")
        if d == '\r\n':
           return data
        data += d
    return 0


HOST = ""
PORT = 8081

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

connection_obj, addr = s.accept()

history = {}

while True:
    data = recieveLine(connection_obj)

    if not data:
        break

    if data in history:
        history[data] += 1
    else:
        history[data] = 1

    connection_obj.send(str.encode(str(history[data])))

connection_obj.close()
