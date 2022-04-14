import os
import shutil
import time
from threading import Thread

path_ifw = "D:\\Qt\\QtIFW-4.3.0\\bin\\"
path_repogen = path_ifw + "repogen.exe"
repository = "repository"

isLoading = True


def asyncThread(f):
    def wrapper(*args, **kwargs):
        thr = Thread(target=f, args=args, kwargs=kwargs)
        thr.start()

    return wrapper


@asyncThread
def repogen(func):
    os.system(path_repogen + " -p packages " + repository)
    func()


def loading():
    print("正在生成repository,请耐心等待...")
    while isLoading:
        print(".", end="", flush=True)
        time.sleep(0.5)


def repogenFunc():
    global isLoading
    isLoading = False
    print("\nrepository已生成，随意按键退出程序...")
    input()


def main():
    if os.path.exists(repository):
        shutil.rmtree(repository, True)
    print(path_repogen)
    repogen(lambda: repogenFunc())
    loading()


if __name__ == '__main__':
    main()
