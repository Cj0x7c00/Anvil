from dataclasses import dataclass
from ImportData import *

@dataclass
class WindowProps:
    width: int
    height: int
    name: str
    maximized: bool

    def __init__(self, w=900, h=700, n="Window", _max=False) -> None:
        self.width     = w
        self.height    = h
        self.name      = n
        self.maximized = _max

@dataclass
class AppProperties:
    name: str
    wrkdir: str
    wind_props:  WindowProps

    def __init__(self, _name: str, _workdir = "", _winProps = WindowProps()):
        anvil.create_app_properties(_name, _workdir, _winProps)

class AnvilApplication:
    def __init__(self, _p: AppProperties):
        pass