import colorama
import rich as  rch
from rich.markdown import Markdown
from rich.text import Text

def YorN(ctx: str) -> bool:
    print("\n")
    fmt = Text(ctx, style="blue bold")
    rch.print(fmt)
    i = input("(Y/N): ").lower()
    if i == "y":
        return True
    if i == "n":
        return False
    else:
        print(colorama.Fore.RED + "expected: y/n... stopping")

def PrintMD(mkd_src):
    rch.print(Markdown(mkd_src))