#import wx  
from wizback import *
import sys


if __name__ == "__main__":
    if sys.argv[1] == 'y':
        main(agree=True)
    else:
        main()
