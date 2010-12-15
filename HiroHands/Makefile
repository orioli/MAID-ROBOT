
all:
	(cd lib; make)
	(cd test0; make)
	(cd test1; make)

clean::
	/bin/rm -f *~
	(cd lib; make clean)
	(cd test0; make clean)
	(cd test1; make clean)

cleanall:: clean
	(cd lib; make cleanall)
	(cd test0; make cleanall)
	(cd test1; make cleanall)
	/bin/rm -rf HiroHands.suo HiroHands.ncb Release Debug
