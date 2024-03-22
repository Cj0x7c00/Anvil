"""
Main DLL Loader and python wrapper.
basically, a dock where c can port
"""

import ctypes

anvil = ctypes.cdll.LoadLibrary("./PyScriptEngine.dll");




