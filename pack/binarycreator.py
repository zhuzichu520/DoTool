import os
import shutil
import time
from threading import Thread

path_ifw = "D:\\Qt\\QtIFW-4.3.0\\bin\\"
path_binarycreator = path_ifw + "binarycreator.exe"
exe_install = "installer.exe"

isLoading = True


def asyncThread(f):
    def wrapper(*args, **kwargs):
        thr = Thread(target=f, args=args, kwargs=kwargs)
        thr.start()

    return wrapper


@asyncThread
def binarycreator(func):
    os.system(path_binarycreator + " --online-only -c config/config.xml -p packages installer")
    func()


def loading():
    print("正在生成离线安装包,请耐心等待...")
    while isLoading:
        print(".", end="", flush=True)
        time.sleep(0.5)


def binarycreatorFunc():
    global isLoading
    isLoading = False
    print("\n离线安装包已生成，随意按键退出程序...")
    input()


def main():
    if os.path.exists(exe_install):
        shutil.rmtree(exe_install, True)
    print(exe_install)
    binarycreator(lambda: binarycreatorFunc())
    loading()


if __name__ == '__main__':
    main()
