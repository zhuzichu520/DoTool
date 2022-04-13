import os

path = "D:\\Qt\\QtIFW-4.3.0\\bin\\"
binarycreator = path+"binarycreator.exe"
print(binarycreator)
status = os.system(binarycreator+" --online-only -c config/config.xml -p packages installer")
input()