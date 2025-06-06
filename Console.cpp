#include "Includes.h"

namespace Console
{
	void Size(HWND console, int width, int height)
	{
		RECT r;
		GetWindowRect(console, &r);

		MoveWindow(console, r.left, r.top, width, height, TRUE);
	}

	void Alpha(HWND console)
	{
		SetWindowLong(console, GWL_EXSTYLE,
			GetWindowLong(console, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(console, 0, 250, LWA_ALPHA);
	}
	
	std::string RandomStr(const size_t length)
	{
		std::string r;
		static const char bet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYabcdefghijklmnopqrstuvwxyzZ1234567890" };
		srand((unsigned)time(NULL) * 5);
		for (int i = 0; i < length; ++i)
			r += bet[rand() % (sizeof(bet) - 1)];
		return r;
	}

	std::string Encrypt(const std::string& data)
	{
		std::string encryptedData = data;
		for (char& character : encryptedData)
		{
			character = (character + 3) % 128;
		}

		return encryptedData;
	}

	std::string Decrypt(const std::string& encryptedData)
	{
		std::string decryptedData = encryptedData;
		for (char& character : decryptedData)
		{
			character = (character - 3 + 128) % 128;
		}

		return decryptedData;
	}
}