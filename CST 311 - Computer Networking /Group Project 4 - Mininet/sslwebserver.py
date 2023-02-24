#!/usr/bin/env python3

# sslserver.py for CST311 @ CSUMB by BayTech: Luis Jimenez-Barrios,
#   Warren Ngoun, Yukio Rivera, Jennah Yasin.
# A python script from Lab 6 that runs an SSL server using our correctly 
# generated certs.

import http.server
import ssl

## Variables you can modify
server_address = "www.webpa4.test"
server_port = 4443
ssl_key_file = "/etc/ssl/demoCA/private/www.webpa4.test-key.pem"
ssl_certificate_file = "/etc/ssl/demoCA/newcerts/www.webpa4.test-cert.pem"

## Don't modify anything below
httpd = http.server.HTTPServer(
    (server_address, server_port), http.server.SimpleHTTPRequestHandler)
httpd.socket = ssl.wrap_socket(httpd.socket,
                               server_side=True,
                               keyfile=ssl_key_file,
                               certfile=ssl_certificate_file,
                               ssl_version=ssl.PROTOCOL_TLSv1_2)

print("Listening on port", server_port)
httpd.serve_forever()