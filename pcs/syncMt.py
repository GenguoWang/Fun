#!/usr/bin/env python
# -*- coding: utf-8 -*- 
import subprocess
import os
import shutil
import sys
import pcsSDK
import threading
import json
lock = threading.Lock()
maxThreadNum = 10
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
        i = 0
        while i<3:
            try:
                pcsSDK.uploadFile(filename["remotePath"],filename["localPath"],ondup="newcopy")
                sys.stdout.write("uploaded "+filename["localPath"]+"\n")
                break
            except:
                i += 1
    
def syncToPcs(path,remote,rPath=""):
    global uploadList
    if not os.path.isdir(path):
        return
    existFile = {}
    try:
        filelist = pcsSDK.getFileList(remote+rPath)
        for fileItem in filelist["list"]:
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
                print "add to upload:"+tf
                uploadList.append({"remotePath":remote+rPath,"localPath":tf})
        elif os.path.isdir(tf):
            syncToPcs(tf,rPath+f+"/")


workDir = os.path.dirname(__file__)
tmpDir = os.path.join(workDir,"tmp")
if os.path.exists(tmpDir):
    shutil.rmtree(tmpDir)
os.mkdir(tmpDir) 
config = json.loads(open(os.path.join(workDir,"config.json")).read())
pcsSDK.setAccessToken(config["access_key"])
pcsSDK.gAppRoot = config["appRoot"]
rarPaht = ""
if "rarPath" in config:
    rarPath = config["rarPath"]
os.system("del /f/s/q "+os.path.join(workDir,"tmp\\*"))
for backPath in config["path"]:
    if "rar" in backPath and backPath["rar"]:
        print "rar "+backPath["local"]
        subprocess.call([rarPath,"a","-idq","-r","-ep1",os.path.join(workDir,"tmp\\"+backPath["rarName"]),backPath["local"]])
        uploadList.append({"remotePath":backPath["remote"],"localPath":os.path.join(workDir,"tmp\\"+backPath["rarName"]+".rar")})
    else:
        syncToPcs(backPath["local"],backPath["remote"])
print "begin upload"
for i in range(min(len(uploadList),maxThreadNum)):
    threading.Thread(target=uploadWorker).start()
os.system("pause")
        
