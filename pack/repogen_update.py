import os

path = "D:\\Qt\\QtIFW-4.3.0\\bin\\"
repogen = path + "repogen.exe"
print(repogen)
status = os.system(repogen + " --update-new-components -p packages_update repository")
input()
