PROG = flippity
JSDIR := static/js
PROGS := $(addprefix $(JSDIR)/,$(addsuffix .js,$(basename $(wildcard *.ts))))
.PHONY: show all srv clean

all: $(PROGS)

srv: all
	./devsrv.py

show:
	echo $(PROGS)

$(JSDIR)/%.js: %.ts
	tsc --out $@ $<

clean:
	rm -f $(PROGS)
