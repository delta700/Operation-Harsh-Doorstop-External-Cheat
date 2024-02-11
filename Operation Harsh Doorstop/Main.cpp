#include "Util.h"

/*
*		Credit: https://github.com/Mokobake/TPSShootingGame-Cheat, https://github.com/Mokobake/Fortnite-EZ-No-Recoil
*
*		Author:  hxxven https://github.com/ReadPhysicalMemory
*/

namespace Settings
{
	bool FovChanger = false;
	bool SpeedHackAndNoRecoil = false;
	bool Fly = false;
}

void SettingsThread()
{
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		Settings::SpeedHackAndNoRecoil = !Settings::SpeedHackAndNoRecoil;

		if (Settings::SpeedHackAndNoRecoil)
		{
			printf("True SpeedHackAndNoRecoil\n");
		}
		else
		{
			printf("False SpeedHackAndNoRecoil\n");
		}
	}

	if (GetAsyncKeyState(VK_F2) & 1)
	{
		Settings::FovChanger = !Settings::FovChanger;

		if (Settings::FovChanger)
		{
			printf("True FovChanger\n");
		}
		else
		{
			printf("False FovChanger\n");
		}
	}

	if (GetAsyncKeyState(VK_F3) & 1)
	{
		Settings::Fly= !Settings::Fly;

		if (Settings::Fly)
		{
			printf("True Fly\n");
		}
		else
		{
			printf("False Fly\n");
		}
	}
}

bool main()
{
	SetConsoleTitleA("Operation Harsh Doorstop Cheat");

	printf("Waiting Operation Harsh Doorstop\n");

	while (true)
	if (FindWindowA("UnrealWindow", "Operation: Harsh Doorstop  ")) break;

	system("cls");
	printf("Operation Harsh Doorstop Found\n");
	Sleep(500);
	system("cls");

	ProcessId = GetProcessId(L"HarshDoorstop-Win64-Shipping.exe");
	ProcessHandle = GetProcessHandle(ProcessId);
	BaseAddress = GetBaseAddress(L"HarshDoorstop-Win64-Shipping.exe", ProcessId);

	printf("ProcessId: 0x%llX\n", ProcessId);
	printf("ProcessHandle: 0x%llX\n", ProcessHandle);
	printf("BaseAddress: 0x%llX\n", BaseAddress);

	printf("[F1] SpeedHackAndNoRecoil\n");
	printf("[F2] FovChanger\n");
	printf("[F3] Fly\n");

	while (true)
	{
		SettingsThread();
		uintptr_t UWorld = Read<uintptr_t>(ProcessHandle, BaseAddress + 0x4377658);
		uintptr_t GameInstance = Read<uintptr_t>(ProcessHandle, UWorld + 0x188);
		uintptr_t LocalPlayers = Read<uintptr_t>(ProcessHandle, Read<uintptr_t>(ProcessHandle, GameInstance + 0x38));
		uintptr_t PlayerController = Read<uintptr_t>(ProcessHandle, LocalPlayers + 0x30);
		uintptr_t PlayerCameraManager = Read<uintptr_t>(ProcessHandle, PlayerController + 0x2B8);
		uintptr_t LocalPawn = Read<uintptr_t>(ProcessHandle, PlayerController + 0x2A0);
		uintptr_t RootComponent = Read<uintptr_t>(ProcessHandle, LocalPawn + 0x130);
		Vector3 RelativeLocation = Read<Vector3>(ProcessHandle, RootComponent + 0x11C);

		if (Settings::FovChanger)
			Write<float>(ProcessHandle, PlayerCameraManager + 0x238 + 0x4, 160);

		if (Settings::SpeedHackAndNoRecoil)
			Write<float>(ProcessHandle, LocalPawn + 0x98, 6); //CustomTimeDilation

		if (Settings::Fly)
		{
			if (GetAsyncKeyState('W'))
			{
				RelativeLocation.x += 0.1;
			}
			if (GetAsyncKeyState('S'))
			{
				RelativeLocation.x -= 0.1;
			}
			if (GetAsyncKeyState('A'))
			{
				RelativeLocation.y -= 0.1;
			}
			if (GetAsyncKeyState('D'))
			{
				RelativeLocation.y += 0.1;
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				RelativeLocation.z += 0.1;
			}
			if (GetAsyncKeyState(VK_LSHIFT))
			{
				RelativeLocation.z -= 0.1;
			}

			Write<Vector3>(ProcessHandle, RootComponent + 0x11c, RelativeLocation);
			Write<char>(ProcessHandle, RootComponent + 0x14c, 0);
		}

		if (GetAsyncKeyState(VK_END) & 1)
			exit(0);
	}
}