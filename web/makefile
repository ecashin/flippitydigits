PROG = flippity
FLOW = $$HOME/git/flow/bin/flow
JSDIR := static/js
CSSDIR := static/css
.PHONY: show all srv watch clean

WATCH_CHECK = kill -0 `cat watcher.pid`

all: $(CSSDIR)/flippity.css
	if ! $(WATCH_CHECK); then \
	  make watch & \
	  sleep 1; \
	fi
	while ! $(WATCH_CHECK); do \
	  sleep 1; \
	done
	@echo The jsx watcher is running.  Stop with '"make stopwatch"'.

srv:
	python -mSimpleHTTPServer

show:
	echo $(PROGS)

stopwatch:
	test -r watcher.pid
	kill `cat watcher.pid`

watch:
	jsx --strip-types --harmony --watch src $(JSDIR) & \
	  echo $$! > watcher.pid

$(JSDIR)/%.js: src/%.js
	$(FLOW) check $<

clean:
	rm -f $(CSSDIR)/flippity.css $(JSDIR)/*.js

$(CSSDIR)/%.css: %.less
	node_modules/.bin/lessc $< $@
