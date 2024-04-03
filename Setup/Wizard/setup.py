import subprocess

try:
    from setuptools import *
except:
    print("Setup tools not installed... Installing.")
    subprocess.check_call(["python", "-m", "pip", "install", "setuptools"])

setup(
    name="Setup_Wizard",
    version="0.1",
    py_modules=['Wizard', 'wizback', 'console', 'licence'],
    install_requires=(["colorama", "requests", "rich"])
)