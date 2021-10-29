@echo off
cls
echo **************Please, press ctrl+D to continue*******************
node
cls
if %errorlevel% EQU 0 (
	npm>Nul
	if %errorlevel% EQU 9009 (
		echo npm is not installed please install it from link
		echo https://nodejs.org/en/download/
	)else if %errorlevel% EQU 0 (
		echo program works fine
		pause();
		cls
		npm install
		npm start
	)
)else if %errorlevel% EQU 9009 (
	echo Node.js is not installed please install it from link
	echo https://nodejs.org/en/download/
)
