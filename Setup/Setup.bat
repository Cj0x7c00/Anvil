call .\Wizard\.venv\Scripts\activate.bat
cd Wizard
pip install .
cls
py Wizard.py %1
pause