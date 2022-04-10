#!/usr/bin/env python3

## HTTP server code



import http.server
import socketserver

PORT = 8080
Handler = http.server.SimpleHTTPRequestHandler

#SimpleHTTPRequestHandler will look for a file named index.html in the current directory.

with socketserver.TCPServer(("", PORT), Handler) as httpd:      #(ip address, port numner) ## TCP address includes IP addr & Port number
  print("Serving at port ", PORT)
  httpd.serve_forever()
  
