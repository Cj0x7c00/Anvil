#import wx  
from wizback import *
import sys


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == 'y':
        main(agree=True)
    else:
        main()
