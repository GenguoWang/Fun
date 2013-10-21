import os
import pcsSDK
import threading
gLocalPath="/home/kingo/Android/Fun"
gRemotePath="t5/"
def syncToPcs(path,rPath):
    if not os.path.isdir(path):
        return
    existFile = {}
    try:
        filelist = pcsSDK.getFileList(gRemotePath+rPath)
        for fileItem in filelist["list"]:
            existFile[fileItem["path"]] = fileItem
    except:
        pass
    for f in os.listdir(path):
        tf = os.path.join(path,f)
        if os.path.isfile(tf):
            print f
            tmpName = pcsSDK.gAppRoot+gRemotePath + rPath + f
            print tmpName
            if tmpName in existFile:
                print "exist:"+tf
            else:
                print "uploading:"+tf
                pcsSDK.uploadFile(gRemotePath+rPath,tf)
        elif os.path.isdir(tf):
            if len(rPath)==0:
                syncToPcs(tf,f)
            else:
                syncToPcs(tf,rPath+"/"+f)
syncToPcs(gLocalPath,"");
        
