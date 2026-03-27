#!/bin/python
# Copyright (c) 2023 Oracle and/or its affiliates.

import smtplib,os,sys
from email import message_from_string

smtp_server = os.environ.get("DM_EMAIL_SMTP_SERVER")
if smtp_server == None or smtp_server == "":
    print("SMTP Server not set")
    sys.exit(1)

input_buf = []
while True:
    line = sys.stdin.readline()
    input_buf.append(line)
    if '.' == line.strip() or '--------------64171C924A6B--' == line.strip():
        break

message = message_from_string("".join(input_buf))

# Try to log in to server
try:
    server = smtplib.SMTP(smtp_server)
except Exception as e:
    print(e)
    sys.exit(2)

try:
    server.set_debuglevel(2)
    server.starttls() # Secure the connection
    sender = message.get("From")
    reciever = message.get("To")
    server.sendmail(sender,reciever,message.as_string())
except Exception as e:
    print(e)
finally:
    server.quit()
