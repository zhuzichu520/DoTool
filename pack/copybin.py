import os
import shutil

path_data = "./packages/DoTool/data"
path_bin = "./../bin"


def main():
    print("开始复制文件")
    if os.path.exists(path_data):
        shutil.rmtree(path_data, True)
    shutil.copytree(path_bin, path_data)


if __name__ == '__main__':
    main()
