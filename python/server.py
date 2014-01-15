import web

CONTENT_PATH = "/opt/julio/content"

class RootHandler(object):
    def __init__(self):
        print "[INFO] Creating RootHandler"

    def GET(self, resource):
        path = CONTENT_PATH + '/' + resource
        return open(path).read()

class ProcHandler(object):
    def __init__(self):
        print "[INFO] Creatint ProcHandler"

    def GET(self):
        path = '/proc/meminfo'
        return open(path).read()

URLS = (
'/proc', ProcHandler,
'/(.*)', RootHandler
)


if __name__ == "__main__":
    app = web.application(URLS, globals())
    app.run()
