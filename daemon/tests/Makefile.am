PORT = 1234

start :
	$(top_builddir)/src/mydaemond -p 1234

debug :
	$(top_builddir)/src/mydaemond -p 1234 -F

stop :
	pkill mydaemond

test :
	$(top_builddir)/client/client --host localhost --port $(PORT)

