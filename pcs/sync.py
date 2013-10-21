import os
import pcsSDK
gLocalPath="/home/kingo/pcsbak"
gRemotePath="bak/"
def syncToPcs(path,rPath):
    if not os.path.isdir(path):
        return
    existFile = {}
    try:
        filelist = pcsSDK.getFileList(gRemotePath+rPath)
        for fileItem in filelist["list"]:
            print fileItem["path"]
            existFile[fileItem["path"]] = fileItem
    except:
        pass
    for f in os.listdir(path):
        tf = os.path.join(path,f)
        if os.path.isfile(tf):
            tmpName = pcsSDK.gAppRoot+gRemotePath + rPath + f
            print tmpName
            if tmpName in existFile:
                print "exist:"+tf
            else:
                print "sync:"+tf
                pcsSDK.uploadFile(gRemotePath+rPath,tf)
        elif os.path.isdir(tf):
            syncToPcs(tf,rPath+"/"+f)
syncToPcs(gLocalPath,"");
        
