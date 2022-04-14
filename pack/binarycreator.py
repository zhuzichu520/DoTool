import os
import shutil
from greenlet import greenlet

path_ifw = "D:\\Qt\\QtIFW-4.3.0\\bin\\"
path_binarycreator = path_ifw + "binarycreator.exe"
exe_install = "installer.exe"


def main():
    print("开始生成install.exe")
    if os.path.exists(exe_install):
        shutil.rmtree(exe_install, True)
    print(exe_install)
    state = g_binarycreator.switch()
    if state == 1:
        print("install.exe已生成，随意按键退出程序")
        input()


def binarycreator():
    os.system(path_binarycreator + " --online-only -c config/config.xml -p packages installer")
    g_main.switch(1)


g_main = greenlet(main)
g_binarycreator = greenlet(binarycreator)
g_main.switch()
