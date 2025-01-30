import sys, socket
s = socket.socket()
s.connect(('127.0.0.1', 3000))

input("press enter to send request type...") # create
s.send((3).to_bytes(1, 'big'))

input("press enter to send payload size...") # 1024 size
s.send((1024).to_bytes(2, 'big'))

input("press enter to send hello world...") # send hello world
s.send("Hello World".encode('ascii'))

while True:
  check = input("type q to quit: ")
  if (check == "q"):
    break

s.close()