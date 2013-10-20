import urllib
import urllib2
import json
import mimetypes
import random
import string

_BOUNDARY_CHARS = string.digits + string.ascii_letters

def encode_multipart(fields, files, boundary=None):
    r"""Encode dict of form fields and dict of files as multipart/form-data.
    Return tuple of (body_string, headers_dict). Each value in files is a dict
    with required keys 'filename' and 'content', and optional 'mimetype' (if
    not specified, tries to guess mime type or uses 'application/octet-stream').

    >>> body, headers = encode_multipart({'FIELD': 'VALUE'},
    ...                                  {'FILE': {'filename': 'F.TXT', 'content': 'CONTENT'}},
    ...                                  boundary='BOUNDARY')
    >>> print('\n'.join(repr(l) for l in body.split('\r\n')))
    '--BOUNDARY'
    'Content-Disposition: form-data; name="FIELD"'
    ''
    'VALUE'
    '--BOUNDARY'
    'Content-Disposition: form-data; name="FILE"; filename="F.TXT"'
    'Content-Type: text/plain'
    ''
    'CONTENT'
    '--BOUNDARY--'
    ''
    >>> print(sorted(headers.items()))
    [('Content-Length', '193'), ('Content-Type', 'multipart/form-data; boundary=BOUNDARY')]
    >>> len(body)
    193
    """
    def escape_quote(s):
        return s.replace('"', '\\"')

    if boundary is None:
        boundary = ''.join(random.choice(_BOUNDARY_CHARS) for i in range(30))
    lines = []

    for name, value in fields.items():
        lines.extend((
            '--{0}'.format(boundary),
            'Content-Disposition: form-data; name="{0}"'.format(escape_quote(name)),
            '',
            str(value),
        ))

    for name, value in files.items():
        filename = value['filename']
        if 'mimetype' in value:
            mimetype = value['mimetype']
        else:
            mimetype = mimetypes.guess_type(filename)[0] or 'application/octet-stream'
        lines.extend((
            '--{0}'.format(boundary),
            'Content-Disposition: form-data; name="{0}"; filename="{1}"'.format(
                    escape_quote(name), escape_quote(filename)),
            'Content-Type: {0}'.format(mimetype),
            '',
            value['content'],
        ))

    lines.extend((
        '--{0}--'.format(boundary),
        '',
    ))
    body = '\r\n'.join(lines)

    headers = {
        'Content-Type': 'multipart/form-data; boundary={0}'.format(boundary),
        'Content-Length': str(len(body)),
    }

    return (body, headers)

gApiKey = "jPNKG9NIr8o2gl0qeidwGddx"
gSecertKey = "8Xn4m6ir9Ab3xd3BHGwKkzYz54EVoL9U"
gCallbackUrl = "http://sharemark.tk/baidu/handle.php"
gBaseAuthUrl = "https://openapi.baidu.com/oauth/2.0/authorize"
gRefreshToken = "4.499b6935f2b7c3c9609d0472b50844f5.315360000.1697639866.2936395967-1489137"
gAccessToken = "3.88de92b660bdf9aaa6178e071ca629bd.2592000.1384871866.2936395967-1489137"
gAppRoot = "/apps/win8pan/"
gDebug = True
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
    if len(path)==0 or (not path[0] == '/'):
        path = gAppRoot + path
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
        if len(path)==0 or (not path[0] == '/'):
            path = gAppRoot + path
        pathPara["list"].append({"path":path})
    reqData["method"] = "meta"
    postData = {}
    postData["param"] = json.dumps(pathPara)
    res = httpRequest(url,"post",reqData,postData)
    return json.loads(res)

def getFileList(path,by=None,order=None,limit=None):
    if len(path)==0 or (not path[0] == '/'):
        path = gAppRoot + path
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

def uploadFile(path,filePath,ondup="newcopy"):
    if len(path)==0 or (not path[0] == '/'):
        path = gAppRoot + path
    url = "https://pcs.baidu.com/rest/2.0/pcs/file"
    reqData = {}
    reqData["method"] = "upload"
    reqData["path"] = path
    res = httpRequest(url,"postfile",reqData,{},filePath)
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
        pData,headers = encode_multipart({},{"file":{"mimetype":"application/octet-stream","filename":filename,"content":open(filename, "rb").read()}})
        #boundary = "---------------------------wggkingowangboundary5211314"
        #boundarybytes = "\r\n--" + boundary + "\r\n"
        #headers["ContentType"] = "multipart/form-data; boundary=" + boundary
        #pData = "Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: application/octet-stream\r\n\r\n"%("file",filename)
        #pData += pData+open(filename, "rb").read()
        #pData += "\r\n--" + boundary + "--\r\n"
        #headers['Content-Length'] = str(len(pData))
        if gDebug:
            print "post:" +pData
        req = urllib2.Request(url,pData,headers)
    else:
        raise ValueError
    try:
        response = urllib2.urlopen(req)#,timeout=15)
        res = response.read()
    except Exception,e:
        print e.msg
    if gDebug:
        print res
    return res

