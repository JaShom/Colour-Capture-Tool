#include <Windows.h>
#include <iomanip>
#include <sstream>
#include <iostream>
// using namespace std;

std::string RGBtoHex(int red, int green, int blue) {
	std::stringstream ss;

	ss << "#" << std::hex << std::setw(2) << std::setfill('0') << red
		<< std::setw(2) << std::setfill('0') << green
		<< std::setw(2) << std::setfill('0') << blue;

	return ss.str();
}

int main() {

	HCURSOR precisionCursor = LoadCursor( NULL, IDC_CROSS ); // Load Precision Select cursor
	// Struggling to load precision cursor <- Find solution later

	if (precisionCursor != NULL) {

		SetCursor(precisionCursor); // Set cursor to Precision Select cursor

		bool quit = false;

		while (!quit) {

			if (GetAsyncKeyState('Q') & 0x8000) { // Check if 'Q' key is pressed to quit
				quit = true;
			}

			POINT cursorPosition;
			GetCursorPos(&cursorPosition);

			int x = cursorPosition.x;
			int y = cursorPosition.y;

			HDC hdcScreen = GetDC(NULL);
			COLORREF pixelColor = GetPixel(hdcScreen, x, y);
			ReleaseDC(NULL, hdcScreen);

			int red = GetRValue(pixelColor);
			int green = GetGValue(pixelColor);
			int blue = GetBValue(pixelColor);

			std::string hexColours = RGBtoHex(red, green, blue);

			// To clear screen
			system("cls");
	
			std::cout << "Current cursor position: x = " << x << " , y = " << y << std::endl;
			std::cout << "Current RGB colour: R = " << red << " , G = " << green << ", B = " << blue << std::endl;
			std::cout << "RGB To Hexdecimals: " << hexColours << std::endl;

			// Sleep to avoid high CPU usage
			Sleep(100);

		}

		SetCursor(LoadCursor(NULL, IDC_ARROW)); // Restore to default cursor

	}

	

	return 0;
}