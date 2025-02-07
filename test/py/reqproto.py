import sys, socket

def send_req(s, msg):
  # input("press enter to send request type...") # create
  s.send((1).to_bytes(1, 'big'))

  # input("press enter to send payload size...") # 1024 size
  s.send((1024).to_bytes(2, 'big'))

  # input("press enter to send hello world...") # send hello world
  s.send(msg.encode('ascii'))


s = socket.socket()
s.connect(('127.0.0.1', 3000))
while True:
  check = input("Type your message or 'q' to quit: ")

  if (check == "q"):
    break

  send_req(s, check)

s.close()
