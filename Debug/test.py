from ctypes import *  
dll = cdll.LoadLibrary('FacePlus.dll');  
ret = dll.groupManger(1, "Test2");  
print ret;
##
##    /*
##    ret = dll.groupManger(0, "Test1");  
##    print ret;
##
##    ret = dll.testInt();  
##    print ret;
##
##    sss = dll.testString();  
##    print sss;

