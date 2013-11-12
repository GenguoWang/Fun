#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import pcsSDK
import sys
import json
reload(sys)
sys.setdefaultencoding("UTF-8")
def syncToPcs(path,remotePath,rPath=""):
    print "here"
    if not os.path.isdir(path):
        return
    print "here"
    existFile = {}
    try:
        filelist = pcsSDK.getFileList(remotePath+rPath)
        for fileItem in filelist["list"]:
            existFile[fileItem["path"]] = fileItem
    except:
        pass
    for f in os.listdir(path):
        tf = os.path.join(path,f)
        if os.path.isfile(tf):
            print f
            tmpName = pcsSDK.gAppRoot+remotePath + rPath + f
            print tmpName
            if tmpName in existFile:
                print "exist:"+tf
            else:
                print "uploading:"+tf
                pcsSDK.uploadFile(remotePath+rPath,tf)
        elif os.path.isdir(tf):
            if len(rPath)==0:
                syncToPcs(tf,remotePath,f)
            else:
                syncToPcs(tf,remotePath,rPath+"/"+f)
config = json.loads(open("config.json").read())
for backPath in config["path"]:
    syncToPcs(backPath["local"],backPath["remote"]);
        
