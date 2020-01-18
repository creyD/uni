import socket


def create_error_page(conn, err_string):
    conn.send('HTTP/1.1 400 Bad Request\r\n'.encode())
    conn.send('Connection: close\r\n'.encode())
    conn.send('Content-Type: text/html\r\n\r\n'.encode())
    conn.send('<html><head><title>ERROR</title></head>\r\n'.encode())
    conn.send(f'<body><h1>Error</h1><hr/><p>{err_string}</p></body></html>'.encode())
    conn.close()
    return


def handle_request(conn):
    data = conn.recv(2048)
    parts = data.decode().split('\r\n\r\n')
    head = parts[0]
    body = ''

    if len(parts) > 1:
        body = parts[1]

    header = {}
    values = {}

    lines = head.split('\r\n')
    balance = 100

    if lines[0].split(' ')[1] != '/':
        create_error_page(conn, "Resource not available")
        return

    # Searching the header for the cookie
    for line in lines[1:]:
        key, value = line.split(': ')
        header[key] = value
        # Setting the current balance to value in the cookie
        if header[key].startswith('balance='):
            balance = float(header[key][8:])

    # Converting the request body into a python array
    if body:
        pairs = body.split('&')
        for pair in pairs:
            key, value = pair.split('=')
            values[key] = value

    amount = False

    if 'amount' in values:
        try:
            amount = float(values['amount'])
        except:
            create_error_page(conn, f"{values['amount']} is not a float")
            return

        balance -= amount

    conn.send('HTTP/1.1 200 OK\r\n'.encode())
    conn.send('Connection: close\r\n'.encode())
    conn.send('Content-Type: text/html\r\n'.encode())
    conn.send('Set-Cookie: balance={0}\r\n\r\n'.format(balance).encode())

    conn.send('<html><head><title>Account</title></head>\r\n'.encode())
    conn.send('<body><h1>Account</h1><hr/>\r\n'.encode())
    if amount:
        conn.send(f'<p>Transfer = {amount:5.2f}</p>\r\n'.encode())
    conn.send(f'<p>New balance = {balance:5.2f}</p>\r\n'.encode())
    conn.send('<form method="POST" action="/" enctype="application/x-www-form-urlencoded">\r\n'.encode())
    conn.send('<p>Amount to transfer: <input type="text" name="amount"/></p>\r\n'.encode())
    conn.send('<p><input type="submit" value="Transfer"/></p>\r\n'.encode())
    conn.send('</form>\r\n'.encode())
    conn.send('</body></html>\r\n'.encode())
    conn.close()
    return


TCP_IP = ''
TCP_PORT = 5000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

while 1:
    conn, addr = s.accept()
    handle_request(conn)
