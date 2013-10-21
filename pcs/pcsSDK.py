import urllib
import urllib2
import json
import mimetypes
import random
import string
import os

_BOUNDARY_CHARS = string.digits + string.ascii_letters
gApiKey = "jPNKG9NIr8o2gl0qeidwGddx"
gSecertKey = "8Xn4m6ir9Ab3xd3BHGwKkzYz54EVoL9U"
gCallbackUrl = "http://sharemark.tk/baidu/handle.php"
gBaseAuthUrl = "https://openapi.baidu.com/oauth/2.0/authorize"
gRefreshToken = "4.499b6935f2b7c3c9609d0472b50844f5.315360000.1697639866.2936395967-1489137"
gAccessToken = "3.88de92b660bdf9aaa6178e071ca629bd.2592000.1384871866.2936395967-1489137"
gAppRoot = "/apps/win8pan/"
gDebug = False
def getPath(path):
    if len(path)==0:
        return gAppRoot
    if path[0] == '/':
        return path
    return gAppRoot + path
def getAuthUrl():
    res = gBaseAuthUrl
    res += "?client_id="+gApiKey
    res += "&response_type=code"
    res += "&redirect_uri="+gCallbackUrl
    res += "&scope=netdisk pcs_doc pcs_album pcs_music pcs_video"
    return res

def getAccessTokenUrl(code):
    res = "https://openapi.baidu.com/oauth/2.0/token"
    res += "?client_id="+gApiKey
    res += "&grant_type=authorization_code"
    res += "&code="+code
    res += "&client_secret="+gSecertKey
    res += "&redirect_uri="+gCallbackUrl
    return res

def getQuota():
    url = "https://pcs.baidu.com/rest/2.0/pcs/quota"
    reqData = {}
    reqData["method"] = "info"
    res = httpRequest(url,"get",reqData)
    return json.loads(res)

def getMeta(path):
    path = getPath(path)
    url = "https://pcs.baidu.com/rest/2.0/pcs/file"
    reqData = {}
    reqData["method"] = "meta"
    reqData["path"] = path
    res = httpRequest(url,"get",reqData)
    return json.loads(res)

def getMetas(paths):
    url = "https://pcs.baidu.com/rest/2.0/pcs/file"
    reqData = {}
    pathPara = {"list":[]}
    for path in paths:
        path = getPath(path)
        pathPara["list"].append({"path":path})
    reqData["method"] = "meta"
    postData = {}
    postData["param"] = json.dumps(pathPara)
    res = httpRequest(url,"post",reqData,postData)
    return json.loads(res)

def getFileList(path,by=None,order=None,limit=None):
    path = getPath(path)
    url = "https://pcs.baidu.com/rest/2.0/pcs/file"
    reqData = {}
    reqData["method"] = "list"
    reqData["path"] = path
    if by:
        reqData["by"] = by
    if order:
        reqData["order"] = order
    if limit:
        reqData["limit"] = limit
    res = httpRequest(url,"get",reqData)
    return json.loads(res)

def uploadFile(path,filePath,newname=None,ondup=None):
    path = getPath(path)
    if not path[-1] == '/':
        path += '/'
    if newname:
        path += newname
    else:
        path += os.path.split(filePath)[1]
    url = "https://pcs.baidu.com/rest/2.0/pcs/file"
    reqData = {}
    reqData["method"] = "upload"
    reqData["path"] = path
    if ondup:
        reqData["ondup"] = ondup
    res = httpRequest(url,"postfile",reqData,{},filePath)
    return json.loads(res)

def addTask(source,path):
    url = "https://pcs.baidu.com/rest/2.0/pcs/services/cloud_dl"
    reqData = {}
    reqData["method"] = "add_task"
    reqData["source_url"] = source
    reqData["save_path"] = getPath(path)
    res = httpRequest(url,"get",reqData)
    return json.loads(res)
    
def httpRequest(url,method,reqData,postData={},filename=""):
    reqData["access_token"] = gAccessToken
    data = urllib.urlencode(reqData)
    url = url+"?"+data
    if gDebug:
        print "url: "+url
    if method=="post":
        pData = urllib.urlencode(postData)
        if gDebug:
            print "post:" +pData
        req = urllib2.Request(url,pData)
    elif method=="get":
        req = urllib2.Request(url)
    elif method=="postfile":
        boundary = ''.join(random.choice(_BOUNDARY_CHARS) for i in range(30))
        pData = "--"+boundary+"\r\nContent-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: application/octet-stream\r\n\r\n"%("file",filename)
        pData += open(filename, "rb").read()
        pData += "\r\n--" + boundary + "--\r\n"
        headers = {}
        headers["Content-Type"] = "multipart/form-data; boundary=" + boundary
        headers['Content-Length'] = str(len(pData))
        if gDebug:
            print pData
            print headers
        req = urllib2.Request(url,pData,headers)
    else:
        raise ValueError
    try:
        response = urllib2.urlopen(req)#,timeout=15)
        res = response.read()
    except urllib2.HTTPError, error:
        res = error.read()
    if gDebug:
        print res
    return res

if __name__ == "__main__":
    gDebug = True
    addTask("http://www.baidu.com","index.html")
