import colorama
import requests
from pathlib import  Path
import sys
import time
import platform
import console
import subprocess
import licence
from rich.progress import track
import os

VK_REQ_VER = "1.3.231.1"
VK_LOC_DIR = "vendor/VkSDK"
VK_SDK_EXE_PATH = f'{VK_LOC_DIR}/VulkanSDK.exe'
VK_INST_URL = f'https://sdk.lunarg.com/sdk/download/{VK_REQ_VER}/{platform.system().lower()}/VulkanSDK-{VK_REQ_VER}-Installer.exe'

eDepends = {
    "VULKANSDK" : os.getenv("VULKAN_SDK")
}

def Licence(agree):
    if agree == False:
        console.PrintMD(licence.licence)
        b = console.YorN(colorama.Back.LIGHTBLACK_EX + colorama.Fore.GREEN + "Agree? " + colorama.Style.RESET_ALL)
        if b == True:
            pass
    elif agree == True:
        print('"Y" was passed during setup, by continuing you agree to the licence')
    else:
        print("You must agree with the licence!" + colorama.Style.RESET_ALL)
        quit()

#download missing dependencies
def Get(depend):
    if depend == "VULKANSDK":
        os.chdir('..')
        Path(VK_LOC_DIR).mkdir(parents=True, exist_ok=True)
        print(f"{colorama.Fore.GREEN}{colorama.Back.BLUE}Downloading VulkanSDK to {VK_LOC_DIR}{colorama.Style.RESET_ALL}")
        with open(VK_SDK_EXE_PATH, 'wb') as ef:
            print(f"{colorama.Fore.CYAN}Retreving SDK installer...{colorama.Style.RESET_ALL}")
            r = requests.get(VK_INST_URL, stream=True)
            t = r.headers.get('content-length')
            print(f'{colorama.Fore.GREEN}Downloading...{colorama.Style.RESET_ALL}')
            if t is None:
                ef.write(r.content)
            else:
                downloaded = 0
                total = int(t)
                startTime = time.time()
                for data in track(r.iter_content(chunk_size=max(int(total/1000), 1024*1024)), description="Downloading Vulkan Installer..."):
                    downloaded += len(data)
                    ef.write(data)
                    #progress
                    done = int(50*downloaded/total)
                    percentage = (downloaded / total) * 100
                    elapsedTime = time.time() - startTime
                    avgKBPerSecond = (downloaded / 1024) / elapsedTime
                    avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
                    if (avgKBPerSecond > 1024):
                        avgMBPerSecond = avgKBPerSecond / 1024
                        avgSpeedString = '{:.2f} MB/s'.format(avgMBPerSecond)
                    sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50-done), percentage, avgSpeedString))
                    sys.stdout.flush()
            ef.close()
            sys.stdout.write('\n')
            os.startfile(os.path.abspath(VK_SDK_EXE_PATH))

def GetDepend():
    print(VK_INST_URL)
    for d in eDepends:
        if eDepends[d] is None:
            if console.YorN(f"{colorama.Fore.RED}VulkanSDK Not found! Install it?{colorama.Style.RESET_ALL}"):
                Get(d)
                print(f"{colorama.Fore.YELLOW}Re-Run the wizard{colorama.Style.RESET_ALL}")
                quit()
            else:
                print(f"{colorama.Fore.RED} Settup cannot continue without the vulkan SDK. as the engine requires it!\nStoping...{colorama.Style.RESET_ALL}")
        else:
            continue

#run premake
def Build():
    print(f"{colorama.Fore.GREEN}== Running Premake =={colorama.Style.RESET_ALL}")
    os.chdir('../..')
    os.system('.\\vendor\\premake5\\premake5.exe vs2022')
    print(f"{colorama.Fore.GREEN}{colorama.Back.LIGHTWHITE_EX}Setup Complete{colorama.Style.RESET_ALL}")

def main(agree=False):
    Licence(agree)
    GetDepend()
    Build()