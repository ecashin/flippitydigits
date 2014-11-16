PROG = flippity
JSDIR := static/js
CSSDIR := static/css
PROGS := $(addprefix $(JSDIR)/,$(addsuffix .js,$(basename $(wildcard *.ts))))
.PHONY: show all srv clean

all: $(PROGS) $(CSSDIR)/flippity.css

srv: all
	./devsrv.py

show:
	echo $(PROGS)

$(CSSDIR)/%.css: %.styl
	stylus < $< > $@

$(JSDIR)/%.js: %.ts
	tsc --out $@ $<

clean:
	rm -f $(PROGS)
