#! /usr/bin/env python2.7
'''devsrv.py - HTTP server for use during development

This is a stupid simple way to make sure that make-maintained
generated code gets served based on its dependencies.

In the example below, flippity.js is created by transpiling
flippity.ts, as specified by the makefile.

Usage::

  (normal)ecashin@montgomery:~/src/typescript/flippitydigits$ cat makefile
  PROG = flippity
  PROGS := $(addsuffix .js,$(basename $(wildcard *.ts)))
  .PHONY: show all srv

  all: $(PROGS)

  srv: all
          python2.7 -mSimpleHTTPServer

  show:
          echo $(PROGS)

  %.js: %.ts
          tsc $<
  (normal)ecashin@montgomery:~/src/typescript/flippitydigits$ ./devsrv.py 8112
  serving on 8112
  127.0.0.1 - - [12/Nov/2014 21:27:41] "GET / HTTP/1.1" 200 -
  call "make flippity.css"
  make: Nothing to be done for `flippity.css'.
  127.0.0.1 - - [12/Nov/2014 21:27:41] "GET /flippity.css HTTP/1.1" 200 -
  call "make jquery-1.11.1.js"
  make: Nothing to be done for `jquery-1.11.1.js'.
  127.0.0.1 - - [12/Nov/2014 21:27:41] "GET /jquery-1.11.1.js HTTP/1.1" 200 -
  call "make flippity.js"
  tsc flippity.ts
  127.0.0.1 - - [12/Nov/2014 21:27:41] "GET /flippity.js HTTP/1.1" 200 -
  127.0.0.1 - - [12/Nov/2014 21:27:42] code 404, message File not found
  127.0.0.1 - - [12/Nov/2014 21:27:42] "GET /favicon.ico HTTP/1.1" 404 -
  ...

'''

from SimpleHTTPServer import SimpleHTTPRequestHandler
import SocketServer
import os
from subprocess import call
import sys


PORT = 8118


class Handler(SimpleHTTPRequestHandler):
    def do_GET(self):
        path = '.' + os.path.abspath(self.path)
        if os.path.isfile(path):
            path = self.path[1:]
            print 'call "{} {}"'.format('make', path)
            call(['make', path])
        return SimpleHTTPRequestHandler.do_GET(self)


if __name__ == '__main__':
    if len(sys.argv) > 1:
        port = int(sys.argv[1])
    else:
        port = PORT
    httpd = SocketServer.TCPServer(('', port), Handler)
    print 'serving on {}'.format(port)
    httpd.serve_forever()
