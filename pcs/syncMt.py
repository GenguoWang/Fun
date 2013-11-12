#!/usr/bin/env python
# -*- coding: utf-8 -*- 
import subprocess
import os
import sys
import pcsSDK
import threading
import json
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
        pcsSDK.uploadFile(filename["remotePath"],filename["localPath"],ondup="overwrite")
    
def syncToPcs(path,remote,rPath=""):
    global uploadList
    if not os.path.isdir(path):
        return
    existFile = {}
    try:
        filelist = pcsSDK.getFileList(remote+rPath)
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
            tmpName = pcsSDK.gAppRoot+remote + rPath + f
            if u""+tmpName in existFile:
                print "exist:"+tf
            else:
                uploadList.append({"remotePath":remote+rPath,"localPath":tf})
        elif os.path.isdir(tf):
            syncToPcs(tf,rPath+f+"/")
config = json.loads(open("config.json").read())
rarPaht = ""
if "rarPath" in config:
    rarPath = config["rarPath"]
os.system("del /f/s/q tmp\\*")
for backPath in config["path"]:
    if "rar" in backPath and backPath["rar"]:
        subprocess.call([rarPath,"a","-r","-ep1","tmp\\"+backPath["rarName"],backPath["local"]])
        uploadList.append({"remotePath":backPath["remote"],"localPath":"tmp\\"+backPath["rarName"]+".rar"})
    else:
        syncToPcs(backPath["local"],backPath["remote"])
print "begin upload"
for i in range(min(len(uploadList),maxThreadNum)):
    threading.Thread(target=uploadWorker).start()
os.system("pause")
        
