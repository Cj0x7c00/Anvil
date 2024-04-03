call .\Wizard\.venv\Scripts\activate.bat
cd Wizard
pip install .
cls
py Wizard.py
echo Setup Complete
deactivate
pause