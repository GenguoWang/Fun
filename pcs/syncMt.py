#!/usr/bin/env python
# -*- coding: utf-8 -*- 
import os
import sys
import pcsSDK
import threading
gLocalPath="/home/kingo/Android/Fun"
gRemotePath="t4/"
lock = threading.Lock()
maxThreadNum = 50
uploadList = []
index=0
reload(sys)
sys.setdefaultencoding("UTF-8")
def uploadWorker():
    global index
    while True:
        lock.acquire()
        if index < len(uploadList):
            filename = uploadList[index]
            index += 1
            lock.release()
        else:
            lock.release()
            return
        sys.stdout.write("uploading "+filename["localPath"]+"\n")
        pcsSDK.uploadFile(filename["remotePath"],filename["localPath"])
    
def syncToPcs(path,rPath):
    global uploadList
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
        if f[0]==".":
            continue
        tf = os.path.join(path,f)
        if os.path.isfile(tf):
            tmpName = pcsSDK.gAppRoot+gRemotePath + rPath + f
            if u""+tmpName in existFile:
                print "exist:"+tf
            else:
                uploadList.append({"remotePath":gRemotePath+rPath,"localPath":tf})
        elif os.path.isdir(tf):
            syncToPcs(tf,rPath+f+"/")
syncToPcs(gLocalPath,"")
print "begin upload"
for i in range(min(len(uploadList),maxThreadNum)):
    threading.Thread(target=uploadWorker).start()
        

